#include "Background.h"
#include "../States/PlayingState.h"
#include "../Util/Constants.h"

#include <cmath>

/**
 * @brief Construct a new Background::Background object
 * 
 * @param name Filename (relative to ./assests/backgrounds/) of file containing the background texture.
 * @param bg_color 
 * @param context Reference to the PlayingState object (to access the camera object)
 */
Background::Background(std::string name, sf::Color bg_color, PlayingState& context):
	m_refPlayingState(context),
	m_bg_texture("backgrounds/"+name),
	m_bg_color(bg_color),
	m_bg_velocity(CONSTANTS::BG_VELOCITY),
	m_bg_top_y_coord(-300.f)
{
	init_bgSprites();
}

/**
 * @brief Initializes the vector of sprites with the background texture.
 * 
 */
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

/**
 * @brief Updates the background every frame.
 * 
 * Moves the background slowly behind w.r.t to camera to create the parallax effect.
 * Doesnt move the background if Camera isn't moving. Reuses the same sprites to create
 * an "infinite" background.
 * 
 * @param dt 
 */
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
	if(camera_velocity.y < -1.f){
		for(auto& bg_tile: m_bgSprites){
			float dy = (camera_velocity.y - m_bg_velocity.y) * (dt.asSeconds());
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
		if(bg_tile.getPosition().x-camera.getPosition().x > camera.getSize().x){
			float min_x = bg_tile.getPosition().x;
			for(auto& tile: m_bgSprites){
				min_x = (tile.getPosition().x < min_x) ? tile.getPosition().x : min_x;
			}
			bg_tile.setPosition(min_x - bg_tile.getGlobalBounds().width, bg_tile.getPosition().y);
		}
	}
}

/**
 * @brief Renders the background on to the renderer
 * 
 * @param renderer 
 */
void Background::render(sf::RenderTarget& renderer){
	for(auto& bg_tile: m_bgSprites){
		renderer.draw(bg_tile);
	}
}