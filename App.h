#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "states\StateStack.h"
#include "entities\Entity.h"
#include "utils\ResourceHolder.h"
#include "states\Player.h"

class App
{
public:
	App();
	~App();

	void run();

private:

	void update(const float &deltaTime);
	void input();
	void render();

	void updateStats(const float &deltaTime);

	TextureHolder m_textures;
	FontHolder m_fonts;
	sf::Sound m_explode;
	std::vector<Entity::Ptr> m_entities;
	sf::RenderWindow m_window;
	sf::Clock m_clock;
	sf::Vector2f m_deathSource;
	std::string m_datafileStr;
	sf::Music m_music;
	float m_tempo = 0;
	bool m_requestRestart = false;
	sf::Vector2f m_newStart;
	float m_musicStart = 0.f;

	sf::SoundBuffer m_explodeBuffer;
	sf::Text m_stats;
	float m_statTime;
	int m_statFrames;

	StateStack m_states;
};