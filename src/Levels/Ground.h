#ifndef GROUND_H
#define GROUND_H

#include "../Util/Sprite.h"

class PlayingState;

class Ground{
public:
	Ground(std::string name, sf::Color ground_bg_color, PlayingState& context);

	void update(sf::Time dt);
	void render(sf::RenderTarget& renderer);

private:
	PlayingState& m_refPlayingState;
	std::string m_ground_texture;
	sf::Color m_ground_color;
	
	float m_ground_scale;

	int m_num_of_groundSprites;
	std::vector<Sprite> m_groundSprites;
	sf::RectangleShape m_ground_bg;
	sf::RectangleShape m_ground_line;

	void init_ground();
};

#endif