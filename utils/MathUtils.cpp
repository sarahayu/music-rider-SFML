#include "MathUtils.h"

const float mu::distanceSquared(const sf::Vector2f & first, const sf::Vector2f & second)
{
	const float x = std::abs(first.x - second.x), y = std::abs(first.y - second.y);
	return x*x + y*y;
}

const CollisionInfo mu::getCollision(const sf::FloatRect & thisBounds, const sf::FloatRect & otherBounds)
{
	const sf::Vector2f	otherPos(otherBounds.left + otherBounds.width / 2, otherBounds.top + otherBounds.height / 2),
		thisPos(thisBounds.left + thisBounds.width / 2, thisBounds.top + thisBounds.height / 2);
	const float		deltaX = otherPos.x - thisPos.x,
		deltaY = otherPos.y - thisPos.y;

	const sf::Vector2f otherHalf(otherBounds.width / 2, otherBounds.height / 2),
		thisHalf(thisBounds.width / 2, thisBounds.height / 2);
	const float minDistX = otherHalf.x + thisHalf.x,
		minDistY = otherHalf.y + thisHalf.y;

	const float interesectX = std::abs(deltaX) - (minDistX),
		interesectY = std::abs(deltaY) - (minDistY);


	CollisionInfo::Side side;

	if (interesectX < 0.f && interesectY < 0.f)
	{
		if (interesectY > interesectX)
		{
			if (deltaY < 0.f) side = CollisionInfo::Top;
			else side = CollisionInfo::Bottom;
		}
		else
		{
			if (deltaX < 0.f) side = CollisionInfo::Left;
			else side = CollisionInfo::Right;
		}
	}
	else side = CollisionInfo::None;

	return{ side, sf::Vector2f(-interesectX, -interesectY) };
}
