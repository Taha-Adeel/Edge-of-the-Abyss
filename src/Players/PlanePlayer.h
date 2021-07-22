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
	//Core logic
	void initVariables() override;
	void initPhysics() override;

	void resolveTileCollision(const BoxBound& tile) override;
	
public:
	PlanePlayer(PlayingState& context);
	virtual ~PlanePlayer();

	//Functions
    void updateRotation(sf::Time elapsedTime) override;
	void updateVelocity(sf::Time elapsedTime) override;
};
#endif