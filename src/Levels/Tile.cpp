#include <iostream>
#include <assert.h>
#include <cmath>

#include "Tile.h"
#include "../Util/BoxBound.h"
#include "../Util/Constants.h"

/**
 * @brief Construct a new Tile object
 * 
 * @param tileset Tile set from which the tile gets its texture
 * @param gid gid of the tile in the tileset(Obtained on parsing the *.tmx files)
 * @param x x co-ordinate of the top left corner of the tile in the level
 * @param y y co-ordinate of the top left corner of the tile in the level
 */
Tile::Tile(TileSet& tileset, int gid, float x, float y, sf::Vector2f scale, float rotation):
	m_tileset(tileset),
	m_gid(gid),
	m_position(x,y),
	m_scale(scale),
	m_rotation(rotation),
	m_sprite(m_tileset.getTexturePath(), m_gid - m_tileset.first_gid, 
		m_tileset.tilewidth, m_tileset.tileheight, m_tileset.tilespacing)
{
	m_sprite.setOrigin(CONSTANTS::TILE_WIDTH/2.f, CONSTANTS::TILE_HEIGHT/2.f);
	m_sprite.setPosition(m_position + m_sprite.getOrigin());
	m_sprite.setScale(m_scale);
	m_sprite.rotate(m_rotation);

	loadTileBounds();
}

/**
 * @brief Get the tile bounds
 * 
 * @return const Bound& 
 */
const Bound& Tile::getBounds() const {
	return *(m_pBound.get());
}


/**
 * @brief Constructs a new Bound for the tile.
 * 
 * Constructs it by using information about the untransformed tile from the tileset,
 * and then transforms it based on the tiles transforms.
 * 
 */
void Tile::loadTileBounds(){
	Bound* tile_bound = m_tileset.tile_bounds.at(m_gid-m_tileset.first_gid).get();

	sf::Vector2f tilecenter{CONSTANTS::TILE_WIDTH/2.f, CONSTANTS::TILE_HEIGHT/2.f};

	if(tile_bound->getBoundType() == BOUNDTYPE::BOX){
		sf::Vector2f p = tile_bound->getPosition();
		float w = tile_bound->getWidth();
		float l = tile_bound->getHeight();

		std::vector<sf::Vector2f> untransformed_cords
			{p,{p.x+w, p.y}, {p.x, p.y+l}, {p.x+w, p.y+l}};// relative to to top-left corner
		std::vector<sf::Vector2f> transformed_cords;

		for(auto pt: untransformed_cords){
			pt = pt - tilecenter;// relative position abt center

			assert(fabs(m_scale.x)==1 && fabs(m_scale.y)==1);
			pt = sf::Vector2f(pt.x*m_scale.x, pt.y*m_scale.y);

			assert(static_cast<int>(m_rotation)%90 <= 2);
			double theta = m_rotation * 3.14159265 / 180;
			pt = sf::Vector2f(pt.x*cos(theta) - pt.y*sin(theta)
				, pt.x*sin(theta) + pt.y*cos(theta));

			transformed_cords.push_back(pt);
		}
		std::sort(transformed_cords.begin(), transformed_cords.end()
			,[](sf::Vector2f v1, sf::Vector2f v2){
				return v1.y == v2.y ? v1.x < v2.x : v1.y < v2.y;
			});
		// for(auto pt: transformed_cords){
		// 	sf::Vector2f abs_pos_top_left = m_position + pt + tilecenter;
		// 	std::cout << "(" << abs_pos_top_left.x << ", " << abs_pos_top_left.y << ")";
		// }
		// std::cout << std::endl;
		
		sf::Vector2f abs_pos_top_left = m_position + transformed_cords[0] + tilecenter;
		float width  = transformed_cords[3].x - transformed_cords[0].x;
		float height = transformed_cords[3].y - transformed_cords[0].y;

		// std::cout << "Top left: (" << abs_pos_top_left.x << ", " 
		// 	<< abs_pos_top_left.y << ") width: " << width << " height: " << height << std::endl;

		m_pBound = std::make_unique<BoxBound>(abs_pos_top_left, width, height
			, tile_bound->getBoundName());
	}
	else if (tile_bound->getBoundType() == BOUNDTYPE::TRIANGLE){
		std::cout << "Triangle Bound" << std::endl;
	}
}

/**
 * @brief Updates the Tile Object
 * 
 * @param elapsedTime 
 */
void Tile::update(sf::Time elapsedTime){}


/**
 * @brief Renders the Tile object on to the window
 * 
 * @param renderer 
 */
void Tile::render(sf::RenderTarget& renderer){
	renderer.draw(m_sprite);
}