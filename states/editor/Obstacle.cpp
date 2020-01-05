#include "Obstacle.h"
#include <iostream>

const Collision Obstacle::collision(sf::RectangleShape & otherRect, const float &correction) const
{

	sf::Vector2f half = sprite.getSize() / 2.f, otherHalf = otherRect.getSize() / 2.f;
	sf::Vector2f other = otherRect.getPosition(), pos = sprite.getPosition();
	float xDist = other.x - pos.x, yDist = other.y - pos.y;

	sf::Vector2f collisionBounds;

	if (std::abs(xDist) < half.x + otherHalf.x
		&& std::abs(yDist) < half.y + otherHalf.y)
	{
		if (std::abs(xDist) > std::abs(yDist))
		{
			if (std::abs(yDist) < half.y + otherHalf.y - 5.f)		// tolerance
			{
				if (xDist > 0.f) return{ collisionBounds,Collision::Right };
				return{ collisionBounds,Collision::Left };
			}

			if (xDist > 0.f) otherRect.move(-correction, 0.f);
			otherRect.move(correction, 0.f);

			return{ collisionBounds,Collision::None };
		}
		else
		{
			if (yDist > 0.f)
			{
				otherRect.move(0.f, correction);
				return{ collisionBounds,Collision::Bottom };
			}
			otherRect.move(0.f,-correction);
			return{ collisionBounds,Collision::Top };
		}
	}
	return{ collisionBounds,Collision::None };
}
