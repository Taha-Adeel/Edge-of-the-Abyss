#include <iostream>

#include "PlayingState.h"
#include "../Game.h"

/**
 * @brief Construct a new Playing State object
 * 
 * @param pGame Reference to the game object (context), so that it can access its contents
 * 	and change its state(if neccesary).
 */
PlayingState::PlayingState(Game& pGame):
	StateBase(pGame),
	m_player(std::make_unique<PlanePlayer>(this)),
	m_level(CONSTANTS::LEVELS[0], this),
	m_camera(this)
{
}
/**
 * @brief Delegates event handeling to player, camera, etc
 * 
 * @param ev sf::Event
 */
void PlayingState::handleEvent(sf::Event& ev){
	//Event handeling to change state can be done here.
	m_player->handleEvent(ev);
}

/**
 * @brief Updates player, camera(view), etc
 * 
 * @param dt Time for which the last frame ran
 */
void PlayingState::update(sf::Time dt){
	m_player->update(dt);
	m_camera.update(dt);
	m_level.update(dt);
}

/**
 * @brief Renders everything on to the window
 * 
 * @param renderer 
 */
void PlayingState::render(sf::RenderTarget& renderer){
	m_camera.render(renderer);
	m_level.render(renderer);
  	m_player->render(renderer);
}

void PlayingState::goToNextLevel(){
	if(m_level.getLevelNumber() < CONSTANTS::LEVELS.size() - 1){
		m_player->setTopLeftPosition(CONSTANTS::SPAWNPOINT_X, CONSTANTS::SPAWNPOINT_Y);
		m_camera.reset();
		m_level = Level(CONSTANTS::LEVELS[m_level.getLevelNumber()+1], this);
	}
	else{
		std::cout << "You win!!" << std::endl;
		Game::getGameInstance().exitGame();
	}
}

/**
 * @brief Get the Player object
 * 
 * @return const Player& 
 */
const Player& PlayingState::getPlayer() const {
	return *m_player.get();
}

/**
 * @brief Get the Camera object
 * 
 * @return const Camera& 
 */
Camera& PlayingState::getCamera() {
	return m_camera;
}

/**
 * @brief Get the current Level
 * 
 * @return const Level& 
 */
const Level& PlayingState::getCurrentLevel() const {
	return m_level;
}
