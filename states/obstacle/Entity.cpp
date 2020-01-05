#include "Entity.h"

const sf::RectangleShape & Entity::getSprite() const
{
	return m_sprite;
}

sf::RectangleShape & Entity::getSprite()
{
	return m_sprite;
}

const CollisionInfo Entity::getCollision(const sf::FloatRect & thisBounds, const sf::FloatRect & otherBounds)
{
	const sf::Vector2f	otherPos(otherBounds.left + otherBounds.width / 2, otherBounds.top + otherBounds.height / 2),
		thisPos(thisBounds.left + thisBounds.width / 2, thisBounds.top + thisBounds.height / 2);
	const float		deltaX = otherPos.x - thisPos.x,
		deltaY = otherPos.y - thisPos.y;

	if (deltaX*deltaX + deltaY*deltaY > 900.f) return{ CollisionInfo::None };

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

Entity::Entity(const Entities::Type & type)
	: m_type(type)
{
}

void Entity::draw(sf::RenderWindow & window) const
{
	window.draw(m_sprite);
}

const sf::Vector2f Entity::getPosition() const
{
	return m_sprite.getPosition();
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

const sf::Vector2f Entity::getSize() const
{
	return m_sprite.getSize();
}

void Entity::setPosition(const sf::Vector2f & position)
{
	m_sprite.setPosition(position);
}

const Entities::Type Entity::getType() const
{
	return m_type;
}
