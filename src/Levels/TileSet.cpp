#include "TileSet.h"

/**
 * @brief Set the texture path of the tileset.
 * 
 * @param filename File path of texture relative to ./maps
 */
void TileSet::setTexturePath(std::string filename){
	std::string assets_path = "../../assets/";
	std::string texture_extension = ".png";
	auto pos1 = filename.find(assets_path);
	if(pos1 != std::string::npos)
		filename.erase(pos1, assets_path.length());

	auto pos2 = filename.find(texture_extension);
	if(pos2 != std::string::npos)
		filename.erase(pos2, texture_extension.length());

	this->m_texture = filename;
}

const std::string TileSet::getTexturePath() const {
	return m_texture;
}