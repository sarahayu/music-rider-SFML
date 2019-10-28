#include "App.h"
#include "states\MenuState.h"
#include "states\GameState.h"
#include "states\GameOverState.h"
#include "states\EditorState.h"
#include "states\DeathState.h"
#include "states\PauseState.h"
#include <iostream>

const float FRAME_DURATION = 1.f / 60;

App::App()
	: m_window(sf::VideoMode(1000U, 500U), "MusicRider"), 
	m_newStart(0.f,-15.f),
	m_states(State::Context{ &m_window,&m_textures,&m_fonts,&m_explode,&m_entities,&m_deathSource,&m_datafileStr,&m_music,&m_tempo,&m_requestRestart,&m_newStart,&m_musicStart })
{
	m_fonts.load(Fonts::Kaushan, "resources/kaushan.ttf");
	m_fonts.load(Fonts::Charm, "resources/charm.ttf");

	m_textures.load(Textures::ThickPlatform, "resources/thick-platform.png");
	m_textures.load(Textures::ThinPlatform, "resources/thin-platform.png");
	m_textures.load(Textures::BigSpike, "resources/big-spike.png");
	m_textures.load(Textures::LittleSpike, "resources/little-spike.png");
	m_textures.load(Textures::Portal, "resources/portal.png");
	m_textures.load(Textures::Eraser, "resources/eraser.png");
	m_textures.load(Textures::Background, "resources/background.jpg");
	m_textures.load(Textures::Ground, "resources/ground.png");

	//load these here to prevent gamestate lag
	m_textures.load(Textures::Jumper, "resources/jumper.png");
	m_textures.load(Textures::Flyer, "resources/flyer.png");
	m_textures.load(Textures::Trail, "resources/trail.png");
	m_textures.load(Textures::Shadow, "resources/shadow.png");
	m_textures.load(Textures::Table, "resources/end.png");
	m_textures.load(Textures::InkSplat, "resources/ink.png");
	
	m_explodeBuffer.loadFromFile("resources/explode.ogg");
	m_explode.setBuffer(m_explodeBuffer);

	m_states.registerState<EditorState>(States::EditorState);
	m_states.registerState<MenuState>(States::MenuState);
	m_states.registerState<GameState>(States::GameState);
	m_states.registerState<GameOverState>(States::GameOverState);
	m_states.registerState<DeathState>(States::DeathState);
	m_states.registerState<PauseState>(States::PauseState);
	m_states.pushState(States::MenuState);

	m_stats.setFont(m_fonts.get(Fonts::Charm));
	m_stats.setPosition(5.f,5.f);
	m_stats.setFillColor(sf::Color::Black);
}

App::~App()
{
}

void App::run()
{
	float deltaTime = 0.f;
	while (m_window.isOpen())
	{
		deltaTime += m_clock.restart().asSeconds();

		while (deltaTime > FRAME_DURATION)
		{
			input();
			deltaTime -= FRAME_DURATION;
			update(FRAME_DURATION);
		}
		updateStats(deltaTime);
		render();
	}
}

void App::update(const float & deltaTime)
{
	m_states.update(deltaTime);
}

void App::input()
{
	sf::Event evnt;
	while (m_window.pollEvent(evnt))
	{
		if (m_window.hasFocus()) m_states.handleEvent(evnt);
		switch (evnt.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		case sf::Event::LostFocus:
			if (m_music.getStatus() != sf::SoundSource::Paused)
			{
				m_music.pause();
				m_states.pushState(States::PauseState);
			}
			break;
		}
	}
}

void App::render()
{
	m_window.clear(sf::Color::Cyan);
	m_states.draw();
	m_window.setView(m_window.getDefaultView());
	m_window.draw(m_stats);
	m_window.display();
}

void App::updateStats(const float &deltaTime)
{
	m_statTime += deltaTime;
	m_statFrames++;
	if (m_statTime >= 1.f)
	{
		m_stats.setString("FPS: " + std::to_string(m_statFrames));

		m_statTime -= 1.f;
		m_statFrames = 0;
	}

}
