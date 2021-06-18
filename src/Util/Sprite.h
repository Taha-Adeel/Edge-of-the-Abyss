#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SFML/Graphics.hpp>

#include "../ResourceManager/ResourceFactory.h"

class Sprite: public sf::Sprite{
public:
	//public constructors
	Sprite(std::string name);
	Sprite(std::string spritesheet, int index);
	Sprite(std::string name, sf::IntRect rect);

	//public functions
	//Define similar setTexture functions as constructors

private:
	//private members
	sf::Texture& m_spritesheet;

	//private constants
	int m_tilewidth = 42;
	int m_tileheight = 42;
	int m_tilespacing = 2;
};


#endif