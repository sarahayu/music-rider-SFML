#pragma once
#include <SFML\Graphics.hpp>
#include "../utils/Resources.h"

class RollingSprite : public sf::Drawable
{
public:
	RollingSprite(const sf::Texture &texture, const sf::Vector2f & size, const float & speed);

	void update(const float &deltaTime, const sf::Vector2f &topLeft);

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	const float m_speed;
	const sf::Vector2f m_size;
	const sf::Texture &m_texture;
	sf::Vector2f m_position;
	float m_leftEdge = 0.f;
};