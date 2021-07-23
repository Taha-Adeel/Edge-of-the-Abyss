#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

#include "Tile.h"
#include "Background.h"
#include "Ground.h"
#include "../Util/tinyxml2.h"

class PlayingState;

/**
 * @brief Defines the level to be played
 * 
 * Contains a tilemap, and handles loading, collisions, and rendering of the tilemap.
 * 
 */
class Level{
public:
	// constructors
	Level(std::string map_name, PlayingState* context);

	// public member functions
	void update(sf::Time elapsedTime);
	void render(sf::RenderTarget& renderer);

	//public accessors
	const long unsigned getLevelNumber() const;
	const std::vector<Tile>& getTileMap() const ;
	const sf::Vector2i getMapSize() const ;
	const int getMapWidth() const ;
	const int getMapHeight() const ;
	const int getTileWidth() const ;
	const int getTileHeight() const ;

private:
	// private member variables
	PlayingState* m_pPlayingState;
	Background m_bg;
	Ground m_ground;
	std::string m_mapName;
	long unsigned m_currentLevel;
	sf::Vector2i m_mapSize;
	sf::Vector2i m_tileSize;
	std::vector<TileSet> m_tilesets;
	std::vector<Tile> m_tilemap;

	// private member functions
	void loadMap(std::string mapName);
	void loadMapData(tinyxml2::XMLElement* pMapNode);
	void loadTileSet(tinyxml2::XMLElement* pTileSet);
	void loadTile(long long int tile_data, int tile_counter);
};

// Utility functions
std::vector<long long int> parse_csv_data_to_ints(const char* data);

#endif