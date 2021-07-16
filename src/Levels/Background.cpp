#include <iostream>
#include <cmath>
#include "Background.h"
#include "../States/PlayingState.h"

Background::Background(std::string name, sf::Color bg_color, PlayingState& context):
	m_refPlayingState(context),
	m_bg_texture("backgrounds/"+name),
	m_bg_color(bg_color),
	m_bg_velocity(-30.f, -30.f),
	m_bg_top_y_coord(-100.f)
{
	init_bgSprites();
}

void Background::init_bgSprites(){
	Sprite bg_tile(m_bg_texture);
	m_bg_scale = (CONSTANTS::GROUNDHEIGHT - m_bg_top_y_coord) / bg_tile.getGlobalBounds().height;
	bg_tile.setScale(m_bg_scale, m_bg_scale);
	m_num_of_bgSprites = floor(CONSTANTS::WINDOW_WIDTH / bg_tile.getGlobalBounds().width + 2);
	
	for(int i=0; i<m_num_of_bgSprites; ++i){
		m_bgSprites.push_back(bg_tile);
		m_bgSprites[i].setPosition(i * m_bgSprites[i].getGlobalBounds().width, m_bg_top_y_coord);	
	}
}

void Background::update(sf::Time dt){
	const Camera& camera = m_refPlayingState.getCamera();
	sf::Vector2f camera_velocity = camera.getVelocity();
	if(camera_velocity.x > 1.f){
		for(auto& bg_tile: m_bgSprites){
			float dx = (camera_velocity.x + m_bg_velocity.x) * (dt.asSeconds());
			bg_tile.move(dx, 0);
		}
	}
	if(camera_velocity.y > 1.f){
		for(auto& bg_tile: m_bgSprites){
			float dy = (camera_velocity.y + m_bg_velocity.y) * (dt.asSeconds());
			bg_tile.move(0, dy);
		}
	}
	for(auto& bg_tile: m_bgSprites){
		if(bg_tile.getPosition().x-camera.getPosition().x < -bg_tile.getGlobalBounds().width){
			float max_x = bg_tile.getPosition().x;
			for(auto& tile: m_bgSprites){
				max_x = (tile.getPosition().x > max_x) ? tile.getPosition().x : max_x;
			}
			bg_tile.setPosition(max_x + bg_tile.getGlobalBounds().width, bg_tile.getPosition().y);
		}
	}
}

void Background::render(sf::RenderTarget& renderer){
	for(auto& bg_tile: m_bgSprites){
		renderer.draw(bg_tile);
	}
}