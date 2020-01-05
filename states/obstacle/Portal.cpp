#include "Portal.h"
#include "../../utils/ResourceHolder.h"
#include "../player/Player.h"

Portal::Portal(const sf::Vector2f &position, ResourceHolder & resources)
	: Entity(Entities::Portal)
{
	getSprite().setTexture(resources.get(Texture::Portal));
	getSprite().setSize({ 30.f,90.f });
	getSprite().setOrigin(15.f, 45.f);
	getSprite().setPosition(position);
}


const bool Portal::checkCollided(const Player & player)
{
	bool collided = player.getGlobalBounds().intersects(getSprite().getGlobalBounds());
	if (!m_passed) m_passed = collided;
	return collided;
}

const bool Portal::passedThrough() const
{
	return m_passed;
}

void Portal::doneWith()
{
	m_passed = false;
}
