#include "Obstacle.h"
#include "../utils/ResourceHolder.h"
#include "../DataTables.h"
#include <sstream>

namespace
{
	std::vector<ObstacleData> Table = initializeObstacleData();
}

Obstacle::Obstacle(const Type & type, const sf::Vector2f &position, TextureHolder & textures)
	: Entity(getObstacleCategory(type)), m_type(type)
{
	getSprite().setTexture(&textures.get(Table[type].texture));
	getSprite().setRotation(Table[type].rotation);
	getSprite().setPosition(position);

	const sf::Vector2f size = Table[type].size;
	getSprite().setSize(size);
	getSprite().setOrigin(size / 2.f);
}

const std::string Obstacle::serialize() const
{
	std::stringstream serial;
	serial << (int)getType()
		<< " " << m_type
		<< " " << getPosition().x
		<< " " << getPosition().y;
	return serial.str();
}

const Obstacle::Type Obstacle::getObstacleType()
{
	return m_type;
}

const Entities::Type Obstacle::getObstacleCategory(const Type &type)
{
	switch (type)
	{
	case ThickPlatform:
	case ThinPlatform:
		return Entities::Platform;
	}
	return Entities::Spike;
}
