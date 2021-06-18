#include "Ground.h"

Ground::Ground(std::string name, sf::Color bg_color):
							m_ground("grounds/"+name),
							line(sf::Vector2f(1280.f, 1.f)),
							ground(sf::Vector2f(1280.f, 150.f)){
	m_ground.setColor(bg_color);
	m_rect = {0,0,2000,256};
	m_ground.setTextureRect(m_rect);
	m_ground.setScale(0.65, 0.8);
	m_ground.setPosition(0, 570);
	ground.setPosition(0, 570);
	ground.setFillColor(bg_color);
	line.setPosition(0, 571);
}

void Ground::update(sf::Time dt){
	m_rect.left = static_cast<int>(m_rect.left + dt.asSeconds()*m_bgVelocity) % 256;
	m_ground.setTextureRect(m_rect);
}

void Ground::render(sf::RenderTarget& renderer){
	renderer.draw(ground);
	renderer.draw(m_ground);
	renderer.draw(line);
}