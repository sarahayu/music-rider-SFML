#pragma once
#include <SFML\Graphics.hpp>
#include "utils/Resources.h"

struct PlayerData
{
	Textures::ID texture;
	sf::Vector2f size;
	float gravity;
	float launchPower;
};

struct ObstacleData
{
	Textures::ID texture;
	sf::Vector2f size;
	float rotation;
};

const std::vector<PlayerData> initializePlayerData();
const std::vector<ObstacleData> initializeObstacleData();