#include "Player.h"
#include <SFML\Graphics.hpp>
#include "../Settings.h"
#include "../utils/MathUtils.h"
#include "../utils/ResourceHolder.h"
#include "../DataTables.h"
#include <iostream>

const float NOSE_ANGLE_SPEED = 90.f;

namespace
{
	std::vector<PlayerData> Table = initializePlayerData();
}

Player::Player(const Type &type, TextureHolder &textures)
	: m_type(type), m_gravity(Table[type].gravity), m_launchPower(Table[type].launchPower)
{
	m_sprite.setTexture(&textures.get(Table[type].texture));

	const sf::Vector2f size = Table[type].size;
	m_sprite.setSize(size);
	m_sprite.setOrigin(size / 2.f);
}

void Player::realTimeInput(const float & deltaTime)
{
	m_ascending = false;

	typedef sf::Keyboard sfk;
	if (sfk::isKeyPressed(sfk::Space))
	{
		switch (m_type)
		{
		case Jumper:
			if (!m_jumping)
			{
				m_jumping = true;
				m_velocity = m_launchPower;
				m_requestPrediction = true;
			}
			break;
		case Flyer:
			m_ascending = true;
		break;
		}
	}
}

void Player::update(const float & deltaTime)
{
	switch (m_type)
	{
	case Jumper:
		if(m_jumping) m_sprite.rotate(m_rotateSpeed*deltaTime);
		m_velocity += m_gravity * deltaTime;
		break;
	case Flyer:
		if (m_ascending)
		{
			m_sprite.rotate(-deltaTime*NOSE_ANGLE_SPEED);
			m_velocity -= m_gravity * deltaTime;
		}
		else
		{
			m_sprite.rotate(deltaTime*NOSE_ANGLE_SPEED);
			m_velocity += m_gravity * deltaTime;
		}
		break;
	}

	move({ Settings::X_SPEED*deltaTime,m_velocity*deltaTime });
}

void Player::move(const sf::Vector2f & movement)
{
	m_sprite.move(movement);
}

void Player::setPosition(const sf::Vector2f & position)
{
	m_sprite.setPosition(position);
}

const sf::Vector2f Player::getPosition() const
{
	return m_sprite.getPosition();
}

const sf::Vector2f Player::getSize() const
{
	return m_sprite.getSize();
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return sf::FloatRect(getPosition() - getSize() / 2.f, getSize());
}

const float Player::getVelocity() const
{
	return m_velocity;
}

void Player::reset()
{
	setToRest();
	m_sprite.setRotation(0.f);
}

void Player::setToRest()
{
	m_velocity = 0.f;
	m_ascending = false;
	m_rotateSpeed = 0.f;
	m_jumping = false;
	if (m_type == Jumper) m_sprite.setRotation((int)((m_sprite.getRotation() + 45.f) / 90) * 90);
	else m_sprite.setRotation(0.f);
}

void Player::setAlive(const bool & alive)
{
	m_alive = alive;
}

const bool Player::requestingPrediction() const
{
	return m_requestPrediction;
}

void Player::setRotationSpeed(const float & rotationSpeed)
{
	m_rotateSpeed = rotationSpeed;
	m_requestPrediction = false;
}

void Player::changeType(const Type & type, TextureHolder &textures)
{
	m_type = type;

	m_sprite.setTexture(&textures.get(Table[type].texture));

	const sf::Vector2f size = Table[type].size;
	m_sprite.setSize(size);
	m_sprite.setOrigin(size / 2.f);
	m_sprite.setRotation(0.f);

	m_gravity = Table[type].gravity;
	m_launchPower = Table[type].launchPower;
}

const Player::Type Player::getType() const
{
	return m_type;
}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (m_alive) target.draw(m_sprite, states);
}
