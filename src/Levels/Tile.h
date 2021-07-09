#ifndef TILE_H
#define TILE_H

#include "../Util/Sprite.h"
#include "TileSet.h"

/**
 * @brief Defines the elements of the tile map(Level)
 * 
 * Each Tile object has a texture, and a position in the level
 */
class Tile{
public:
	//constructor
	Tile(TileSet& tileset, int gid, float x, float y);

	//public member functions
	virtual void update(sf::Time elapsedTime);
    virtual void render(sf::RenderTarget& renderer);

private:
	//private member variables
	TileSet& m_tileset;/**<Tile set from which the tile gets its texture*/
	int m_gid;/**<gid of the tile in the tileset(Obtained on parsing the *.tmx files)*/
	sf::Vector2f m_position;/**<Position of the top left corner of the tile in the level*/
	Sprite m_tile;/**<The tile initialized with all the above properties*/
};

#endif