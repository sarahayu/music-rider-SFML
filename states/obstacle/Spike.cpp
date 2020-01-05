#include "Spike.h"
#include "../player/Player.h"
#include "../../utils/ResourceHolder.h"

Spike::Spike(const sf::Vector2f & location, ResourceHolder & resources, const Rotation &rotation)
	: Obstacle(getSpikeSprite(location, resources, rotation), getType(rotation))
{
}

const Collision::Type Spike::checkCollision(Player & player) const
{
	return getCollision(getSprite().getGlobalBounds(), player.getGlobalBounds()).side == CollisionInfo::None ? Collision::None : Collision::Bad;
}

const sf::RectangleShape Spike::getSpikeSprite(const sf::Vector2f & location, ResourceHolder & resources, const Rotation & rotation)
{
	sf::RectangleShape spike({ 30.f,30.f });
	spike.setTexture(resources.get(Texture::Triangle));
	spike.setOrigin(15.f, 15.f);
	spike.setPosition(location);
	spike.setRotation((int)rotation * 90.f);
	return spike;
}

const Entities::Type Spike::getType(const Rotation & rotation)
{
	switch (rotation)
	{
	case Up: return Entities::UpSpike;
	case Right: return Entities::RightSpike;
	case Down: return Entities::DownSpike;
	}
	return Entities::LeftSpike;
}
