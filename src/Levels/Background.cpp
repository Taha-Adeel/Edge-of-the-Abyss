#include "Background.h"
#include "../States/PlayingState.h"

Background::Background(std::string name, sf::Color bg_color, PlayingState& context):
	m_refPlayingState(context),
	m_bg_texture("backgrounds/"+name),
	m_bg_color(bg_color),
	m_bg_velocity(30.f),
	m_bg_top_y_coord(-500.f),
	m_bg_scale(1.f),
	m_num_of_bgSprites(3)
{
	init_bgSprites();
}

void Background::init_bgSprites(){
	for(int i=0; i<m_num_of_bgSprites; ++i){
		m_bgSprites.emplace_back(Sprite(m_bg_texture));
		m_bgSprites[i].setScale(m_bg_scale, m_bg_scale);
		m_bgSprites[i].setPosition(i * m_bgSprites[i].getGlobalBounds().width, m_bg_top_y_coord);	
	}
}

void Background::update(sf::Time dt){
	// m_rect.left += 1;
	// // m_rect.left = static_cast<int>(m_rect.left + dt.asSeconds()*m_bgVelocity) % 512;
	// m_bg.setTextureRect(m_rect);
}

void Background::render(sf::RenderTarget& renderer){
	renderer.draw(m_bg);
}