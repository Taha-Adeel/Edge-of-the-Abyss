#ifndef TILESET_H
#define TILESET_H	

#include <string>
#include <vector>

// class Bound;

/**
 * @brief Container for the tilesets obtained on parsing our Level files(*.tmx files)
 * 
 */
class TileSet{
public:
	TileSet() = default;

	int first_gid;/**<gid (Obtained on parsing *.tmx files) of the first tile in the tileset*/
	int tilewidth = 0;
	int tileheight = 0;
	int tilecount = 0;
	int tilespacing = 0;

	// std::vector<Bound> tile_bounds;

	void setTexturePath(std::string);
	const std::string getTexturePath() const;

private:
	std::string m_texture;/**<Filename of file(relative to ./assets) in which the Tile Set texture is stored*/
};

#endif