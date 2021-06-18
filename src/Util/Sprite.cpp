#include "Sprite.h"
#include <assert.h>

/**
 * @brief Construct a new Sprite:: Sprite object
 * 
 * 
 * 
 * @param name 
 */

Sprite::Sprite(std::string name):
			m_spritesheet(ResourceFactory::getResourceFactory().textures.get(name)){
	sf::Sprite::setTexture(m_spritesheet);
}

/**
 * @brief Construct a new Sprite:: Sprite object
 * 
 * @param spritesheet 
 * @param index 
 */
Sprite::Sprite(std::string spritesheet, int index):
	m_spritesheet(ResourceFactory::getResourceFactory().textures.get(spritesheet)){
	sf::Vector2u size = m_spritesheet.getSize();
	//sf::IntRect rect;

	assert(index >= 0);
	assert(size.x % 44 == 0 && size.y % 44 == 0);
	assert(static_cast<unsigned>(index) < size.x * size.y);
		
	//rect.width = m_tilewidth;
	//rect.height = m_tileheight;
	//rect.left = ((index % size.x) * (m_tilewidth + m_tilespacing)) + m_tilespacing/2;
	//rect.top = (index % size.y) * (m_tileheight + m_tilespacing) + m_tilespacing/2;

	sf::Sprite::setTexture(m_spritesheet);
	sf::IntRect rect(1, 1, 42, 42);
	sf::Sprite::setTextureRect(rect);
}

/**
 * @brief Construct a new Sprite:: Sprite object
 * 
 * @param name 
 * @param rect 
 */
Sprite::Sprite(std::string name, sf::IntRect rect):
	m_spritesheet(ResourceFactory::getResourceFactory().textures.get(name)){
		sf::Sprite::setTexture(m_spritesheet);
		sf::Sprite::setTextureRect(rect);
}


void Sprite::changeTexture(std::string name)
{
	//sf::Texture m_spritesheet ;
	m_spritesheet = (ResourceFactory::getResourceFactory().textures.get(name));
	sf::Sprite::setTexture(m_spritesheet);
	
}


void Sprite::changeTexture(std::string spritesheet , int index) 
{
	m_spritesheet = (ResourceFactory::getResourceFactory().textures.get(spritesheet)) ;
	sf::Vector2u size = m_spritesheet.getSize();
	sf::IntRect rect;

	assert(index >= 0);
	assert(size.x % 44 == 0 && size.y % 44 == 0);
	assert(static_cast<unsigned>(index) < size.x * size.y);
		
	rect.width = m_tilewidth;
	rect.height = m_tileheight;
	rect.left = ((index % size.x) * (m_tilewidth + m_tilespacing)) + m_tilespacing/2;
	rect.top = (index % size.y) * (m_tileheight + m_tilespacing) + m_tilespacing/2;

	sf::Sprite::setTexture(m_spritesheet);
	sf::Sprite::setTextureRect(rect);

}
/**
 * @brief change the  texture
 * 		
 * @param name  relative file path to resource from asset
 * @param rect  part to texture 
 */

void Sprite::changeTexture(std::string name ,sf::IntRect rect) 
{
	m_spritesheet = (ResourceFactory::getResourceFactory().textures.get(name));
	sf::Sprite(m_spritesheet, rect) ;
}