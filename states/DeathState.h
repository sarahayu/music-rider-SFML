#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <fstream>
#include <functional>
#include "State.h"

class DeathState : public State
{
public:
	DeathState(StateStack &stack, Context &context);

	virtual void draw();
	virtual const bool update(const float &deltaTime);
	virtual const bool handleEvent(const sf::Event &evnt);

private:
	float m_totalTime = 0.f;
	float m_elapsedTime = 0.f;

	const sf::Vector2f m_frameSize;
	const float m_frameDuration;
	sf::RectangleShape m_sprite;
	bool m_done = false;

};