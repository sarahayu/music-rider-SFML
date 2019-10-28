#include "MenuState.h"
#include "../entities/Entities.h"
#include "../entities/Obstacle.h"
#include "../entities/Portal.h"
#include "../Settings.h"
#include <SFML\Audio.hpp>
#include <functional>
#include <iostream>

MenuState::MenuState(StateStack & stack, Context & context)
	: State(stack, context),
	m_background({ (float)context.window->getSize().y * 6, (float)context.window->getSize().y }),
	m_shadow((sf::Vector2f)context.window->getSize()),
	m_text("", context.fonts->get(Fonts::Charm),40U),
	m_logo("Music Rider", context.fonts->get(Fonts::Kaushan), 80U)
{
	m_background.setTexture(&context.textures->get(Textures::Background));
	m_shadow.setTexture(&context.textures->get(Textures::Shadow));
	m_text.setFillColor(sf::Color::Black);
	m_logo.setPosition((float)context.window->getSize().x / 2, 20.f);
	m_logo.setOrigin(m_logo.getGlobalBounds().width / 2, 0.f);
	m_logo.setFillColor(sf::Color::Black);

	m_prompts.push_back({ "Type a level name: ", "", std::bind(&MenuState::checkFile,this, std::placeholders::_1) });
	m_prompts.push_back({ "Type a music file: ", "", [this](const std::string &answer) {
		m_file << answer << " ";
		getContext().music->openFromFile("resources/" + answer);
		m_currentPrompt++;
		return false;
	} });
	m_prompts.push_back({ "Type a tempo in beats per minute: ", "", [this](const std::string &answer) {
		m_file << answer << " ";
		*getContext().tempo = std::stof(answer);

		m_file.close();

		requestStackPop();
		requestStackPush(States::GameState);
		return true;
	} });

}

void MenuState::draw()
{
	m_text.setString(m_prompts[m_currentPrompt].question + m_prompts[m_currentPrompt].answer + "_");

	sf::FloatRect bounds = m_text.getGlobalBounds();
	m_text.setOrigin(bounds.width / 2, bounds.height / 2);

	auto &window = *getContext().window;
	sf::Vector2f size = (sf::Vector2f)window.getSize();
	m_text.setPosition(size.x / 2, size.y / 2);

	window.draw(m_background);
	window.draw(m_shadow);
	window.draw(m_logo);
	window.draw(m_text);
}

const bool MenuState::update(const float & deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
	{
		
	}
	return true;
}

const bool MenuState::handleEvent(const sf::Event & evnt)
{

	if (evnt.type == sf::Event::KeyPressed && evnt.key.code == sf::Keyboard::Return)
		if (m_prompts[m_currentPrompt].callback(m_prompts[m_currentPrompt].answer)) return true;

	if (evnt.type == sf::Event::KeyPressed && evnt.key.code == sf::Keyboard::BackSpace)
		m_prompts[m_currentPrompt].answer = m_prompts[m_currentPrompt].answer.substr(0, m_prompts[m_currentPrompt].answer.size() - 1);

	if (evnt.type == sf::Event::TextEntered && evnt.text.unicode > 31) m_prompts[m_currentPrompt].answer += (char)evnt.text.unicode;

	return true;
}


const bool MenuState::checkFile(const std::string &answer)
{
	m_file.open("resources/" + answer + Settings::SUFFIX, std::ios::in);
	*getContext().levelName = answer;

	if (m_file.peek() == std::ifstream::traits_type::eof())
	{
		m_file.close();
		m_file.open("resources/" + answer + Settings::SUFFIX, std::ios::out);
		m_currentPrompt = 1;
		return false;
	}

	std::string songFile; float tempo;

	m_file >> songFile >> tempo;

	getContext().music->openFromFile("resources/" + songFile);
	*getContext().tempo = tempo;

	int itype;
	while (m_file >> itype)
	{

		Entities::Type type = (Entities::Type) itype;

		switch (type)
		{
		case Entities::Platform:
		case Entities::Spike:
		{
			int subType; m_file >> subType;
			sf::Vector2f coords; m_file >> coords.x >> coords.y;
			getContext().entities->push_back(std::make_unique<Obstacle>((Obstacle::Type)subType, coords, *getContext().textures));
		}
		break;
		case Entities::Portal:
		{
			int playerType; m_file >> playerType;
			sf::Vector2f coords; m_file >> coords.x >> coords.y;
			getContext().entities->push_back(std::make_unique<Portal>(coords, *getContext().textures, playerType));
		}
		break;
		}
	}

	m_file.close();

	
	requestStackPop();
	requestStackPush(States::GameState);

	return true;
}