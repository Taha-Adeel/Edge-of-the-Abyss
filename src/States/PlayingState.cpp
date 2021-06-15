#include "PlayingState.h"

/**
 * @brief Delegates event handeling to player, camera, etc
 * 
 * @param ev sf::Event
 */
void PlayingState::handleEvent(sf::Event ev){
	//Event handeling to change state can be done here.
	
	// m_player.handleEvent(ev);
}

/**
 * @brief Updates player, camera(view), etc
 * 
 * @param dt Time for which the last frame ran
 */
void PlayingState::update(sf::Time dt){
	// m_player.update(dt);
	// m_camera.update(dt);
}

/**
 * @brief Renders everything on to the window
 * 
 * @param renderer 
 */
void PlayingState::render(sf::RenderTarget& renderer){

}