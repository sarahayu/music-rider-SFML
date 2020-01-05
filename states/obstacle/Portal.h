#pragma once
#include <SFML\Graphics.hpp>
#include "Entity.h"

class ResourceHolder;
class Player;

class Portal : public Entity
{
public:
	Portal(const sf::Vector2f &position, ResourceHolder &resources);

	const bool checkCollided(const Player &other);
	const bool passedThrough() const;
	void doneWith();

private:
	bool m_passed = false;
};