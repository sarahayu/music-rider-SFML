#pragma once
#include <functional>
#include <vector>
#include "State.h"

class StateStack
{
public:
	enum Action { Push, Pop, Clear };

	StateStack(State::Context &context);
	~StateStack();

	template <typename T>
	void registerState(const States::ID &id);

	void update(const float &deltaTime);
	void draw();
	void handleEvent(const sf::Event &evnt);

	void pushState(const States::ID &id);
	void popState();
	void clearStates();

	const bool isEmpty() const;

private:
	State::Ptr createState(const States::ID &id);
	void applyPendingChanges();

	struct PendingChange
	{
		Action action;
		States::ID id;
	};

	std::vector<State::Ptr> m_stack;
	std::vector<PendingChange> m_pendingList;
	State::Context m_context;
	std::map<States::ID, std::function<State::Ptr()>> m_factories;
};

template<typename T>
inline void StateStack::registerState(const States::ID & id)
{
	m_factories[id] = [this]()
	{
		return std::make_unique<T>(*this, m_context);
	};
}
