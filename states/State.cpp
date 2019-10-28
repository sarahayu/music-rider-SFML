#include "State.h"
#include "StateStack.h"
#include <iostream>

State::State(StateStack & stack, Context & context)
	: r_stack(stack), m_context(context)
{
}

State::~State()
{
}

void State::requestStackPush(const States::ID & id)
{
	r_stack.pushState(id);
}

void State::requestStackPop()
{
	r_stack.popState();
}

void State::requestStackClear()
{
	r_stack.clearStates();
}

const State::Context State::getContext() const
{
	return m_context;
}
