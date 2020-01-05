#include "Obstacle.h"
#include "../player/Player.h"
#include <iostream>
#include <sstream>

const bool operator<(const sf::Vector2f & v, const float & f)
{
	return v.x < f && v.y < f;
}

const bool operator>(const sf::Vector2f & v, const float & f)
{
	return v.x > f && v.y > f;
}

Obstacle::Obstacle(const sf::RectangleShape &sprite, const Entities::Type & type)
	: Entity(type)
{
	getSprite() = sprite;
}
