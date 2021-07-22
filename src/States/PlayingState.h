#ifndef PLAYING_STATE_H
#define PLAYING_STATE_H

#include "StateBase.h"
#include "../Players/NormalPlayer.h"
#include "../Players/PlanePlayer.h"
#include "../Levels/Level.h"
#include "../Camera.h"
#include "../Util/Score.h"

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
	ScoreKeeper m_scoreKeeper;

public:
	// constructors
	PlayingState(Game& pGame) ;

	// public functions
	void handleEvent(sf::Event&) override ;
    void update(sf::Time) override ;
    void render(sf::RenderTarget& renderer) override ;
	// public accessors
	const Player& getPlayer() const ;
	Camera& getCamera();
	const Level& getCurrentLevel() const ;
	void displayGameEnd();
};

#endif