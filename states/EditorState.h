#pragma once
#include "State.h"
#include "editor\Tool.h"
#include <fstream>
#include <functional>

class EditorState : public State
{
public:
	EditorState(StateStack &stack, Context &context);
	~EditorState();

	virtual void draw();
	virtual const bool update(const float &deltaTime);
	virtual const bool handleEvent(const sf::Event &evnt);

private:

	typedef sf::Keyboard sfk;

	sf::View m_view;
	sf::CircleShape m_newstart;
	Tool::Ptr m_activeTool;
	std::map<sfk::Key, std::function<Tool::Ptr(const sf::Vector2f&)>> m_buttonMap;
};