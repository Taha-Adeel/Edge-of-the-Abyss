#ifndef GROUND_H
#define GROUND_H

#include "../Util/Sprite.h"

class Ground{
public:
	Ground(std::string name, sf::Color bg_color = sf::Color(65, 0, 156));

	void update(sf::Time dt);
	void render(sf::RenderTarget& renderer);

private:
	Sprite m_ground;
	int m_bgVelocity = 500;
	sf::IntRect m_rect;
	sf::RectangleShape line;
	sf::RectangleShape ground;
};

#endif