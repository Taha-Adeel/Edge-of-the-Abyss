#include "Tile.h"

/**
 * @brief Construct a new Tile object
 * 
 * @param tileset Tile set from which the tile gets its texture
 * @param gid gid of the tile in the tileset(Obtained on parsing the *.tmx files)
 * @param x x co-ordinate of the top left corner of the tile in the level
 * @param y y co-ordinate of the top left corner of the tile in the level
 */
Tile::Tile(TileSet& tileset, int gid, float x, float y):
	m_tileset(tileset),
	m_gid(gid),
	m_position(x,y),
	m_tile(m_tileset.texture, m_gid - m_tileset.first_gid)
{
	m_tile.setPosition(m_position);
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
	renderer.draw(m_tile);
}