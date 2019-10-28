#include "DataTables.h"
#include "states\Player.h"
#include "entities\Obstacle.h"
#include "states\RollingSprite.h"
#include "Settings.h"

namespace
{/*
	const float A = 0.03f;
	const float JUMP_DISTANCE = 125.f;*/

}

const std::vector<PlayerData> initializePlayerData()
{
	std::vector<PlayerData> data(Player::TypeCount);

	data[Player::Jumper] = { Textures::Jumper,sf::Vector2f(30.f,30.f),Settings::VEL_STEP,Settings::START_VELOCITY };
	data[Player::Flyer] = { Textures::Flyer,sf::Vector2f(30.f,30.f),Settings::FLY_STEP,Settings::START_VELOCITY };

	return data;
}

const std::vector<ObstacleData> initializeObstacleData()
{
	std::vector<ObstacleData> data(Obstacle::TypeCount);

	data[Obstacle::ThickPlatform] = { Textures::ThickPlatform,sf::Vector2f(30.f,30.f),0.f };
	data[Obstacle::ThinPlatform] = { Textures::ThinPlatform,sf::Vector2f(30.f,10.f),0.f };
	data[Obstacle::UpBigSpike] = { Textures::BigSpike,sf::Vector2f(30.f,30.f),0.f };
	data[Obstacle::RightBigSpike] = { Textures::BigSpike,sf::Vector2f(30.f,30.f),90.f };
	data[Obstacle::DownBigSpike] = { Textures::BigSpike,sf::Vector2f(30.f,30.f),180.f };
	data[Obstacle::LeftBigSpike] = { Textures::BigSpike,sf::Vector2f(30.f,30.f),275.f };
	data[Obstacle::UpLittleSpike] = { Textures::LittleSpike,sf::Vector2f(30.f,10.f),0.f };
	data[Obstacle::DownLittleSpike] = { Textures::LittleSpike,sf::Vector2f(30.f,10.f),180.f };

	return data;
}