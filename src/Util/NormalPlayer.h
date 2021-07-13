#ifndef NORMAL_PLAYER_H
#define NORMAL_PLAYER_H
#include "Player.h"
class NormalPlayer : public Player
{
private:
	float timeAbove;
	float maxTimeAbove;

	//Core logic
	void initVariables() override;
	void initPhysics() override;
public:
	NormalPlayer();
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