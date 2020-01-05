#include "PlayState.h"
#include "obstacle\Obstacle.h"
#include "../utils/ResourceHolder.h"
#include "Settings.h"
#include "player\Jumper.h"
#include "player\Flyer.h"
#include <SFML\Audio.hpp>
#include <fstream>
#include <iostream>

int jumpstarted = 0;

PlayState::PlayState(StateStack & stack, Context & context)
	: State(stack, context),
	m_view({}, { (sf::Vector2f)context.window->getSize() / 1.5f }), m_player(std::make_shared<Flyer>(*context.resources, sf::Vector2f{ 0.f, -15.f })), m_playerType(1)
{
	m_view.setCenter(m_player->getPosition());
	context.music->play();
}

void PlayState::draw()
{
	auto window = getContext().window;

	window->clear(sf::Color(248, 238, 194));

	sf::RectangleShape ground({ m_view.getSize().x,m_view.getSize().y / 2 });
	ground.setFillColor(sf::Color(47, 87, 47));
	ground.setPosition(m_view.getCenter().x - m_view.getSize().x / 2, 0.f);

	window->setView(m_view);

	window->draw(ground);
	m_player->draw(*window);
	for (const auto &portal : *getContext().portals) portal.draw(*window);
	for (const auto &obstacle : *getContext().obstacles) obstacle->draw(*window);
}

const bool PlayState::update(const float & deltaTime)
{
	m_player->input();
	m_player->update(deltaTime);

	const float bottomEdge = m_player->getPosition().y + m_player->getSize().y / 2;
	if (bottomEdge > 0.f)
	{
		m_player->stopVelocity();
		m_player->move({ 0.f,std::min(0.f,-bottomEdge + 0.1f)*0.8f });
	}

	for (const auto &obstacle : *getContext().obstacles)
		if (obstacle->checkCollision(*m_player.get()) == Collision::Bad) resetPlayer();

	for (auto &portal : *getContext().portals)
		if (!portal.checkCollided(*m_player.get()) && portal.passedThrough())
		{
			if (m_playerType == 0)
			{
				std::cout << "\nChanging to fluer...";
				m_playerType = 1;
				m_player = std::make_shared<Flyer>(*getContext().resources, m_player->getPosition());
			}
			else
			{
				std::cout << "\nChanging to jumper...";
				m_playerType = 0;
				m_player = std::make_shared<Jumper>(*getContext().resources, m_player->getPosition(), getContext().obstacles);
			}
			portal.doneWith();
		}


	float oldY = m_view.getCenter().y;
	m_view.setCenter(m_player->getPosition().x, oldY);

	float yDif = oldY - m_player->getPosition().y;

	if (m_player->getVelocity() == 0.f || std::abs(yDif) > m_view.getSize().y / 6) m_view.move(0.f, -(oldY - m_player->getPosition().y)*deltaTime);

	//m_player.update(deltaTime);

	return true;
}

const bool PlayState::handleEvent(const sf::Event & evnt)
{
	typedef sf::Keyboard sfk;

	if (evnt.type == sf::Event::KeyPressed)
	{
		switch (evnt.key.code)
		{
		case sfk::E:
			requestStackPop();
			requestStackPush(States::EditorState);
			getContext().music->stop();
			break;
		case sfk::R:
			resetPlayer();
			break;
		}
	}

	return true;
}

void PlayState::resetPlayer()
{
	m_player->stopVelocity();
	m_player->setPosition({ 15.f,-15.f });
	getContext().music->play();		// restart music
}
