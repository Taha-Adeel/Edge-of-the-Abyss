#include <cmath>

#include "Ground.h"
#include "../States/PlayingState.h"
#include "../Util/Constants.h"

Ground::Ground(std::string name, sf::Color ground_ground_color, PlayingState& context):
	m_refPlayingState(context),
	m_ground_texture("grounds/"+name),
	m_ground_color(ground_ground_color),
	m_ground_line(sf::Vector2f(CONSTANTS::WINDOW_WIDTH, 1.f))
{
	init_ground();
}

void Ground::init_ground(){
	Sprite ground_tile(m_ground_texture);
	m_ground_scale = 1.f;
	ground_tile.setScale(m_ground_scale, m_ground_scale);
	m_num_of_groundSprites = floor(CONSTANTS::WINDOW_WIDTH / ground_tile.getGlobalBounds().width + 2);
	
	m_ground_line.setPosition(0.f, CONSTANTS::GROUNDHEIGHT);
	m_ground_bg.setSize(sf::Vector2f(CONSTANTS::WINDOW_WIDTH, ground_tile.getGlobalBounds().height));
	m_ground_bg.setPosition(0.f, CONSTANTS::GROUNDHEIGHT + m_ground_line.getGlobalBounds().height);
	m_ground_bg.setFillColor(m_ground_color);

	for(int i=0; i<m_num_of_groundSprites; ++i){
		m_groundSprites.push_back(ground_tile);
		m_groundSprites[i].setPosition(i * m_groundSprites[i].getGlobalBounds().width, CONSTANTS::GROUNDHEIGHT + m_ground_line.getGlobalBounds().height);	
	}
}

void Ground::update(sf::Time dt){
	const Camera& camera = m_refPlayingState.getCamera();

	m_ground_bg.setPosition(camera.getPosition().x, m_ground_bg.getPosition().y);
	m_ground_line.setPosition(camera.getPosition().x, m_ground_line.getPosition().y);

	for(auto& ground_tile: m_groundSprites){
		if(ground_tile.getPosition().x-camera.getPosition().x < -ground_tile.getGlobalBounds().width){
			float max_x = ground_tile.getPosition().x;
			for(auto& tile: m_groundSprites){
				max_x = (tile.getPosition().x > max_x) ? tile.getPosition().x : max_x;
			}
			ground_tile.setPosition(max_x + ground_tile.getGlobalBounds().width, ground_tile.getPosition().y);
		}
	}
}

void Ground::render(sf::RenderTarget& renderer){
	renderer.draw(m_ground_bg);
	for(auto& ground_tile: m_groundSprites){
		renderer.draw(ground_tile);
	}
	renderer.draw(m_ground_line);
}