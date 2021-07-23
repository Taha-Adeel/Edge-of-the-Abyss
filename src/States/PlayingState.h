#ifndef PLAYING_STATE_H
#define PLAYING_STATE_H

#include "StateBase.h"
#include "../Players/NormalPlayer.h"
#include "../Players/PlanePlayer.h"
#include "../Levels/Level.h"
#include "../Camera.h"
#include "../Util/Score.h"

enum class GAMEMODE{NORMAL, PLANE, REVERSE};
enum class NEXTFRAMEACTION{NOTHING, NORMAL, PLANE, REVERSE};
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
	GAMEMODE m_gameMode;
	NEXTFRAMEACTION nextFrameAction;

public:
	// constructors
	PlayingState(Game& pGame) ;

	// public functions
	void displayGameEnd();
	void changeGameMode(GAMEMODE gameMode);
	void switchGameMode();
	void setNextFrameAction(NEXTFRAMEACTION _nextFrameAction);
	void resetGameMode();

	void handleEvent(sf::Event&) override ;
    void update(sf::Time) override ;
    void render(sf::RenderTarget& renderer) override ;
	// public accessors
	const Player& getPlayer() const ;
	Camera& getCamera();
	const Level& getCurrentLevel() const ;
	const NEXTFRAMEACTION getNextFrameAction() const;
	const GAMEMODE getGameMode() const;
	
};

#endif