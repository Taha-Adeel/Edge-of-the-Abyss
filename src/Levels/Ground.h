#ifndef GROUND_H
#define GROUND_H

#include "../Util/Sprite.h"

class PlayingState;

class Ground{
public:
	Ground(std::string name, sf::Color bg_color, PlayingState& context);

	void update(sf::Time dt);
	void render(sf::RenderTarget& renderer);

private:
	PlayingState& m_refPlayingState;
	Sprite m_ground;
	int m_bgVelocity = 500;
	sf::IntRect m_rect;
	sf::RectangleShape line;
	sf::RectangleShape ground;
};

#endif