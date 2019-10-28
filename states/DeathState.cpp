#include "DeathState.h"
#include "../utils/ResourceHolder.h"
#include "Player.h"
#include <iostream>

DeathState::DeathState(StateStack & stack, Context & context)
	: State(stack, context),
	m_frameSize((float)context.textures->get(Textures::InkSplat).getSize().x / 33, context.textures->get(Textures::InkSplat).getSize().y), m_frameDuration(2.f / 33), m_sprite({ 90.f,90.f })
{
	m_sprite.setOrigin(m_sprite.getSize() / 2.f);
	m_sprite.setPosition(*context.deathSource);
	auto &ink = context.textures->get(Textures::InkSplat);
	ink.setSmooth(true);
	m_sprite.setTexture(&ink);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameSize.x, m_frameSize.y));

	context.explode->play();
}

void DeathState::draw()
{
	getContext().window->draw(m_sprite);
}

const bool DeathState::update(const float & deltaTime)
{
	m_totalTime += deltaTime;
	m_elapsedTime += deltaTime;

	while (!m_done && m_elapsedTime > m_frameDuration)
	{
		m_elapsedTime -= m_frameDuration;
		if (m_sprite.getTextureRect().left < m_sprite.getTexture()->getSize().x - m_sprite.getTextureRect().width) m_sprite.setTextureRect(sf::IntRect(m_sprite.getTextureRect().left + m_frameSize.x, 0, m_frameSize.x, m_frameSize.y));
		else m_done = true;
	}

	if (m_totalTime >= 1.f)
	{
		*getContext().requestRestart = true;
		requestStackPop();
	}


	return false;
}

const bool DeathState::handleEvent(const sf::Event & evnt)
{
	return false;
}
