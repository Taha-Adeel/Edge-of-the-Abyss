#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "Util/Sprite.h"

enum class PLAYER_STATES {STAY,JUMPING};

class Player
{
private:
	Sprite sprite;

	//Physics
	sf::Vector2f velocity;
	float timeAbove;
	float maxTimeAbove;

	//Core
    PLAYER_STATES playerState;
	void initVariables();
	void initPhysics();

public:
	Player();
	virtual ~Player();

	//Accessors
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;

	//Modifiers
	void setPosition(const float x, const float y);
	void resetVelocityY();

	//Functions	
	void move(const float dir_x, const float dir_y);
	void updateMovement(sf::Time elapsedTime);
	void updatePhysics(sf::Time elapsedTime);
	//void updatePlayerState();
	void handleEvent(sf::Event ev);
	void update(sf::Time elapsedTime);
	void render(sf::RenderTarget& target);
};
#endif