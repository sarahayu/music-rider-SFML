#include "StateStack.h"
#include <cassert>
#include <iostream>

StateStack::StateStack(State::Context & context)
	: m_context(context)
{
}

StateStack::~StateStack()
{
}

void StateStack::update(const float & deltaTime)
{
	for (auto state = m_stack.rbegin(); state != m_stack.rend(); state++)
		if (!(*state)->update(deltaTime)) break;

	applyPendingChanges();
}

void StateStack::draw()
{
	for (auto state = m_stack.begin(); state != m_stack.end(); state++)
		(*state)->draw();
}

void StateStack::handleEvent(const sf::Event & evnt)
{
	for (auto state = m_stack.rbegin(); state != m_stack.rend(); state++)
		if (!(*state)->handleEvent(evnt)) break;

	applyPendingChanges();
}

void StateStack::pushState(const States::ID & id)
{
	m_pendingList.push_back({ Push, id });
}

void StateStack::popState()
{
	m_pendingList.push_back({ Pop });
}

void StateStack::clearStates()
{
	m_pendingList.push_back({ Clear });
}

const bool StateStack::isEmpty() const
{
	return m_stack.empty();
}

State::Ptr StateStack::createState(const States::ID & id)
{
	auto found = m_factories.find(id);
	assert(found != m_factories.end());

	return found->second();
}

void StateStack::applyPendingChanges()
{
	for (const PendingChange &change : m_pendingList)
	{
		switch (change.action)
		{
		case Push:
			m_stack.push_back(createState(change.id));
			break;
		case Pop:
			m_stack.pop_back();
			break;
		case Clear:
			m_stack.clear();
			break;
		}
	}

	m_pendingList.clear();
}
