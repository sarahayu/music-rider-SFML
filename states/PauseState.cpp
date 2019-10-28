#include "PauseState.h"
#include "../utils/ResourceHolder.h"
#include <SFML\Audio.hpp>

PauseState::PauseState(StateStack & stack, Context & context)
	: State(stack, context),
	m_overlay((sf::Vector2f)context.window->getSize()),
	m_text("Paused", context.fonts->get(Fonts::Kaushan), 80U), 
	m_text2("Press [Esc] to resume", context.fonts->get(Fonts::Charm), 35U)
{
	m_text.setPosition((sf::Vector2f)context.window->getSize() / 2.f - sf::Vector2f(0.f,40.f));
	m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
	m_text.setFillColor(sf::Color::White);
	m_text2.setPosition((sf::Vector2f)context.window->getSize() / 2.f + sf::Vector2f(0.f, 40.f));
	m_text2.setOrigin(m_text2.getGlobalBounds().width / 2, m_text2.getGlobalBounds().height / 2);
	m_text2.setFillColor(sf::Color::White);
	m_overlay.setFillColor(sf::Color(0, 0, 0, 150));
}

void PauseState::draw()
{
	auto &window = getContext().window;
	window->setView(window->getDefaultView());
	window->draw(m_overlay);
	window->draw(m_text);
	window->draw(m_text2);
}

const bool PauseState::update(const float & deltaTime)
{
	return false;
}

const bool PauseState::handleEvent(const sf::Event & evnt)
{
	if (evnt.type == sf::Event::KeyPressed && evnt.key.code == sf::Keyboard::Escape)
	{
		getContext().music->play();
		requestStackPop();
	}
	return false;
}
