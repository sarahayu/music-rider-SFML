#pragma once
#include "Obstacle.h"

class ResourceHolder;
namespace Texture { enum ID; }

class Platform : public Obstacle
{
public:
	enum Type
	{
		Thick,
		Thin
	};

	Platform(const Type &type, ResourceHolder &resources, const sf::Vector2f &position = {});
	const Collision::Type collision(Player &player) const;
private:
	static const sf::RectangleShape getSprite()
	static const sf::Vector2f getPlatformSize(const Type &type);
	static const Texture::ID getTexture(const Type &type);
};