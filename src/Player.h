#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
enum PLAYER_STATES {STAY = 0,JUMPING, FALLING};

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;


	//Physics
	sf::Vector2f velocity;
	float gravity;

	//Core

	void initVariables();
	void initTexture();
	void initSprite();
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
	void updatePhysics();
	void updateMovement();
	void update();
	void render(sf::RenderTarget& target);
};
#endif