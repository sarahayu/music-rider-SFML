#pragma once
#include <SFML\Graphics.hpp>
#include "../utils/Resources.h"

class Player : public sf::Drawable
{
public:
	enum Type { Jumper, Flyer, TypeCount };
	Player(const Type &type, TextureHolder &textures);

	void realTimeInput(const float &deltaTime);
	void update(const float &deltaTime);

	void move(const sf::Vector2f &movement);
	void setPosition(const sf::Vector2f &position);
	const sf::Vector2f getPosition() const;
	const sf::Vector2f getSize() const;
	const sf::FloatRect getGlobalBounds() const;
	const float getVelocity() const;
	
	void reset();
	void setToRest();
	void setAlive(const bool &alive);
	const bool requestingPrediction() const;		// for jump spin effect
	void setRotationSpeed(const float &rotationSpeed);
	void changeType(const Type &type, TextureHolder &textures);
	const Type getType() const;

protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::RectangleShape m_sprite;
	Type m_type;
	float m_velocity = 0.f;
	float m_gravity, m_launchPower;
	bool m_alive = true;

	// for Jumper
	bool m_requestPrediction = false;
	bool m_jumping = false;	
	float m_rotateSpeed = 0.f;

	// for Flyer
	bool m_ascending = false;
};