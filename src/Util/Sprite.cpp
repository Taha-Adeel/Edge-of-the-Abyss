#include "Sprite.h"
#include "Constants.h"

#include <assert.h>

/**
 * @brief Construct a new Sprite object with the texture from file "name.png".
 *   
 * @param name File path of texture relative to AssetPool::m_folder (=./assets/)
 */

Sprite::Sprite(std::string name):
	m_spritesheet(ResourceFactory::getResourceFactory().textures.get(name))
{
	m_spritesheet.setRepeated(true);
	sf::Sprite::setTexture(m_spritesheet);
}

/**
 * @brief Construct a new Sprite:: Sprite object with a part of the texture
 * 
 * Sets the texture of the Sprite object to the sprite/tile at index "index" from 
 * a larger spritesheet/tileset from file "spritesheet.png"
 * 
 * @param spritesheet File path of texture relative to AssetPool::m_folder (=./assets/)
 * @param index Index of the sprite/tile in the spritesheet/tileset.
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
 * @brief Construct a new Sprite:: Sprite object with a specified part of a texture
 * 
 * @param name File path of texture relative to AssetPool::m_folder (=./assets/)
 * @param rect The region in the texture with which to iniialize our sprite
 */
Sprite::Sprite(std::string name, sf::IntRect rect):
	m_spritesheet(ResourceFactory::getResourceFactory().textures.get(name)){
		sf::Sprite::setTexture(m_spritesheet);
		sf::Sprite::setTextureRect(rect);
}

/**
 * @brief Changes the Sprite object's texture to texture from file "name.png".
 *   
 * @param name File path of texture relative to AssetPool::m_folder (=./assets/)
 */
void Sprite::changeTexture(std::string name)
{
	//sf::Texture m_spritesheet ;
	m_spritesheet = (ResourceFactory::getResourceFactory().textures.get(name));
	sf::Sprite::setTexture(m_spritesheet);
	
}

/**
 * @brief Changes the Sprite object's texture to part of the texture from file "name.png".
 * 
 * Sets the texture of the Sprite object to the sprite/tile at index "index" from 
 * a larger spritesheet/tileset from file "spritesheet.png"
 * 
 * @param spritesheet File path of texture relative to AssetPool::m_folder (=./assets/)
 * @param index Index of the sprite/tile in the spritesheet/tileset.
 */
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
 * @brief Changes the Sprite object's texture to part of the texture from file "name.png".
 * 
 * @param name File path of texture relative to AssetPool::m_folder (=./assets/)
 * @param rect The region in the texture with which to set the texture of our sprite
 */
void Sprite::changeTexture(std::string name ,sf::IntRect rect) 
{
	m_spritesheet = (ResourceFactory::getResourceFactory().textures.get(name));
	sf::Sprite(m_spritesheet, rect) ;
}