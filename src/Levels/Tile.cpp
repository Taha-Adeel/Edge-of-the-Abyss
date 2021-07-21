#include <iostream>

#include "Tile.h"
#include "../Util/BoxBound.h"
#include "../Util/Constants.h"

/**
 * @brief Construct a new Tile object
 * 
 * @param tileset Tile set from which the tile gets its texture
 * @param gid gid of the tile in the tileset(Obtained on parsing the *.tmx files)
 * @param x x co-ordinate of the top left corner of the tile in the level
 * @param y y co-ordinate of the top left corner of the tile in the level
 */
Tile::Tile(TileSet& tileset, int gid, float x, float y, sf::Vector2f scale, float rotation):
	m_tileset(tileset),
	m_gid(gid),
	m_position(x,y),
	m_scale(scale),
	m_rotation(rotation),
	m_sprite(m_tileset.getTexturePath(), m_gid - m_tileset.first_gid, 
		m_tileset.tilewidth, m_tileset.tileheight, m_tileset.tilespacing)
{
	m_sprite.setOrigin(CONSTANTS::TILE_WIDTH/2.f, CONSTANTS::TILE_HEIGHT/2.f);
	m_sprite.setPosition(m_position + m_sprite.getOrigin());
	m_sprite.setScale(m_scale);
	m_sprite.rotate(m_rotation);

	Bound* tile_bound = tileset.tile_bounds.at(gid-tileset.first_gid).get();

	if(tile_bound->getBoundType() == BOUNDTYPE::BOX){
		m_pBound = std::make_unique<BoxBound>(sf::Vector2f(tile_bound->getPosition()+m_position)
			, tile_bound->getWidth(), tile_bound->getHeight(), tile_bound->getBoundName());
	}
	else if (tile_bound->getBoundType() == BOUNDTYPE::TRIANGLE){
		std::cout << "Triangle Bound" << std::endl;
	}
}

/**
 * @brief Get the tile bounds
 * 
 * @return const Bound& 
 */
const Bound& Tile::getBounds() const {
	return *(m_pBound.get());
}


/**
 * @brief Updates the Tile Object
 * 
 * @param elapsedTime 
 */
void Tile::update(sf::Time elapsedTime){}


/**
 * @brief Renders the Tile object on to the window
 * 
 * @param renderer 
 */
void Tile::render(sf::RenderTarget& renderer){
	renderer.draw(m_sprite);
}