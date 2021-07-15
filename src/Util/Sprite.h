#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SFML/Graphics.hpp>

#include "../ResourceManager/ResourceFactory.h"
#include "Constants.h"

/**
 * @brief class Sprite is a wrapper class for sf::sprite
 * 
 * We can directly set the texture of a Sprite object using its different constructors, rather
 * than first manually initializing an sf::Texture, then construct an sf::sprite with it. Internally
 * uses the Resource Manager.
 * 
 */

class Sprite: public sf::Sprite{
public:
	//public constructor
	Sprite() = default;
	Sprite(std::string name);
	Sprite(std::string spritesheet, int index, 
		int tilewidth = CONSTANTS::TILE_WIDTH,
			int tileheight = CONSTANTS::TILE_HEIGHT,
				int tilespacing = CONSTANTS::TILE_SPACING);
	Sprite(std::string name, sf::IntRect rect);

	//public functions
	//Define similar setTexture functions as constructors
	void setTexture(std::string name);
	void setTexture(std::string spritesheet, int index, 
		int tilewidth = CONSTANTS::TILE_WIDTH,
			int tileheight = CONSTANTS::TILE_HEIGHT,
				int tilespacing = CONSTANTS::TILE_SPACING);
	void setTexture(std::string name, sf::IntRect rect);
};


#endif