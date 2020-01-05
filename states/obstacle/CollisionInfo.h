#pragma once

struct CollisionInfo
{
	enum Side { Top, Right, Bottom, Left, None };

	Side side;
	sf::Vector2f intersection;
};