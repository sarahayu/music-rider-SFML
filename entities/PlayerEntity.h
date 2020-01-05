#pragma once
#include "Entity.h"
#include "../utils/Resources.h"

class PlayerEntity : public Entity
{
public:
	enum Type { Jumper, Flyer, TypeCount };

	PlayerEntity(const Type &type, TextureHolder &textures, const sf::Vector2f &position);

	const Type getPlayerType() const;
	const float getGravity() const;
	const float getLaunchPower() const;

	void rotate(const float &rotation);
	void setRotation(const float &rotation);
	const float getRotation() const;
	void move(const sf::Vector2f &movement);
	void changeType(const Type &type);

	float velocity = 0.f;

private:
	static const std::vector<sf::Texture> getTextures(TextureHolder &textures);
	const std::vector<sf::Texture> m_textures;

	Type m_type;
	float m_gravity, m_launchPower;
};