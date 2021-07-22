#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "../Util/Sprite.h"
#include "../Util/Constants.h"
#include "../Util/BoxBound.h"
#include "../Levels/Tile.h"

// Forward Declared Dependencies
class PlayingState;

// enum class GRAVITY_STATE {NORMAL = 1, FLIPPED = -1};

/**
 * @brief Defines an interface for Player classes. Player class manages the physics.
 * 
 */
class Player
{
protected:
	Sprite sprite;
	PlayingState& m_ref_PlayingState;
	BoxBound playerBounds;

	//Physics
    // GRAVITY_STATE gravity_state;
	sf::Vector2f velocity;
	bool keyHeld = false;

	//Core
	virtual void initVariables() = 0;
	virtual void initPhysics() = 0;

	virtual bool resolveGroundCollision();

	void resolveCollision(const Bound& bound);

	virtual void resolveTileCollision(const BoxBound& bound);
	void snapToSide(const BoxBound& tile,const SIDE collisionside);

	virtual void resolveSpikeCollision(const Bound& bound);
	virtual void resolvePortalCollision(const BoxBound& bound);
	
public:
	Player(PlayingState& context);
	virtual ~Player();

	//Accessors
	const sf::Vector2f getTopLeftPosition() const;
	const sf::Vector2f getCenter() const;
	const float getRotation() const;
	const sf::Vector2f getVelocity() const;
	const BoxBound& getplayerBounds() const;
	const float getWidth() const;
	const float getHeight() const;

	//Modifiers
	void setTopLeftPosition(const float x, const float y);
	void setCenter(const float x, const float y);
	void setRotation(const float angle);
	void setVelocity(const float x, const float y);
	void rotate(const float angle);
	void resetVelocityY();
	// void flipGravity();
	void die();

	//Functions	
	void move(const float dir_x, const float dir_y);
	virtual void updateMovement(sf::Time elapsedTime);
	virtual void updateRotation(sf::Time elapsedTime);
	virtual void updateVelocity(sf::Time elapsedTime) = 0; // Physics may change on the mode of the game
	
	void handleEvent(sf::Event ev);
	void update(sf::Time elapsedTime);
	void render(sf::RenderTarget& target);
};


#endif