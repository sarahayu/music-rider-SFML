#include "RollingSprite.h"
#include "../utils/ResourceHolder.h"
#include "../DataTables.h"

RollingSprite::RollingSprite(const sf::Texture &texture, const sf::Vector2f & size, const float & speed)
	: m_speed(speed), m_size(size), m_texture(texture)
{
}

void RollingSprite::update(const float & deltaTime, const sf::Vector2f &topLeft)
{
	m_leftEdge -= deltaTime * m_speed;
	if (m_leftEdge < -m_size.x) m_leftEdge = (m_leftEdge + m_size.x);
	m_position = { topLeft.x + m_leftEdge, topLeft.y };
}

void RollingSprite::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	sf::VertexArray verts(sf::Quads);
	const auto targetLeft = target.getView().getCenter().x + target.getView().getSize().x / 2;
	const sf::Vector2f texSize = (sf::Vector2f)m_texture.getSize();
	sf::Vector2f pos = m_position;

	while (pos.x < targetLeft)
	{
		verts.append(sf::Vertex(pos, { 0.f,0.f }));
		verts.append(sf::Vertex({ pos.x + m_size.x,pos.y }, { texSize.x,0.f }));
		verts.append(sf::Vertex({ pos.x + m_size.x,pos.y + m_size.y }, { texSize.x,texSize.y }));
		verts.append(sf::Vertex({ pos.x,pos.y + m_size.y }, { 0.f,texSize.y }));

		pos.x += m_size.x;
	}

	states.texture = &m_texture;
	target.draw(verts, states);

	//m_sprite.move(m_sprite.getSize().x, 0.f);
	//target.draw(m_sprite, states);
	
	/*
	const auto targetLeft = target.getView().getCenter().x + target.getView().getSize().x / 2;
	while (m_sprite.getGlobalBounds().left < targetLeft)
	{
		target.draw(m_sprite, states);
		m_sprite.move(m_sprite.getSize().x, 0.f);
	}*/
}
