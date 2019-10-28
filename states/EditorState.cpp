#include "EditorState.h"
#include "State.h"
#include "editor\Placer.h"
#include "editor\Eraser.h"
#include "../utils/ResourceHolder.h"
#include "../entities/Entities.h"
#include "../Settings.h"
#include "../entities/Obstacle.h"
#include "../entities/Portal.h"
#include "../entities/Portal.h"
#include "../states/Player.h"
#include <iostream>
#include <SFML\Audio.hpp>

const float PAN_SPEED = 500.f;

EditorState::EditorState(StateStack & stack, Context & context)
	: State(stack, context),
	m_view(*context.newStart, (sf::Vector2f)context.window->getSize()),
	m_newstart(10.f)
{
	for (int i = 0, numKey = sfk::Num1; i < Obstacle::TypeCount; i++, numKey++)
	{
		m_buttonMap[(sfk::Key)numKey] = [this, i](const sf::Vector2f &location) {
			return std::make_unique<Placer<Obstacle>>(std::make_unique<Obstacle>((Obstacle::Type)i, location, *getContext().textures));
		};
	}

	m_buttonMap[sfk::O] = [this](const sf::Vector2f &location) {
		return std::make_unique<Placer<Portal>>(std::make_unique<Portal>(location, *getContext().textures, Player::Flyer));
	};
	m_buttonMap[sfk::P] = [this](const sf::Vector2f &location) {
		return std::make_unique<Placer<Portal>>(std::make_unique<Portal>(location, *getContext().textures, Player::Jumper));
	};

	m_buttonMap[sfk::E] = [this](const sf::Vector2f &location) {
		return std::make_unique<Eraser>(*getContext().textures, location);
	};

	m_activeTool = m_buttonMap[sfk::Num1]((sf::Vector2f)sf::Mouse::getPosition(*getContext().window));
	m_newstart.setFillColor(sf::Color::Red);
	m_newstart.setPosition(*context.newStart);
	m_newstart.setOrigin(10.f, 10.f);
}

EditorState::~EditorState()
{
	std::fstream file("resources/" + *getContext().levelName + Settings::SUFFIX, std::ios::in);

	std::string musicFileStr, tempo;
	file >> musicFileStr >> tempo;

	file.close();

	file.open("resources/" + *getContext().levelName + Settings::SUFFIX, std::ios::out | std::ios::trunc);
	file << musicFileStr << " " << tempo << " ";
	for (const auto &entity : *getContext().entities) file << entity->serialize() << " ";
	file.close();
}

void EditorState::draw()
{
	auto window = getContext().window;

	window->clear(sf::Color(248, 238, 194));

	window->setView(m_view);

	const float bpm = *getContext().tempo;
	float xDist = Settings::X_SPEED / (bpm / 60);
	float left = std::ceil((m_view.getCenter().x - m_view.getSize().x / 2) / xDist) * xDist;

	sf::RectangleShape barLine({ 2.f,m_view.getSize().y });
	barLine.setFillColor(sf::Color::Red);

	while (left < m_view.getCenter().x + m_view.getSize().x / 2)
	{
		if (std::fmod(left, 4 * xDist) <= 0.01f) barLine.setFillColor(sf::Color(255, 0, 0));
		else barLine.setFillColor(sf::Color(255, 0, 0, 50));
		barLine.setPosition(left, m_view.getCenter().y - m_view.getSize().y / 2);
		window->draw(barLine);
		left += xDist;
	}

	sf::RectangleShape maxFlyerHeight({ m_view.getSize().x,2.f });
	maxFlyerHeight.setPosition(m_view.getCenter().x - m_view.getSize().x / 2, -267.78f);		// TODO move to settings
	maxFlyerHeight.setFillColor(sf::Color(0, 0, 0, 50));
	window->draw(maxFlyerHeight);

	sf::RectangleShape ground((sf::Vector2f)(window->getSize()));
	ground.setFillColor(sf::Color(47, 87, 47));
	ground.setPosition(m_view.getCenter().x - m_view.getSize().x / 2, 0.f);	

	for (const auto &obstacle : *getContext().entities) window->draw(*obstacle);

	window->draw(m_newstart);
	window->draw(*m_activeTool);
	window->draw(ground);
}

const bool EditorState::update(const float & deltaTime)
{
	sf::Vector2f viewMovement;

	typedef sf::Keyboard sfk;

	if (sfk::isKeyPressed(sfk::W)) viewMovement.y -= PAN_SPEED * deltaTime;
	if (sfk::isKeyPressed(sfk::S)) viewMovement.y += PAN_SPEED * deltaTime;
	if (sfk::isKeyPressed(sfk::A)) viewMovement.x -= PAN_SPEED * deltaTime;
	if (sfk::isKeyPressed(sfk::D)) viewMovement.x += PAN_SPEED * deltaTime;

	if (sfk::isKeyPressed(sfk::LControl)) viewMovement *= 4.f;

	m_view.move(viewMovement);

	getContext().window->setView(m_view);

	m_activeTool->update(*getContext().window, *getContext().entities, sf::Mouse::isButtonPressed(sf::Mouse::Left));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		const auto &newStart = getContext().window->mapPixelToCoords(sf::Mouse::getPosition(*getContext().window));
		m_newstart.setPosition(newStart);
		*getContext().newStart = m_newstart.getPosition();
		*getContext().musicStart = newStart.x / Settings::X_SPEED;
	}

	return false;
}

const bool EditorState::handleEvent(const sf::Event & evnt)
{
	if (evnt.type == sf::Event::KeyPressed)
	{
		const auto &newType = m_buttonMap.find(evnt.key.code);
		const sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(*getContext().window);

		if (newType != m_buttonMap.end())
			m_activeTool = newType->second(mousePos);
		else
		{
			switch (evnt.key.code)
			{
			case sfk::G:
				requestStackPop();
				requestStackPush(States::GameState);
				break;
			}
		}
	}
	return false;
}
