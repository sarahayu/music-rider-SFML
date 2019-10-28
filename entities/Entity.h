#pragma once
#include <SFML\Graphics.hpp>
#include <memory>
#include "Entities.h"

class Entity : public sf::Drawable
{
public:
	typedef std::unique_ptr<Entity> Ptr;

	virtual const std::string serialize() const = 0;

	const sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f &position);
	const sf::FloatRect getGlobalBounds() const;
	const sf::Vector2f getSize() const;

	const Entities::Type getType() const;

protected:
	Entity(const Entities::Type &type);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::RectangleShape& getSprite();
	const sf::RectangleShape& getSprite() const;

private:
	const Entities::Type m_type;
	sf::RectangleShape m_sprite;
};