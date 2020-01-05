#pragma once
#include <SFML\Graphics.hpp>
#include "Entities.h"
#include "CollisionInfo.h"

namespace Collision
{
	enum Type
	{
		Good,
		Bad,
		None
	};
}

class Entity
{
public:
	Entity(const Entities::Type &type);

	void draw(sf::RenderWindow &window) const;
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const sf::Vector2f getSize() const;
	void setPosition(const sf::Vector2f &position);

	const Entities::Type getType() const;		// for file writing
protected:

	const sf::RectangleShape& getSprite() const;
	sf::RectangleShape& getSprite();
	static const CollisionInfo getCollision(const sf::FloatRect &thisBounds, const sf::FloatRect &otherBounds);

private:
	const Entities::Type m_type;
	sf::RectangleShape m_sprite;
};