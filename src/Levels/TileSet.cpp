#include "TileSet.h"

/**
 * @brief Default constructor that constructs a new TileSet object
 * 
 * Sets first_gid = -1 (which implies tileset hasn't been initialized, as gid >= 0)
 * 
 */
TileSet::TileSet(){
	this->first_gid = -1;
}

/**
 * @brief Construct a new Tile Set:: Tile Set object
 * 
 * @param filename File path of texture relative to AssetPool::m_folder (=./assets/)
 * @param _first_gid gid (Obtained on parsing *.tmx files) of the first tile in the tileset.
 */
TileSet::TileSet(std::string filename, int _first_gid):
	texture(filename),
	first_gid(_first_gid){
}