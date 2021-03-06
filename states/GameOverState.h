#pragma once
#include <SFML\Graphics.hpp>
#include "State.h"

class GameOverState : public State
{
public:
	GameOverState(StateStack &stack, Context &context);

	virtual void draw();
	virtual const bool update(const float &deltaTime);
	virtual const bool handleEvent(const sf::Event &evnt);

private:
	sf::RectangleShape m_overlay;
	sf::Text m_text, m_text2;
};