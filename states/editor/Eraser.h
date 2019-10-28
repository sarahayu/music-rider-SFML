#pragma once
#include "Tool.h"
#include "../../utils/Resources.h"

class Eraser : public Tool
{
public:
	Eraser(TextureHolder &textures, const sf::Vector2f &mousePos);

	virtual const void update(const sf::RenderWindow &window, std::vector<Entity::Ptr> &obstacles, const bool &isClicked);

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::RectangleShape m_eraserIcon;
};