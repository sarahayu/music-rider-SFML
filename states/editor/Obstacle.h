#pragma once
#include <SFML\Graphics.hpp>

struct Collision
{
	enum Type
	{
		Top, Right, Bottom, Left, None
	};

	sf::Vector2f bounds;
	Type type;
};

class Obstacle
{
public:
	enum Type
	{
		Block,
		UpSpike,
		DownSpike,
		RightSpike,
		LeftSpike
	};


	const Collision collision(sf::RectangleShape &other, const float &correction) const;

	sf::RectangleShape sprite;
	Type type;
};