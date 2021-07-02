#include "Sprite.h"
#include "Constants.h"

#include <assert.h>

/**
 * @brief Construct a new Sprite:: Sprite object
 *   
 * @param name 
 */

Sprite::Sprite(std::string name):
			m_spritesheet(ResourceFactory::getResourceFactory().textures.get(name)){
	m_spritesheet.setRepeated(true);
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
	sf::IntRect rect;

	assert(index >= 0);
	assert(size.x % (CONSTANTS::TILE_WIDTH + CONSTANTS::TILE_SPACING) == 0 && size.y % (CONSTANTS::TILE_HEIGHT + CONSTANTS::TILE_SPACING) == 0);
	assert(static_cast<unsigned>(index) < size.x * size.y);

	rect.width = CONSTANTS::TILE_WIDTH;
	rect.height = CONSTANTS::TILE_HEIGHT;
	rect.left = (index%(size.x/(CONSTANTS::TILE_WIDTH + CONSTANTS::TILE_SPACING)))
					* (CONSTANTS::TILE_WIDTH + CONSTANTS::TILE_SPACING) + CONSTANTS::TILE_SPACING/2;
	rect.top = (index/(size.x/(CONSTANTS::TILE_WIDTH + CONSTANTS::TILE_SPACING)))
					* (CONSTANTS::TILE_HEIGHT + CONSTANTS::TILE_SPACING) + CONSTANTS::TILE_SPACING/2;
	sf::Sprite::setTextureRect(rect);
	sf::Sprite::setTexture(m_spritesheet);
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
	assert(size.x % (CONSTANTS::TILE_WIDTH + CONSTANTS::TILE_SPACING) == 0 && size.y % (CONSTANTS::TILE_HEIGHT + CONSTANTS::TILE_SPACING) == 0);
	assert(static_cast<unsigned>(index) < size.x * size.y);

	rect.width = CONSTANTS::TILE_WIDTH;
	rect.height = CONSTANTS::TILE_HEIGHT;
	rect.left = (index%(size.x/(CONSTANTS::TILE_WIDTH + CONSTANTS::TILE_SPACING)))
					* (CONSTANTS::TILE_WIDTH + CONSTANTS::TILE_SPACING) + CONSTANTS::TILE_SPACING/2;
	rect.top = (index/(size.x/(CONSTANTS::TILE_WIDTH + CONSTANTS::TILE_SPACING)))
					* (CONSTANTS::TILE_HEIGHT + CONSTANTS::TILE_SPACING) + CONSTANTS::TILE_SPACING/2;

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