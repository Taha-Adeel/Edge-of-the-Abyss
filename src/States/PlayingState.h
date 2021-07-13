#ifndef PLAYING_STATE_H
#define PLAYING_STATE_H

#include "StateBase.h"
#include "../Player.h"
#include "../camera.h"
#include "../Levels/Background.h"
#include "../Levels/Ground.h"
#include"../camera.h"
// #include "Player.h"
// #include "Level.h"


/**
 * @brief Main game play state.
 * 
 */
//class Player;
class PlayingState: public StateBase{
private:
	Player m_player;
	// Level m_level;
	Camera m_camera;
	Background m_bg;
	Ground m_ground;

public:
	/**
	 * @brief Construct a new Playing State object
	 * 
	 * @param pGame Reference to the game object (context), so that it can access its contents
	 * 	and change its state(if neccesary).
	 */
	PlayingState(Game& pGame): StateBase(pGame),m_camera(m_player), m_bg("bg01"), m_ground("ground01"){}

	void handleEvent(sf::Event&) override ;
    void update(sf::Time) override ;
    void render(sf::RenderTarget& renderer) override ;
};

#endif