#pragma once
#include "Obstacle.h"

class ResourceHolder;

class Spike : public Obstacle
{
public:
	enum Rotation { Up, Right, Left, Down };

	Spike(const sf::Vector2f &location, ResourceHolder &resources, const Rotation &rotation);

	const Collision::Type checkCollision(Player &player) const;

private:
	static const sf::RectangleShape getSpikeSprite(const sf::Vector2f &location, ResourceHolder &resources, const Rotation &rotation);
	static const Entities::Type getType(const Rotation& rotation);
};