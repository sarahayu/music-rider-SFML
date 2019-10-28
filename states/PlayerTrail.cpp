#include "PlayerTrail.h"
#include "../utils/ResourceHolder.h"
#include <iostream>

const float PARTICLE_INTERVAL = 1.f / 60;
const sf::Vector2f PARTICLE_SIZE(30.f, 30.f);
const sf::Vector2f PARTICLE_HALF_SIZE = PARTICLE_SIZE / 2.f;
const float LIFETIME = 0.25f;

PlayerTrail::PlayerTrail()
	: m_verts(sf::Quads)
{
}

void PlayerTrail::loadTexture(TextureHolder & textures)
{
	m_texture = &textures.get(Textures::Trail);
}

void PlayerTrail::update(const sf::Vector2f & pos, const float & deltaTime)
{
	while (!m_particles.empty() && m_particles.front().lifetime <= 0.f) m_particles.pop_front();
	for (Particle &p : m_particles) p.lifetime -= deltaTime;
	m_needsUpdate = true;

	m_totalTime += deltaTime;
	while (m_totalTime > PARTICLE_INTERVAL)
	{
		m_totalTime -= PARTICLE_INTERVAL;
		
		m_particles.push_back({ pos,LIFETIME });
	}

	lastPos = pos;
}

void PlayerTrail::clearTrail()
{
	m_particles.clear();
	m_needsUpdate = true;
}

void PlayerTrail::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (m_needsUpdate)
	{
		m_needsUpdate = false;
		
		m_verts.clear();

		const sf::Vector2f texSize = (sf::Vector2f)m_texture->getSize();

		for (const Particle &p : m_particles)
		{
			const sf::Color c = sf::Color(255, 255, 255, std::max(0.f, p.lifetime / LIFETIME) * 255);
			m_verts.append(sf::Vertex({ p.pos.x - PARTICLE_HALF_SIZE.x,p.pos.y - PARTICLE_HALF_SIZE.y }, c, { 0.f,0.f }));
			m_verts.append(sf::Vertex({ p.pos.x + PARTICLE_HALF_SIZE.x,p.pos.y - PARTICLE_HALF_SIZE.y }, c, { texSize.x,0.f }));
			m_verts.append(sf::Vertex({ p.pos.x + PARTICLE_HALF_SIZE.x,p.pos.y + PARTICLE_HALF_SIZE.y }, c, { texSize.x,texSize.y }));
			m_verts.append(sf::Vertex({ p.pos.x - PARTICLE_HALF_SIZE.x,p.pos.y + PARTICLE_HALF_SIZE.y }, c, { 0.f,texSize.y }));

		}
	}


	states.texture = m_texture;
	target.draw(m_verts, states);
}
