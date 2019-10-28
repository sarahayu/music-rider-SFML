#pragma once
#include <SFML\Graphics.hpp>
#include "State.h"
#include "../utils/Resources.h"
#include "../utils/ResourceHolder.h"
#include "Player.h"
#include "PlayerTrail.h"
#include "RollingSprite.h"

struct CollisionInfo;

class GameState : public State
{
public:
	GameState(StateStack &stack, Context &context);

	virtual void draw();
	virtual const bool update(const float &deltaTime);
	virtual const bool handleEvent(const sf::Event &evnt);

private:
	enum Layer { Background, Air, PlayerLayer, Terrain, LayerCount };

	void predictCollision();	// for jumper spinning effect
	void checkCollisions();
	void died(const sf::Vector2f &otherPos, const sf::Vector2f &intersection);

	const sf::FloatRect getViewBounds() const;
	void resetPlayer();

	Player m_player;
	PlayerTrail m_trail;
	sf::View m_view;
	RollingSprite m_background;
	RollingSprite m_ground;
	sf::RectangleShape m_shadow, m_finishLine;
	std::vector<std::vector<sf::Drawable*>> m_layers;

	bool m_gameOver = false;
};