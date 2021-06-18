#ifndef RESOURCEFACTORY_H
#define RESOURCEFACTORY_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "AssetPool.h"
#include "../Util/NonCopyable.h"
#include "../Util/NonMoveable.h"

/**
 * @brief Handles and responsible for our resource creation.
 * 
 * Internally maintains AssetPool of sf::Texture, sf::Fonts, sf::SoundBuffer,which actually
 * handle the resource management. ResourceFactory is noncopyable and nonmovable(and a singleton).
 * 
 */

class ResourceFactory: public NonCopyable, public NonMovable{
public:
	static ResourceFactory& getResourceFactory();

	AssetPool<sf::Texture> textures;
	AssetPool<sf::Font> fonts;
	AssetPool<sf::SoundBuffer> sounds;

private:
	//Private constructor
	ResourceFactory();
};

#endif	