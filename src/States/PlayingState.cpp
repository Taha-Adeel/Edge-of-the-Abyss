#include <iostream>
#include <thread>

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
	m_player(std::make_unique<NormalPlayer>(this)),
	m_level(CONSTANTS::LEVELS[0], this),
	m_camera(this),
	m_scoreKeeper(this),
	m_gameMode(GAMEMODE::NORMAL),
	nextFrameAction(NEXTFRAMEACTION::NOTHING)
{
}

/**
 * @brief makes the scorekeeper update the highscore at the end of the game if needed.
 * 
 */
void PlayingState::displayGameEnd()
{
	m_scoreKeeper.updateHighScore();
}

void PlayingState::setNextFrameAction(NEXTFRAMEACTION flag)
{
	nextFrameAction = flag;
}
const NEXTFRAMEACTION PlayingState::getNextFrameAction() const
{
	return nextFrameAction;
}
/**
 * @brief Changes the current game mode to required mode. Called when portal is used.
 * 		  Preserves the position, orientation and velocity of the player through portals
 * 		  (It takes a GAMEMODE as a parameter instead of merely switching between NORMAL and PLAYER
 * 		  based on current GAMEMODE so that when further game modes are used, it is easy to extend)
 * @param gameMode of type GAMEMODE enum class, NORMAL or PLANE
 */
void PlayingState::changeGameMode(GAMEMODE gameMode)
{
	if(m_gameMode == gameMode)return; // No need to change
	m_gameMode = gameMode;
	std::unique_ptr<Player> oldPlayer = std::move(m_player); // Transfer ownership to new m_player
	if(gameMode == GAMEMODE::NORMAL)
	{
		m_player = std::make_unique<NormalPlayer>(this);
		m_camera.unlock_y();
	}
	else if(gameMode == GAMEMODE::PLANE)
	{
		m_player = std::make_unique<PlanePlayer>(this);
		m_camera.lock_y(m_camera.getPosition().y);
	}
	m_player->setTopLeftPosition(oldPlayer->getTopLeftPosition().x, oldPlayer->getTopLeftPosition().y);
	m_player->setVelocity(oldPlayer->getVelocity().x, oldPlayer->getVelocity().y);
	
	//m_player->setRotation(oldPlayer->getRotation());
}

const GAMEMODE PlayingState::getGameMode() const{
	return m_gameMode;
}
/**
 * @brief Switches between NORMAL and PLANE gameModes. Uses PlayingState::changeGameMode()
 * 
 */
void PlayingState::switchGameMode()
{
	if(m_gameMode == GAMEMODE::NORMAL)this->changeGameMode(GAMEMODE::PLANE);
	else if(m_gameMode == GAMEMODE::PLANE)this->changeGameMode(GAMEMODE::NORMAL);
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
	
	switch(nextFrameAction)
	{
		case NEXTFRAMEACTION::NOTHING:
			break;
		case NEXTFRAMEACTION::NORMAL:
			this->changeGameMode(GAMEMODE::NORMAL);
			break;
		case NEXTFRAMEACTION::PLANE:
			this->changeGameMode(GAMEMODE::PLANE);
			break;
	}
	nextFrameAction = NEXTFRAMEACTION::NOTHING;

	m_player->update(dt);
	m_camera.update(dt);
	m_level.update(dt);
	m_scoreKeeper.update(dt);
}

/**
 * @brief Renders everything on to the window
 * 
 * @param renderer 
 */
void PlayingState::render(sf::RenderTarget& renderer){
	m_camera.render(renderer);
	m_level.render(renderer);
	m_scoreKeeper.render(renderer);
  m_player->render(renderer);
}

void PlayingState::goToNextLevel(){
	if(m_level.getLevelNumber() < CONSTANTS::LEVELS.size() - 1){
		m_player->setTopLeftPosition(CONSTANTS::SPAWNPOINT_X, CONSTANTS::SPAWNPOINT_Y);
		if(m_gameMode != GAMEMODE::NORMAL){
			this->setNextFrameAction(NEXTFRAMEACTION::NORMAL);
		}
		m_camera.reset();
		m_level = Level(CONSTANTS::LEVELS[m_level.getLevelNumber()+1], this);
	}
	else{
		std::cout << "You win!!" << std::endl;
		this->displayGameEnd();
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
