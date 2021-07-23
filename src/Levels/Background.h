#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <vector>

#include "../Util/Sprite.h"

// Forward Declared Dependencies
class PlayingState;

/**
 * @brief Creates an "infinite" parallax background.
 * 
 * Has a vector of Sprites with the backgrouns texture, and shifts the sprites that
 * go outside the view on the left to right of the background sprite furthest from the left,
 * while moving the background sprites in such a way as to create a parallax effect.
 * 
 */
class Background{
public:
	Background(std::string name, sf::Color bg_color, PlayingState* context);

	void update(sf::Time dt);
	void render(sf::RenderTarget& renderer);

private:
	PlayingState* m_pPlayingState;
	std::string m_bg_texture;
	sf::Color m_bg_color;
	sf::Vector2f m_bg_velocity;

	float m_bg_top_y_coord;
	float m_bg_scale;

	int m_num_of_bgSprites;
	std::vector<Sprite> m_bgSprites;

	void init_bgSprites();
};

#endif