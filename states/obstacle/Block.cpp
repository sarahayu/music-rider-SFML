#include "Block.h"
#include "../../utils/ResourceHolder.h"
#include "../player/Player.h"
#include <iostream>

Block::Block(const sf::Vector2f & location, ResourceHolder & resources)
	: Obstacle(getBlockSprite(location, resources), Entities::Block)
{
}

const Collision::Type Block::checkCollision(Player & player) const
{
	const sf::Vector2f loc = getSprite().getPosition();

	CollisionInfo collision = getCollision(getSprite().getGlobalBounds(), player.getGlobalBounds());

	if (collision.side == CollisionInfo::Top
		|| collision.side == CollisionInfo::Right)
	{
		player.move({ 0.f,std::min(0.f,-collision.intersection.y + 0.1f)*0.7f });
		player.stopVelocity();
		//if (collision.intersection.y > 3.f) player.move({ 0.f,-collision.intersection.y*0.2f });
		return Collision::Good;
	}
	//else if (collision.side == CollisionInfo::None && collision.intersection.y > -2.f && collision.intersection.x > 0.f) return Collision::Good;

	return collision.side == CollisionInfo::None ? Collision::None : Collision::Bad;
}

const sf::RectangleShape Block::getBlockSprite(const sf::Vector2f & location, ResourceHolder &resources)
{
	sf::RectangleShape block({ 30.f,30.f });
	block.setTexture(resources.get(Texture::Square));
	block.setOrigin(15.f, 15.f);
	block.setPosition(location);
	return block;
}
