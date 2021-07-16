#ifndef PLAYING_STATE_H
#define PLAYING_STATE_H

#include "StateBase.h"
#include "../Players/NormalPlayer.h"
#include "../Levels/Level.h"
#include "../Camera.h"


/**
 * @brief Main game play state.
 *  
 */
class PlayingState: public StateBase{
private:
	// private member variables
	std::unique_ptr<Player> m_player;
	Level m_level;
	Camera m_camera;

public:
	// constructors
	PlayingState(Game& pGame) ;

	// public functions
	void handleEvent(sf::Event&) override ;
    void update(sf::Time) override ;
    void render(sf::RenderTarget& renderer) override ;

	// public accessors
	const Player& getPlayer() const ;
	const Camera& getCamera() const ;
	const Level& getCurrentLevel() const ;
};

#endif