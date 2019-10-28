#pragma once
#include <SFML\Graphics.hpp>
#include "../../entities/Obstacle.h"

class Tool : public sf::Drawable
{
public:
	typedef std::unique_ptr<Tool> Ptr;
	virtual ~Tool();

	virtual const void update(const sf::RenderWindow &window, std::vector<Entity::Ptr> &obstacles, const bool &isClicked) = 0;
};