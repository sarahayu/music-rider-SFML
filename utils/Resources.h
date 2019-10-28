#pragma once

// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
	class Shader;
	class SoundBuffer;
}

namespace Textures
{
	enum ID
	{
		Jumper,
		Flyer,
		ThickPlatform,
		ThinPlatform,
		BigSpike,
		LittleSpike,
		Eraser,
		Portal,
		Trail,
		Background,
		Ground,
		Shadow,
		Table,
		InkSplat
	};
}

namespace Shaders
{
	enum ID
	{
		BrightnessPass,
		DownSamplePass,
		GaussianBlurPass,
		AddPass,
	};
}

namespace Fonts
{
	enum ID
	{
		Kaushan,
		Charm
	};
}

namespace Sounds
{
	enum ID
	{
		Explode
	};
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>	TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>			FontHolder;
typedef ResourceHolder<sf::Shader, Shaders::ID>			ShaderHolder;
typedef ResourceHolder<sf::SoundBuffer, Sounds::ID>			SoundBufferHolder;