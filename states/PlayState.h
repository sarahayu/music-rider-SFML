#pragma once
#include "State.h"
#include <functional>
#include "player\Player.h"

class PlayState : public State
{
public:
	PlayState(StateStack &stack, Context &context);

	virtual void draw();
	virtual const bool update(const float &deltaTime);
	virtual const bool handleEvent(const sf::Event &evnt);

private:

	void resetPlayer();

	Player::Ptr m_player;
	sf::View m_view;
	int m_playerType = 0;

	sf::Vector2f m_nextCollision;
	bool m_deadNextRest = false;
};