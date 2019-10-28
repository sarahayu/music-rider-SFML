#pragma once
#include "Entity.h"
#include "../utils/Resources.h"

class Obstacle : public Entity
{
public:
	enum Type 
	{
		ThickPlatform, 
		ThinPlatform,
		UpBigSpike,
		RightBigSpike,
		DownBigSpike,
		LeftBigSpike,
		UpLittleSpike,
		DownLittleSpike,
		TypeCount
	};

	Obstacle(const Type &type, const sf::Vector2f &position, TextureHolder &textures);

	virtual const std::string serialize() const;

	const Type getObstacleType();

private:
	static const Entities::Type getObstacleCategory(const Type &type);

	const Type m_type;
};