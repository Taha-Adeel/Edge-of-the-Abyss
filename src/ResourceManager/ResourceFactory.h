#ifndef RESOURCEFACTORY_H
#define RESOURCEFACTORY_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "AssetPool.h"
#include "../Util/NonCopyable.h"
#include "../Util/NonMoveable.h"

class ResourceFactory: public NonCopyable, public NonMovable{
public:
	static ResourceFactory& getResourceFactory();

	AssetPool<sf::Texture> m_textures;
	AssetPool<sf::Font> m_fonts;
	AssetPool<sf::SoundBuffer> m_sounds;

private:
	//Private constructor
	ResourceFactory();
};

#endif	