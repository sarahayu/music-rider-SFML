#pragma once
#include <SFML\Graphics.hpp>

struct CollisionInfo
{
	enum Side { Top, Right, Bottom, Left, None };

	Side side;
	sf::Vector2f intersection;
};

namespace mu
{
	const float distanceSquared(const sf::Vector2f &first, const sf::Vector2f &second);
	const CollisionInfo getCollision(const sf::FloatRect & thisBounds, const sf::FloatRect & otherBounds);
}