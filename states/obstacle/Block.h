#pragma once
#include "Obstacle.h"

class ResourceHolder;

class Block : public Obstacle
{
public:
	Block(const sf::Vector2f &location, ResourceHolder &resources);

	const Collision::Type checkCollision(Player &player) const;

private:
	static const sf::RectangleShape getBlockSprite(const sf::Vector2f &location, ResourceHolder &resources);
};