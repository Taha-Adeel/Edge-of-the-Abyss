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
 * @param filename File path of texture relative to ./maps
 * @param _first_gid gid (Obtained on parsing *.tmx files) of the first tile in the tileset.
 */
TileSet::TileSet(std::string filename, int _first_gid):
	first_gid(_first_gid)
{
	std::string assets_path = "../assets/";
	std::string texture_extension = ".png";
	auto pos1 = filename.find(assets_path);
	if(pos1 != std::string::npos)
		filename.erase(pos1, assets_path.length());

	auto pos2 = filename.find(texture_extension);
	if(pos2 != std::string::npos)
		filename.erase(pos2, texture_extension.length());

	this->texture = filename;
}