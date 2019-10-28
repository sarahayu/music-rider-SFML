#include "GameState.h"

#include "../entities/Portal.h"
#include "../entities/Obstacle.h"
#include "../utils/MathUtils.h"
#include "../Settings.h"
#include <iostream>
#include <SFML\Audio.hpp>


const float PAN_SPEED = 150.f;
const float SQRT3 = 1.73205080757f;

GameState::GameState(StateStack & stack, Context & context)
	: State(stack, context), m_view({}, (sf::Vector2f)context.window->getSize()/1.8f), m_layers(LayerCount), 
	m_background(context.textures->get(Textures::Background), { m_view.getSize().y*6, m_view.getSize().y}, 30.f),
	m_ground(context.textures->get(Textures::Ground), { (float)context.window->getSize().y/2*4, (float)context.window->getSize().y / 2 }, Settings::X_SPEED),
	m_shadow((sf::Vector2f)context.window->getSize()),
	m_finishLine({ 100.f,417.f }),
	m_player(Player::Jumper, *context.textures)
{
	m_player.setPosition(*getContext().newStart);
	m_trail.loadTexture(*context.textures);
	m_shadow.setTexture(&context.textures->get(Textures::Shadow));
	m_finishLine.setTexture(&context.textures->get(Textures::Table));
	m_finishLine.setPosition(context.music->getDuration().asSeconds()*Settings::X_SPEED,-278.f);

	m_view.setCenter(m_player.getPosition());
	
	m_layers[Background].push_back(&m_background);
	m_layers[Terrain].resize(context.entities->size());
	std::transform(context.entities->begin(), context.entities->end(), m_layers[Terrain].begin(), [](const Entity::Ptr& e) {return e.get(); });
	m_layers[Terrain].push_back(&m_ground);
	m_layers[Terrain].push_back(&m_finishLine);

	m_layers[Air].push_back(&m_trail);
	m_layers[PlayerLayer].push_back(&m_player);
	
	context.music->play();
	context.music->setPlayingOffset(sf::seconds(*getContext().musicStart));
}

void GameState::draw()
{
	auto &window = getContext().window;

	window->clear(sf::Color::Cyan);
	window->setView(m_view);

	for (const auto &layer : m_layers) 
		for (const auto &sprite : layer) window->draw(*sprite);

	window->setView(window->getDefaultView());
	window->draw(m_shadow);
	getContext().window->setView(m_view);
}

const bool GameState::update(const float & deltaTime)
{
	if (*getContext().requestRestart)
	{
		*getContext().requestRestart = false;
		resetPlayer();
	}

	m_player.realTimeInput(deltaTime);
	m_player.update(deltaTime);

	if (m_player.requestingPrediction()) predictCollision();

	checkCollisions();

	m_trail.update(m_player.getPosition(), deltaTime);

	const float oldY = m_view.getCenter().y;
	const auto viewBounds = getViewBounds();
	if (viewBounds.left + viewBounds.width - 100.f < m_finishLine.getPosition().x) m_view.setCenter(m_player.getPosition().x, oldY);

	const float playerY = m_player.getPosition().y;
	if (m_player.getType() == Player::Jumper)
	{
		const float yDif = oldY - playerY;
		const float maxYDist = m_view.getSize().y / 6;

		if (m_player.getType() == Player::Jumper && (m_player.getVelocity() == 0.f || std::abs(yDif) > maxYDist))
			m_view.move(0.f, -yDif *deltaTime * 2.f);
	}
	else if (m_player.getType() == Player::Flyer)
		m_view.move(0.f, -(oldY + viewBounds.height/2.f-10.f)*deltaTime*2.f);

	m_background.update(deltaTime, m_view.getCenter() - m_view.getSize() / 2.f);
	m_ground.update(deltaTime, {m_view.getCenter().x - m_view.getSize().x/2, 0.f});

	if (getContext().music->getStatus() == sf::SoundSource::Stopped && m_player.getPosition().x >= m_finishLine.getPosition().x)
		requestStackPush(States::GameOverState);

	return true;
}

