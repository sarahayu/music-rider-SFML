#pragma once
#include <SFML\Graphics.hpp>
#include <deque>
#include "../utils/Resources.h"

class PlayerTrail : public sf::Drawable
{
public:
	PlayerTrail();
	void loadTexture(TextureHolder &textures);
	void update(const sf::Vector2f &pos, const float &deltaTime);
	void clearTrail();
protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	struct Particle
	{
		sf::Vector2f pos;
		float lifetime;
	};
	sf::RenderTexture m_renderTex;
	std::deque<Particle> m_particles;
	sf::Texture *m_texture;
	float m_totalTime = 0.f;
	sf::Vector2f lastPos;

	mutable sf::VertexArray m_verts;
	mutable bool m_needsUpdate = true;
};