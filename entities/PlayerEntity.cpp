#include "PlayerEntity.h"
#include "../utils/ResourceHolder.h"
#include "DataTables.h"
#include <iostream>

namespace
{
	std::vector<PlayerData> Table = initializePlayerData();
}

PlayerEntity::PlayerEntity(const Type &type, TextureHolder &textures, const sf::Vector2f &position)
	: Entity(Entities::Player), m_type(type), m_gravity(Table[type].gravity), m_launchPower(Table[type].launchPower), m_textures(getTextures(textures))
{
	std::cout << "\nType: " << m_type;
	getSprite().setTexture(&textures.get(Table[type].texture));

	const sf::Vector2f size = Table[type].size;
	getSprite().setSize(size);
	getSprite().setOrigin(size / 2.f);
	getSprite().setPosition(position);
}

const PlayerEntity::Type PlayerEntity::getPlayerType() const
{
	return m_type;
}

const float PlayerEntity::getGravity() const
{
	return m_gravity;
}

const float PlayerEntity::getLaunchPower() const
{
	return m_launchPower;
}

void PlayerEntity::rotate(const float & rotation)
{
	getSprite().rotate(rotation);
}

void PlayerEntity::setRotation(const float & rotation)
{
	getSprite().setRotation(rotation);
}

const float PlayerEntity::getRotation() const
{
	return getSprite().getRotation();
}

void PlayerEntity::move(const sf::Vector2f & movement)
{
	getSprite().move(movement);
}

void PlayerEntity::changeType(const Type & type)
{
	std::cout << "\n2Type: " << m_type;
	m_type = type;

	getSprite().setTexture(&m_textures[type]);

	const sf::Vector2f size = Table[type].size;
	getSprite().setSize(size);
	getSprite().setOrigin(size / 2.f);
	setRotation(0.f);

	m_gravity = Table[type].gravity;
	m_launchPower = Table[type].launchPower;
}

const std::vector<sf::Texture> PlayerEntity::getTextures(TextureHolder & textures)
{
	std::vector<sf::Texture> texs(TypeCount);
	for (int i = 0; i < TypeCount; i++) texs[i] = textures.get(Table[(Type)i].texture);
	return texs;
}
