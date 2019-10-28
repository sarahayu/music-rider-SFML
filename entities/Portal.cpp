#include "Portal.h"
#include "../states/Player.h"
#include "../utils/ResourceHolder.h"
#include <sstream>

Portal::Portal(const sf::Vector2f &position, TextureHolder &textures, const int &_playerType)
	: Entity(Entities::Portal), playerType(getPlayerType(_playerType))
{
	getSprite().setTexture(&textures.get(Textures::Portal));
	getSprite().setSize({ 30.f,90.f });
	getSprite().setOrigin(15.f, 45.f);
	getSprite().setPosition(position);
}

const std::string Portal::serialize() const
{
	std::stringstream serial;
	serial << (int)getType()
		<< " " << playerType
		<< " " << getPosition().x
		<< " " << getPosition().y;
	return serial.str();
}

const int Portal::getPlayerType(const int & type)
{
	assert(type < Player::TypeCount);
	return type;
}
