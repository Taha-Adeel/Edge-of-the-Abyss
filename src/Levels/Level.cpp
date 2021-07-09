#include "Level.h"
#include <iostream>

/**
 * @brief Constructs a new Level::Level object
 * 
 * @param mapName Filename (relative to ???) of the .tmx file from which the level is loaded.
 */
Level::Level(std::string mapName):
	m_bg("bg01"),
	m_ground("ground01"),
	m_mapName(mapName)
{
	loadMap(m_mapName);
}

/**
 * @brief Updates the Level
 * 
 * @param elapsedTime 
 */
void Level::update(sf::Time elapsedTime){
	m_bg.update(elapsedTime);
	m_ground.update(elapsedTime);
}

/**
 * @brief Renders the Level on to the window
 * 
 * @param renderer 
 */
void Level::render(sf::RenderTarget& renderer){
	m_bg.render(renderer);
	m_ground.render(renderer);
	for(auto& tile: m_tilemap){
		tile.render(renderer);
	}
}

/**
 * @brief Loads m_tilemap from "mapname.tmx"
 * 
 * Parses "mapname.tmx"(Created using Tiled (A 3rd party software)) and converts it 
 * to a form useable by the class, and initializes the tile map.
 * 
 * @param mapName Filename (relative to ???) of the .tmx file from which the level is loaded.
 */
void Level::loadMap(std::string mapName){
	// m_tilesets.emplace_back(TileSet("smallBlocks", 0));
	// m_tilemap.emplace_back(Tile(m_tilesets[0], 3, 600, 529.f));
	// m_tilemap.emplace_back(Tile(m_tilesets[0], 0, 642, 529.f));
	// m_tilemap.emplace_back(Tile(m_tilesets[0], 0, 684, 529.f));
	// m_tilemap.emplace_back(Tile(m_tilesets[0], 4, 726, 529.f));
}