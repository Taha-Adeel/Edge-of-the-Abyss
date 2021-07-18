#include <iostream>
#include <sstream>
#include <exception>

#include "../States/PlayingState.h"
#include "Level.h"
#include "../Util/Constants.h"
#include "../Util/tinyxml2.h"

/**
 * @brief Constructs a new Level::Level object
 * 
 * @param mapName Filename (relative to maps/) of the .tmx file from which the level is loaded.
 * @param context Reference to the PlayingState object that level belongs to so that it can access its contents
 */
Level::Level(std::string mapName, PlayingState& context):
	m_refPlayingState(context),
	m_bg("bg01-hd", CONSTANTS::BG_COLOR, context),
	m_ground("ground01", CONSTANTS::GROUND_BG_COLOR, context),
	m_mapName(mapName)
{	
	try{
		loadMap(m_mapName);
	}
	catch(std::exception& e){
		std::cout << e.what() << std::endl;
	}
}

/**
 * @brief Return a const reference to the tile map.
 * 
 * @return const std::vector<Tile>& 
 */
const std::vector<Tile>& Level::getTileMap() const {
	return m_tilemap;
}

/**
 * @brief Get the width of the map in tile units
 * 
 * @return const int 
 */
const int Level::getMapWidth() const {
	return m_mapSize.x;
}

/**
 * @brief Get the height of the map in tile units
 * 
 * @return const int 
 */
const int Level::getMapHeight() const {
	return m_mapSize.y;
}

/**
 * @brief Get the map size in pixel x pixel
 * 
 */
const sf::Vector2i Level::getMapSize() const {
	return sf::Vector2i(m_mapSize.x*m_tileSize.x , m_mapSize.y*m_tileSize.y);
}

/**
 * @brief Get the tile width in pixels
 * 
 * @return const int 
 */
const int Level::getTileWidth() const {
	return m_tileSize.x;
}

/**
 * @brief Get the tile height in pixels
 * 
 * @return const int 
 */
