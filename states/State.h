#pragma once
#include <memory>
#include "States.h"
#include "../entities/Entity.h"
#include "../utils/Resources.h"

class StateStack;
class Player;
namespace sf 
{
	class RenderWindow; 
	class Event; 
	class Music; 
	class Sound;
	template <typename T>
	class Vector2;
	typedef Vector2<float> Vector2f;
}

class State
{
public:
	typedef std::unique_ptr<State> Ptr;
	struct Context
	{
		sf::RenderWindow *window;
		TextureHolder *textures;
		FontHolder *fonts;
		sf::Sound *explode;
		std::vector<Entity::Ptr> *entities;
		sf::Vector2f *deathSource;
		std::string *levelName;
		sf::Music *music;
		float *tempo;
		bool *requestRestart;
		sf::Vector2f *newStart;
		float *musicStart;
	};

	State(StateStack &stack, Context &context);
	virtual ~State();

	virtual void draw() = 0;
	virtual const bool update(const float &deltaTime) = 0;
	virtual const bool handleEvent(const sf::Event &evnt) = 0;

protected:
	void requestStackPush(const States::ID &id);
	void requestStackPop();
	void requestStackClear();

	const Context getContext() const;

private:
	Context m_context;
	StateStack &r_stack;
};