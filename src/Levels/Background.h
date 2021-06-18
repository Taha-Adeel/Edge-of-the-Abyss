#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../Util/Sprite.h"

class Background{
public:
	Background(std::string name, sf::Color bg_color = sf::Color::Blue);

	void update(sf::Time dt);
	void render(sf::RenderTarget& renderer);

private:
	Sprite m_bg;
	int m_bgVelocity = 60;
	sf::IntRect m_rect;
};

#endif