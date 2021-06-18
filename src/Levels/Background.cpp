#include "Background.h"

Background::Background(std::string name, sf::Color bg_color):
							m_bg("backgrounds/"+name){
	m_bg.setColor(bg_color);
	m_rect = {0,106,1280,512};
	m_bg.setTextureRect(m_rect);
	m_bg.setScale(1.7, 1.7);
}

void Background::update(sf::Time dt){
	m_rect.left += 1;
	// m_rect.left = static_cast<int>(m_rect.left + dt.asSeconds()*m_bgVelocity) % 512;
	m_bg.setTextureRect(m_rect);
}

void Background::render(sf::RenderTarget& renderer){
	renderer.draw(m_bg);
}