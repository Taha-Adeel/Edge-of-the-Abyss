#ifndef TILESET_H
#define TILESET_H	

#include <string>

/**
 * @brief Container for the tilesets obtained on parsing our Level files(*.tmx files)
 * 
 */
struct TileSet{
	TileSet();
	TileSet(std::string filename, int _first_gid);

	std::string texture;/**<Filename of file(relative to ./assets) in which the Tile Set texture is stored*/
	int first_gid;/**<gid (Obtained on parsing *.tmx files) of the first tile in the tileset*/
};

#endif