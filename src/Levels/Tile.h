#ifndef TILE_H
#define TILE_H

#include "../Util/Sprite.h"
#include "../Util/Bound.h"
#include "TileSet.h"

/**
 * @brief Defines the elements of the tile map(Level)
 * 
 * Each Tile object has a texture, and a position in the level
 */
class Tile{
public:
	//constructor
	Tile(TileSet& tileset, int gid, float x, float y, sf::Vector2f scale, float rotation);

	//public member functions
	virtual void update(sf::Time elapsedTime);
    virtual void render(sf::RenderTarget& renderer);

	const Bound& getBounds() const;

private:
	//private member variables
	TileSet& m_tileset;/**<Reference to the tile set from which the tile gets its texture*/
	int m_gid;/**<gid of the tile in the tileset(Obtained on parsing the *.tmx files)*/
	sf::Vector2f m_position;/**<Position of the center of the tile in the level*/
	sf::Vector2f m_scale;/**<Scale of the tile in the level*/
	float m_rotation;/**<Rotation of the tile in the level*/
	Sprite m_sprite;/**<The sprite initialized with all the above properties*/
	std::unique_ptr<Bound> m_pBound;
};

#endif