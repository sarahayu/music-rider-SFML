#pragma once/*
#include <SFML\Audio.hpp>
#include <map>

namespace Music
{
	enum ID
	{

	};
}

class MusicPlayer
{
public:
	void loadMusic(const std::string &filename);

private:
	std::map<std::string, sf::Music> m_songs;
};*/