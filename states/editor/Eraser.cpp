#include "Eraser.h"
#include "../../utils/ResourceHolder.h"

Eraser::Eraser(TextureHolder & textures, const sf::Vector2f &mousePos)
{
	m_eraserIcon.setSize({ 30.f, 30.f });
	m_eraserIcon.setOrigin({ 15.f,15.f });
	m_eraserIcon.setPosition(mousePos);
	m_eraserIcon.setTexture(&textures.get(Textures::Eraser));
}

const void Eraser::update(const sf::RenderWindow &window, std::vector<Entity::Ptr>& obstacles, const bool &isClicked)
{
	m_eraserIcon.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
	
	if (isClicked)
	{
		for (auto obstacle = obstacles.begin(); obstacle != obstacles.end(); obstacle++)
		{
			if ((*obstacle)->getGlobalBounds().contains(m_eraserIcon.getPosition()))
			{
				obstacles.erase(obstacle);
				return;
			}
		}
	}
}

void Eraser::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_eraserIcon, states);
}