const bool GameState::handleEvent(const sf::Event & evnt)
{
	typedef sf::Keyboard sfk;
	if (evnt.type == sf::Event::KeyPressed)
	{
		switch (evnt.key.code)
		{
		case sfk::R:
			resetPlayer();
			break;
		case sfk::E:
			requestStackPop();
			requestStackPush(States::EditorState);
			getContext().music->stop();
			break;
		case sfk::Escape:
			getContext().music->pause();
			requestStackPush(States::PauseState);
			break;
		}
	}
	return true;
}

void GameState::predictCollision()
{
	bool collided = false;
	Player copy(m_player);

	const float dt = 15.f / Settings::X_SPEED;
	while (!collided)
	{
		copy.update(dt);

		const float bottom = copy.getPosition().y + copy.getSize().y / 2;
		if (bottom > 0.f)
		{
			collided = true;
			break;
		}

		for (const auto &entity : *getContext().entities)
		{
			if (mu::distanceSquared(entity->getPosition(), copy.getPosition()) < 4500.f
				&& mu::getCollision(entity->getGlobalBounds(), copy.getGlobalBounds()).side != CollisionInfo::None)
			{
				collided = true;
				break;
			}
		}
	}

	m_player.setRotationSpeed(90.f / ((copy.getPosition().x - m_player.getPosition().x) / Settings::X_SPEED));
}

void GameState::checkCollisions()
{
	const float bottom = m_player.getPosition().y + m_player.getSize().y / 2;
	if (bottom > 0.f)
	{
		m_player.move({ 0.f,std::min(0.f,-bottom) });
		m_player.setToRest();
	}

	for (const auto &entity : *getContext().entities)
	{
		if (mu::distanceSquared(entity->getPosition(), m_player.getPosition()) < 4500.f)
		{
			const CollisionInfo coll = mu::getCollision(entity->getGlobalBounds(), m_player.getGlobalBounds());
			if (entity->getType() == Entities::Spike)
			{
				if (((Obstacle*)entity.get())->getObstacleType() == Obstacle::UpBigSpike)
				{/*
					if (coll.side == CollisionInfo::Left)
					{
						const sf::FloatRect spikeBounds = entity->getGlobalBounds(), playerBounds = m_player.getGlobalBounds();
						const sf::Vector2f playerBotRight(playerBounds.left + playerBounds.width, playerBounds.top + playerBounds.height);

						if (playerBotRight.x < spikeBounds.left + spikeBounds.width / 2
							&& playerBotRight.y <= spikeBounds.top + spikeBounds.height
							&& playerBotRight.y > -SQRT3*(playerBotRight.x - spikeBounds.left) + spikeBounds.top + spikeBounds.height)
						{
							died(entity->getPosition(), coll.intersection);
							return;
						}
					}
					else if (coll.side == CollisionInfo::Right)
					{
						const sf::FloatRect spikeBounds = entity->getGlobalBounds(), playerBounds = m_player.getGlobalBounds();
						const sf::Vector2f playerBotLeft(playerBounds.left, playerBounds.top + playerBounds.height);

						if (playerBotLeft.x > spikeBounds.left + spikeBounds.width / 2
							&& playerBotLeft.y <= spikeBounds.top + spikeBounds.height
							&& playerBotLeft.y > SQRT3*(playerBotLeft.x - (spikeBounds.left + spikeBounds.width)) + spikeBounds.top + spikeBounds.height)
						{
							died(entity->getPosition(), coll.intersection);
							return;
						}
					}
					else if (coll.side != CollisionInfo::None)
					{
						died(entity->getPosition(), coll.intersection);
						return;
					}
				}*/
					const sf::FloatRect spikeBounds = entity->getGlobalBounds(), playerBounds = m_player.getGlobalBounds();
					const sf::Vector2f playerBotRight(playerBounds.left + playerBounds.width, playerBounds.top + playerBounds.height);
					const sf::Vector2f playerBotLeft(playerBounds.left, playerBounds.top + playerBounds.height);

					if ((playerBotRight.x < spikeBounds.left + spikeBounds.width / 2
						&& playerBotRight.y <= spikeBounds.top + spikeBounds.height
						&& playerBotRight.y > -SQRT3*(playerBotRight.x - spikeBounds.left) + spikeBounds.top + spikeBounds.height)
						|| (playerBotLeft.x > spikeBounds.left + spikeBounds.width / 2
							&& playerBotLeft.y <= spikeBounds.top + spikeBounds.height
							&& playerBotLeft.y > SQRT3*(playerBotLeft.x - (spikeBounds.left + spikeBounds.width)) + spikeBounds.top + spikeBounds.height)
						|| (playerBotLeft.x < spikeBounds.left + spikeBounds.width / 2
							&& playerBotLeft.y <= spikeBounds.top + spikeBounds.height
							&& playerBotLeft.y > -SQRT3*(playerBotLeft.x - spikeBounds.left) + spikeBounds.top + spikeBounds.height)
						|| (playerBotRight.x > spikeBounds.left + spikeBounds.width / 2
							&& playerBotRight.y <= spikeBounds.top + spikeBounds.height
							&& playerBotRight.y > SQRT3*(playerBotRight.x - (spikeBounds.left + spikeBounds.width)) + spikeBounds.top + spikeBounds.height))
					{
						died(entity->getPosition(), coll.intersection);
						return;
					}
				}
				else if (coll.side != CollisionInfo::None)
				{
					died(entity->getPosition(), coll.intersection);
					return;
				}
			}
			else if (entity->getType() == Entities::Platform)
			{
				if (coll.side == CollisionInfo::Top || coll.side == CollisionInfo::Right)
				{
					m_player.move({ 0.f,-coll.intersection.y });
					m_player.setToRest();
				}
				else if (coll.side == CollisionInfo::Bottom && m_player.getType() == Player::Flyer)
				{
					m_player.move({ 0.f,coll.intersection.y });
					m_player.setToRest();
				}
				else if (coll.side == CollisionInfo::Left)
				{
					if (coll.intersection.y < 1.f)
					{
						m_player.move({ 0.f,-coll.intersection.y });
						m_player.setToRest();
						return;
					}
					else
					{
						died(entity->getPosition(), coll.intersection);
						return;
					}
				}
				else if (coll.side != CollisionInfo::None)
				{
					died(entity->getPosition(), coll.intersection);
					return;
				}
			}
			else if (entity->getType() == Entities::Portal)
			{
				Portal* portal = (Portal*)entity.get();

				if (coll.side != CollisionInfo::None && !portal->passed) portal->passed = true;
				else if (portal->passed && coll.side == CollisionInfo::None)
				{
					portal->passed = false;
					m_player.changeType((Player::Type)portal->playerType, *getContext().textures);
				}
			}
		}
	}
}

