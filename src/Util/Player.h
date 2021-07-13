#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "Sprite.h"
#include "Constants.h"

enum class PLAYER_STATES {ON_AIR, ON_GROUND};

class Player
{
protected:
	Sprite sprite;

	//Physics
	sf::Vector2f velocity;
	

	//Core
    PLAYER_STATES playerState;
	virtual void initVariables() = 0;
	virtual void initPhysics() = 0;

public:
	Player();
	virtual ~Player();

	//Accessors
	virtual const sf::Vector2f getPosition() const;
	virtual const sf::FloatRect getGlobalBounds() const;

	//Modifiers
	virtual void setPosition(const float x, const float y);
	

	//Functions	
	virtual void move(const float dir_x, const float dir_y);
	virtual void updateMovement(sf::Time elapsedTime);
	virtual void updatePhysics(sf::Time elapsedTime) = 0; // Physics may change on the mode of the game
	//void updatePlayerState();
	virtual void handleEvent(sf::Event ev)=0;// Different game modes have different controlls
	virtual void update(sf::Time elapsedTime);
	virtual void render(sf::RenderTarget& target);
};


#endif