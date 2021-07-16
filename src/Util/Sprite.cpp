#include "Sprite.h"
#include "Constants.h"

#include <assert.h>

/**
 * @brief Construct a new Sprite object with the texture from file "name.png".
 *   
 * @param name File path of texture relative to AssetPool::m_folder (=./assets/)
 */

Sprite::Sprite(std::string name){
	sf::Texture& texture = ResourceFactory::getResourceFactory().textures.get(name);
	texture.setSmooth(true);
	sf::Sprite::setTexture(texture);
}

/**
 * @brief Construct a new Sprite:: Sprite object with a part of the texture
 * 
 * Sets the texture of the Sprite object to the sprite/tile at index "index" from 
 * a larger spritesheet/tileset from file "spritesheet.png"
 * 
 * @param spritesheet File path of texture relative to AssetPool::m_folder (=./assets/)
 * @param index Index of the sprite/tile in the spritesheet/tileset.
 * @param tilewidth The tile width. Defaults to CONSTANTS::TILE_WIDTH = 42
 * @param tileheight The tile height. Defaults to CONSTANTS::TILE_HEIGHT = 42
 * @param tilespacing The tile spacing. Defaults to CONSTANTS::TILE_SPACING = 2
 */
Sprite::Sprite(std::string spritesheet, int index, int tilewidth, int tileheight, int tilespacing){
	setTexture(spritesheet, index, tilewidth, tileheight, tilespacing);
}

/**
 * @brief Construct a new Sprite:: Sprite object with a specified part of a texture
 * 
 * @param name File path of texture relative to AssetPool::m_folder (=./assets/)
 * @param rect The region in the texture with which to iniialize our sprite
 */
Sprite::Sprite(std::string name, sf::IntRect rect):
	sf::Sprite(ResourceFactory::getResourceFactory().textures.get(name), rect)
{
}

/**
 * @brief Sets the Sprite object's texture to texture from file "name.png".
 *   
 * @param name File path of texture relative to AssetPool::m_folder (=./assets/)
 */
void Sprite::setTexture(std::string name){
	sf::Sprite::setTexture(ResourceFactory::getResourceFactory().textures.get(name));	
}

/**
 * @brief Sets the Sprite object's texture to part of the texture from file "name.png".
 * 
 * Sets the texture of the Sprite object to the sprite/tile at index "index" from 
 * a larger spritesheet/tileset from file "spritesheet.png"
 * 
 * @param spritesheet File path of texture relative to AssetPool::m_folder (=./assets/)
 * @param index Index of the sprite/tile in the spritesheet/tileset.
 * @param tilewidth The tile width. Defaults to CONSTANTS::TILE_WIDTH = 42
 * @param tileheight The tile height. Defaults to CONSTANTS::TILE_HEIGHT = 42
 * @param tilespacing The tile spacing. Defaults to CONSTANTS::TILE_SPACING = 2
 */
void Sprite::setTexture(std::string spritesheet, int index, int tilewidth, int tileheight, int tilespacing){
	sf::Texture& texture(ResourceFactory::getResourceFactory().textures.get(spritesheet));
	sf::Vector2u size = texture.getSize();
	sf::IntRect rect;

	assert(index >= 0
		&& ("Negative index provided for sprite from " + spritesheet).c_str());
	assert(size.x % (tilewidth + tilespacing) == 0 && size.y % (tileheight + tilespacing) == 0
		&& (spritesheet + " is an invalid spritesheet for give tilewidth, tileheigth, and tilespacing").c_str());
	assert(static_cast<unsigned>(index)<(size.x/(tilewidth+tilespacing))*(size.y/(tileheight+tilespacing))
		&& ("Out of bounds index accessed from " + spritesheet).c_str());

	rect.width = tilewidth;
	rect.height = tileheight;
	rect.left = (index % (size.x / (tilewidth + tilespacing))) * (tilewidth + tilespacing);
	rect.top = (index / (size.x / (tilewidth + tilespacing))) * (tileheight + tilespacing);
	sf::Sprite::setTextureRect(rect);
	sf::Sprite::setTexture(texture);
}


/**
 * @brief Sets the Sprite object's texture to part of the texture from file "name.png".
 * 
 * @param name File path of texture relative to AssetPool::m_folder (=./assets/)
 * @param rect The region in the texture with which to set the texture of our sprite
 */
void Sprite::setTexture(std::string name ,sf::IntRect rect) 
{
	sf::Sprite::setTexture(ResourceFactory::getResourceFactory().textures.get(name));
	sf::Sprite::setTextureRect(rect);
}