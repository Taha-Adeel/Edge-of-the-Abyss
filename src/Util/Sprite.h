#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SFML/Graphics.hpp>

#include "../ResourceManager/ResourceFactory.h"

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
	Sprite(std::string name);
	Sprite(std::string spritesheet, int index);
	Sprite(std::string name, sf::IntRect rect);

	//public functions
	//Define similar setTexture functions as constructors
	void changeTexture(std::string name) ;
	void changeTexture(std::string spritesheet , int index) ;
	void changeTexture(std::string name ,sf::IntRect rect) ;
	

private:
	//private members
	sf::Texture& m_spritesheet;
};


#endif