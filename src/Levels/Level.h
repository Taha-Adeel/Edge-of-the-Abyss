#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

#include "Tile.h"
#include "Background.h"
#include "Ground.h"

/**
 * @brief Defines the level to be played
 * 
 * Contains a tilemap, and handles loading, collisions, and rendering of the tilemap.
 * 
 */
class Level{
public:
	// constructors
	Level(std::string map_name);

	// public member functions
	void update(sf::Time elapsedTime);
	void render(sf::RenderTarget& renderer);

private:
	// private member variables
	Background m_bg;
	Ground m_ground;
	std::string m_mapName;
	sf::Vector2i m_mapSize;
	std::vector<TileSet> m_tilesets;
	std::vector<Tile> m_tilemap;

	// private member functions
	void loadMap(std::string mapName);
};

#endif