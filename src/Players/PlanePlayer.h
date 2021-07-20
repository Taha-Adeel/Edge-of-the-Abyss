#ifndef PLANE_PLAYER_H
#define PLANE_PLAYER_H
#include "Player.h"
/**
 * @brief Player class for the plane game mode
 * 
 */

class PlanePlayer : public Player
{
private:
	// float timeAbove;
	bool onAir;

	//Core logic
	void initVariables() override;
	void initPhysics() override;
public:
	PlanePlayer();
	virtual ~PlanePlayer();

	//Modifiers
	void resetVelocityY();
	void setOnAir(bool _onAir = true);
    //void resetNearestOrientation();

	//Functions
    void updateMovement(sf::Time elapsedTime) override;
	void updateVelocity(sf::Time elapsedTime) override;
};
#endif