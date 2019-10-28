#include "Entity.h"
#include <iostream>

Entity::Entity(const Entities::Type & type)
	: m_type(type)
{
}

void Entity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	const auto &view = target.getView();
	const auto &size = view.getSize();
	
	if (getPosition().x > view.getCenter().x - size.x/2 + 10.f
		&& getPosition().x < view.getCenter().x + size.x / 2 - 10.f) target.draw(m_sprite, states);
}

const sf::Vector2f Entity::getPosition() const
{
	return m_sprite.getPosition();
}

void Entity::setPosition(const sf::Vector2f & position)
{
	m_sprite.setPosition(position);
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

const sf::Vector2f Entity::getSize() const
{
	return m_sprite.getSize();
}

const Entities::Type Entity::getType() const
{
	return m_type;
}

sf::RectangleShape & Entity::getSprite()
{
	return m_sprite;
}

const sf::RectangleShape & Entity::getSprite() const
{
	return m_sprite;
}
