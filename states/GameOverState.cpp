#include "GameOverState.h"
#include "../utils/ResourceHolder.h"

GameOverState::GameOverState(StateStack & stack, Context & context)
	: State(stack, context),
	m_overlay((sf::Vector2f)context.window->getSize()),
	m_text("Level Complete", context.fonts->get(Fonts::Kaushan), 80U),
	m_text2("Press [R] to restart", context.fonts->get(Fonts::Charm), 35U)
{
	m_text.setPosition((sf::Vector2f)context.window->getSize() / 2.f - sf::Vector2f(0.f, 40.f));
	m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
	m_text.setFillColor(sf::Color::White);
	m_text2.setPosition((sf::Vector2f)context.window->getSize() / 2.f + sf::Vector2f(0.f, 40.f));
	m_text2.setOrigin(m_text2.getGlobalBounds().width / 2, m_text2.getGlobalBounds().height / 2);
	m_text2.setFillColor(sf::Color::White);
	m_overlay.setFillColor(sf::Color(0, 0, 0, 150));
}

void GameOverState::draw()
{
	auto &window = getContext().window;
	window->setView(window->getDefaultView());
	window->draw(m_overlay);
	window->draw(m_text);
	window->draw(m_text2);
}

const bool GameOverState::update(const float & deltaTime)
{
	return false;
}

const bool GameOverState::handleEvent(const sf::Event & evnt)
{
	if (evnt.type == sf::Event::KeyPressed && evnt.key.code == sf::Keyboard::R)
	{
		*getContext().requestRestart = true;
		requestStackPop();
	}
	return false;
}
