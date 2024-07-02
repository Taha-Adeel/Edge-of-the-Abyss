#ifndef GROUND_H
#define GROUND_H

#include "../Util/Sprite.h"

// Forward Declared Dependencies
class PlayingState;

/**
 * @brief Draws an "infinite" Ground at CONSTANTS::GROUNDHEIGHT
 * 
 * Has a vector of Sprites with the grounds texture, and shifts the sprites that
 * go outside the view on the left to right of the ground sprite furthest from the left.
 * 
 */
class Ground{
public:
	// constructors
	Ground(std::string name, sf::Color ground_bg_color, PlayingState* context);

	// public member functions
	void update(sf::Time dt);
	void render(sf::RenderTarget& renderer);

private:
	// private member variables
	PlayingState* m_pPlayingState;
	std::string m_ground_texture;
	sf::Color m_ground_color;
	
	float m_ground_scale;

	int m_num_of_groundSprites;
	std::vector<Sprite> m_groundSprites;
	sf::RectangleShape m_ground_bg;
	sf::RectangleShape m_ground_line;

	// private member function
	void init_ground();
};

#endif