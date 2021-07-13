#include <iostream>
#include <assert.h>
#include <sstream>

#include "Level.h"
#include "../Util/Constants.h"
#include "../Util/tinyxml2.h"

/**
 * @brief Constructs a new Level::Level object
 * 
 * @param mapName Filename (relative to maps/) of the .tmx file from which the level is loaded.
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

std::vector<int> parse_csv_data(const char* data);

/**
 * @brief Loads m_tilemap from "mapname.tmx"
 * 
 * Parses "mapname.tmx"(Created using Tiled (A 3rd party software)) and converts it 
 * to a form useable by the class, and initializes the tile map.
 * 
 * @param mapName Filename (relative to maps/) of the .tmx file from which the level is loaded.
 */
void Level::loadMap(std::string mapName){
	using namespace tinyxml2;

	XMLDocument doc;
	if(doc.LoadFile(("maps/" + mapName + ".tmx").c_str()) != XML_SUCCESS) return;

	XMLElement* pMapNode = doc.FirstChildElement("map");

	// Get the width and the height of the whole map and store it in m_mapSize
	pMapNode->QueryIntAttribute("width", &m_mapSize.x);
	pMapNode->QueryIntAttribute("height", &m_mapSize.y);

	// Get the width and the height of the tiles
	int tileWidth, tileHeight;
	pMapNode->QueryIntAttribute("tilewidth", &tileWidth);
	pMapNode->QueryIntAttribute("tileheight", &tileHeight);
	assert(tileWidth==CONSTANTS::TILE_WIDTH && tileHeight==CONSTANTS::TILE_HEIGHT);

	//Loading the tilesets
	for(XMLElement* pTileset = pMapNode->FirstChildElement("tileset"); pTileset != NULL;
						pTileset = pTileset->NextSiblingElement("tileset")){
		// Get tileset texture source.
		std::string tileset_source = "maps/";
		tileset_source.append(pTileset->Attribute("source"));
		XMLDocument tileset_doc;
		if(tileset_doc.LoadFile(tileset_source.c_str()) != XML_SUCCESS) return;
		std::string tileset_texture_path = 
			tileset_doc.FirstChildElement()->FirstChildElement("image")->Attribute("source");
		
		// Get tileset firstgid
		int firstgid;
		pTileset->QueryIntAttribute("firstgid", &firstgid);
		// Create and add the tileset to m_tilesets
		m_tilesets.emplace_back(TileSet(tileset_texture_path, firstgid));
	}

	// Loading the layers
	for(XMLElement* pLayer = pMapNode->FirstChildElement("layer"); pLayer != NULL;
						pLayer = pLayer->NextSiblingElement("layer")){
		// Loading the tiles
		XMLElement* pData = pLayer->FirstChildElement("data");
		std::vector<int> tile_gids = parse_csv_data(pData->GetText());

		for(long unsigned tile_counter=0; tile_counter < tile_gids.size(); ++tile_counter){
			//If gid is 0, that means no tile is to be drawn there
			if(tile_gids[tile_counter]==0)
				continue;

			//Get the tileset for this specific gid
			TileSet tileset;
			int closest{0};
			for(auto& _tileset: m_tilesets){
				if(_tileset.first_gid <= tile_gids[tile_counter]){
					if (closest < _tileset.first_gid){
						closest = _tileset.first_gid;
						tileset = _tileset;
					}
				}
			}
			//No tileset was found for this gid
			if(tileset.first_gid == -1)
				continue;
			
			//Get the position of the tile in the level
			int xx = 0;
			int yy = 0;
			xx = tileWidth * (tile_counter % m_mapSize.x);
			yy = tileHeight * (tile_counter / m_mapSize.x);
			
			int y_offset = (m_mapSize.y * tileHeight) - CONSTANTS::GROUNDHEIGHT;
			yy -= y_offset;

			// Create our tile and add it to the m_tilemap
			m_tilemap.emplace_back(Tile(tileset, tile_gids[tile_counter], xx, yy));
		}
	}
}

std::vector<int> parse_csv_data(const char* data){
	std::stringstream _data(data);
	std::vector<int> _tile_gids;
	int i;
    while (_data >> i){
        _tile_gids.push_back(i);
        if (_data.peek() == ',')
            _data.ignore();
    }
	return _tile_gids;
}