void GameState::died(const sf::Vector2f & otherPos, const sf::Vector2f & intersection)
{
	getContext().music->stop();
	m_trail.clearTrail();

	const sf::Vector2f pos = m_player.getPosition(), halfSize = m_player.getSize() / 2.f, halfIntrsc = intersection /2.f;
	sf::Vector2f collSource;
	if (otherPos.y < m_player.getPosition().y)
	{
		if (otherPos.x < m_player.getPosition().x) collSource = pos - halfSize + halfIntrsc;
		else collSource = m_player.getPosition() + sf::Vector2f(halfSize.x, -halfSize.y) - halfIntrsc;
	}
	else
	{
		if (otherPos.x < m_player.getPosition().x) collSource = m_player.getPosition() + sf::Vector2f(-halfSize.x, -halfSize.y) + halfIntrsc;
		else collSource = pos + halfSize - halfIntrsc;
	}

	*getContext().deathSource = collSource;
	requestStackPush(States::DeathState);
	m_player.setAlive(false);
}

const sf::FloatRect GameState::getViewBounds() const
{
	const sf::Vector2f size = m_view.getSize();
	return sf::FloatRect(m_view.getCenter() - size / 2.f, size);
}

void GameState::resetPlayer()
{
	m_player.setAlive(true);
	m_player.setPosition(*getContext().newStart);
	m_player.changeType(Player::Jumper, *getContext().textures);
	m_player.reset();
	m_trail.clearTrail();
	m_view.setCenter(m_player.getPosition());
	getContext().music->stop();
	getContext().music->play();
	getContext().music->setPlayingOffset(sf::seconds(*getContext().musicStart));
}
