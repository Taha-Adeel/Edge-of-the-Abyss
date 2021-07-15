#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <vector>

#include "../Util/Sprite.h"

class PlayingState;

class Background{
public:
	Background(std::string name, sf::Color bg_color, PlayingState& context);

	void update(sf::Time dt);
	void render(sf::RenderTarget& renderer);

private:
	PlayingState& m_refPlayingState;
	std::string m_bg_texture;
	sf::Color m_bg_color;
	float m_bg_velocity;
	const float m_bg_top_y_coord;
	const float m_bg_scale;

	int m_num_of_bgSprites;
	std::vector<Sprite> m_bgSprites;

	void init_bgSprites();
};

#endif