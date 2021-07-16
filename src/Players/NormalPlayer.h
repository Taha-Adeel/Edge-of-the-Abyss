#ifndef NORMAL_PLAYER_H
#define NORMAL_PLAYER_H
#include "Player.h"
/**
 * @brief Player class for the normal game mode
 * 
 */
class NormalPlayer : public Player
{
private:
	float timeAbove;

	//Core logic
	void initVariables() override;
	void initPhysics() override;
public:
	NormalPlayer(int index = CONSTANTS::DEFAULT_PLAYER_SPRITE_INDEX);
	virtual ~NormalPlayer();

	//Modifiers
	void resetVelocityY();
    void resetPositionY();
    void resetNearestOrientation();
    void resetPlayerState();
	//Functions
    void updateMovement(sf::Time elapsedTime) override;
	void updatePhysics(sf::Time elapsedTime) override;
	void handleEvent(sf::Event ev) override;
};
#endif