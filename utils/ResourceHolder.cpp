#include "ResourceHolder.h"
#include <cassert>

ResourceHolder::ResourceHolder()
{
	m_textures[Texture::Player].loadFromFile("resources/player.png");
	m_textures[Texture::Square].loadFromFile("resources/square.png");
	m_textures[Texture::Triangle].loadFromFile("resources/triangle.png");
	m_textures[Texture::Eraser].loadFromFile("resources/eraser.png");
	m_textures[Texture::Portal].loadFromFile("resources/portal.png");

	m_fonts[Font::Bell].loadFromFile("resources/bell.ttf");
}

sf::Texture * ResourceHolder::get(const Texture::ID & id)
{
	auto find = m_textures.find(id);
	assert(find != m_textures.end());
	return &find->second;
}


sf::Font * ResourceHolder::get(const Font::ID & id)
{
	auto find = m_fonts.find(id);
	assert(find != m_fonts.end());
	return &find->second;
}
