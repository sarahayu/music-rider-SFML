#pragma once
#include <memory>
#include "Entity.h"

class Player;

class Obstacle : public Entity
{
public:
	typedef std::shared_ptr<Obstacle> Ptr;

	Obstacle(const sf::RectangleShape &sprite, const Entities::Type &type);

	virtual const Collision::Type checkCollision(Player &player) const = 0;

};