const int Level::getTileHeight() const {
	return m_tileSize.y;
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
 * @param mapName Filename (relative to maps/) of the .tmx file from which the level is loaded.
 */
void Level::loadMap(std::string mapName){
	using namespace tinyxml2;

	XMLDocument doc;
	if(doc.LoadFile(("maps/" + mapName + ".tmx").c_str()) != XML_SUCCESS)
		throw std::runtime_error("Map: maps/" + mapName + ".tmx not found");

	XMLElement* pMapNode = doc.FirstChildElement("map");

	loadMapData(pMapNode);

	//Loading the tilesets
	for(XMLElement* pTileset = pMapNode->FirstChildElement("tileset"); pTileset != NULL;
						pTileset = pTileset->NextSiblingElement("tileset"))
	{
		try{
			// Load and add the tileset to m_tilesets
			TileSet tls = loadTileSet(pTileset);
			m_tilesets.push_back(tls);
		}
		catch(std::exception& e){
			std::cout << e.what() << std::endl;
		}
	}

	// Loading the layers
	for(XMLElement* pLayer = pMapNode->FirstChildElement("layer"); pLayer != NULL;
						pLayer = pLayer->NextSiblingElement("layer")){
		// Loading the tile data
		XMLElement* pData = pLayer->FirstChildElement("data");
		std::vector<long long int> tile_data = parse_csv_data_to_ints(pData->GetText());

		for(long unsigned tile_counter=0; tile_counter < tile_data.size(); ++tile_counter){
			//If tile_data is 0, that means no tile is to be drawn there
			if(tile_data[tile_counter]==0)
				continue;
			
			try{
				// Load and add the tile to m_tilemap
				Tile tile = loadTile(tile_data[tile_counter], tile_counter);
				m_tilemap.push_back(tile);
			}
			catch(std::exception& e){
				std::cout << e.what() << std::endl;
			}
		}
	}
}


void Level::loadMapData(tinyxml2::XMLElement* pMapNode){
	// Get the width and the height of the whole map and store it in m_mapSize
	pMapNode->QueryIntAttribute("width", &m_mapSize.x);
	pMapNode->QueryIntAttribute("height", &m_mapSize.y);

	// Get the width and the height of the tiles and store it in m_tileSize
	pMapNode->QueryIntAttribute("tilewidth", &m_tileSize.x);
	pMapNode->QueryIntAttribute("tileheight", &m_tileSize.y);
}


TileSet Level::loadTileSet(tinyxml2::XMLElement* pTileset){
	using namespace tinyxml2;

	TileSet tileset;

	// Get tileset firstgid
	pTileset->QueryIntAttribute("firstgid", &tileset.first_gid);

	// Get tileset data source.
	std::stringstream tileset_source;
	tileset_source << "maps/" << pTileset->Attribute("source");

	// Open the *.tsx file with the tileset data
	XMLDocument tileset_doc;
	if(tileset_doc.LoadFile(tileset_source.str().c_str()) != XML_SUCCESS)
		throw std::runtime_error("TileSet: " + tileset_source.str() + " not found");

	XMLElement* pTileSetNode = tileset_doc.FirstChildElement("tileset");

	// Set the tileset texture path
	std::string texture_path = pTileSetNode->FirstChildElement("image")->Attribute("source");
	tileset.setTexturePath(texture_path);

	// Get the tile width, height, spacing, tilecount, etc
	pTileSetNode->QueryIntAttribute("tilewidth", &tileset.tilewidth);
	pTileSetNode->QueryIntAttribute("tileheight", &tileset.tileheight);
	pTileSetNode->QueryIntAttribute("spacing", &tileset.tilespacing);
	pTileSetNode->QueryIntAttribute("tilecount", &tileset.tilecount);

	// tileset.bounds.allocate(tilecount);

	for(XMLElement* pTile = pTileSetNode->FirstChildElement("tile"); pTile != NULL;
						pTile = pTile->NextSiblingElement("tile")){
		int tile_id;
		pTile->QueryIntAttribute("id", &tile_id);

		// XMLElement* pTileBound = pTile->FirstChildElement("objectgroup")->FirstChildElement("object");

		// bounds[tile_id].name = pTileBound->Attribute("name");
		// bounds[tile_id].type = pTileBound->Attribute("type");
		// pTileBound->QueryIntAttribute("x", &bounds[tile_id].x);
		// pTileBound->QueryIntAttribute("y", &bounds[tile_id].y);
		// pTileBound->QueryIntAttribute("width", &bounds[tile_id].width);
		// pTileBound->QueryIntAttribute("height", &bounds[tile_id].height);
	}

	return tileset;	
}


std::vector<long long int> parse_csv_data_to_ints(const char* _data){
	std::stringstream data(_data);
	std::vector<long long int> tile_data;
	long long int i;
    while (data >> i){
        tile_data.push_back(i);
        if (data.peek() == ',')
            data.ignore();
    }
	return tile_data;
}


Tile Level::loadTile(long long int tile_data, int tile_counter){
	//Parse the tile_data. The bits at position 28, 29, 30 represent the following flags.
	bool horizontalFlip = tile_data & 0x80000000;
	bool verticalFlip = tile_data & 0x40000000;
	bool diagonalFlip = tile_data & 0x20000000;

	int horizontalScale = (horizontalFlip & !diagonalFlip)? -1 : 1;
	int verticalScale = (verticalFlip & !diagonalFlip) ? -1 : 1;
	float rotation = diagonalFlip ? (horizontalFlip ? 90.f : -90.f) : 0.f; 

	int tileID = tile_data & ~(0x80000000 | 0x40000000 | 0x20000000); //clear the flags
	sf::Vector2f scale(horizontalScale, verticalScale);

	//Get the tileset for this specific tileID
	int tileset_index = -1;
	for(long unsigned int i=0; i<m_tilesets.size(); ++i){
		if(tileID >= m_tilesets[i].first_gid 
			&& tileID - m_tilesets[i].first_gid < m_tilesets[i].tilecount)
		{
			tileset_index = i;
			break;
		}
	}
	// No tileset was found for this tileID
	if(tileset_index == -1){ 
		std::stringstream err;
		err << "No tileset found for tile with id: " << tileID << " and tile data: " << tile_data;
		throw std::runtime_error(err.str());
	}
	
	//Get the position of center of the tile in the level
	int xx = m_tileSize.x/2;
	int yy = m_tileSize.y/2;
	xx += getTileWidth() * (tile_counter % getMapWidth()) + 1000;
	yy += getTileHeight() * (tile_counter / getMapWidth());
	
	int y_offset = getMapSize().y - CONSTANTS::GROUNDHEIGHT;
	yy -= y_offset;

	return Tile(m_tilesets[tileset_index], tileID, xx, yy, scale, rotation);
}