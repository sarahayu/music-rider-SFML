#pragma once
#include "Entity.h"
#include "../utils/Resources.h"

class Portal : public Entity
{
public:
	Portal(const sf::Vector2f &position, TextureHolder &textures, const int &playerType);

	virtual const std::string serialize() const;

	bool passed = false;
	const int playerType;

private:
	static const int getPlayerType(const int &type);
};