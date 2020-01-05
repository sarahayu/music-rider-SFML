#include "Platform.h"
#include "../../utils/ResourceHolder.h"
#include "../Player.h"

const sf::Vector2f THICK_PLATFORM_SIZE(30.f, 30.f), THIN_PLATFORM_SIZE(30.f, 5.f);
const float COLLISION_TOLERANCE = 5.f;	// tolerance for side collision on multi-square platforms


Platform::Platform(const Type &type, ResourceHolder &resources, const sf::Vector2f &position)
	: Obstacle( *resources.get(getTexture(type)), getPlatformSize(type), position)
{
}

const Collision::Type Platform::collision(Player & player) const
{
	const sf::Vector2f	playerPos = player.getPosition(),
		playerHalf = player.getSize() / 2.f,
		thisPos = getPosition(),
		thisHalf = getSize();

	const float		deltaX = playerPos.x - thisPos.x,
		deltaY = playerPos.y - thisPos.y,
		interesectX = std::abs(deltaX) - (playerHalf.x + thisHalf.x),
		interesectY = std::abs(deltaY) - (playerHalf.y + thisHalf.y);

	if (interesectX < 0.f && interesectY < 0.f)
	{
		if (interesectX > interesectY 
			&& deltaY < 0.f
			&& interesectY < -COLLISION_TOLERANCE)
		{
			player.move({ 0.f,interesectY });
			player.land();
			return Collision::Good;
		}
		return Collision::Bad;
	}
	return Collision::None;
}

const sf::Vector2f Platform::getPlatformSize(const Platform::Type & type)
{
	switch (type)
	{
	case Platform::Thick: return THICK_PLATFORM_SIZE;
	case Platform::Thin: return THIN_PLATFORM_SIZE;
	}

	return THICK_PLATFORM_SIZE;
}

const Texture::ID Platform::getTexture(const Platform::Type & type)
{
	switch (type)
	{
	case Platform::Thick: return Texture::ThickPlatform;
	case Platform::Thin: return Texture::ThinPlatform;
	}

	return Texture::ThickPlatform;
}
