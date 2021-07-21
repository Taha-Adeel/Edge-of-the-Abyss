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
	// float timeAbove;
	bool onGround;

	//Core logic
	void initVariables() override;
	void initPhysics() override;
public:
	NormalPlayer(PlayingState& context, int index = CONSTANTS::DEFAULT_PLAYER_SPRITE_INDEX);
	virtual ~NormalPlayer();

	//Modifiers
	void resetVelocityY();
	void setOnGround(bool _onGround = true);
    void resetNearestOrientation();

	//Functions
    void updateMovement(sf::Time elapsedTime) override;
	void updateVelocity(sf::Time elapsedTime) override;
	void snapToSurface(const float heightLevel) override;
};
#endif