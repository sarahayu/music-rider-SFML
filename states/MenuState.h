#pragma once
#include <SFML\Graphics.hpp>
#include <fstream>
#include <functional>
#include "State.h"
#include "../utils/Resources.h"
#include "../utils/ResourceHolder.h"

class MenuState : public State
{
public:
	MenuState(StateStack &stack, Context &context);

	virtual void draw();
	virtual const bool update(const float &deltaTime);
	virtual const bool handleEvent(const sf::Event &evnt);

private:
	const bool checkFile(const std::string &answer);

	FontHolder m_fonts;
	sf::RectangleShape m_background, m_shadow;
	sf::Text m_text, m_logo;
	std::fstream m_file;

	struct Prompts { std::string question, answer; std::function<const bool(const std::string&)> callback; };
	std::vector<Prompts> m_prompts;
	int m_currentPrompt = 0;
};