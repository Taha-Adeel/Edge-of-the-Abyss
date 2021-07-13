#include "Player.h"
#include <iostream>

// Functions for class Player

// Constructors and Destructors
Player::Player():sprite("player/spritesheet", 29)
{
}
Player::~Player(){}
// Accessors
const sf::Vector2f Player::getPosition() const
{
    return this->sprite.getPosition();
}
const sf::FloatRect Player::getGlobalBounds() const
{
    return this->sprite.getGlobalBounds();
}
const sf::Vector2f Player::getOrigin() const
{
    return this->sprite.getOrigin();
}
const float Player::getRotation() const
{
    return this->sprite.getRotation();
}
// Modifier
void Player::setPosition(const float x, const float y){
    this->sprite.setPosition(x, y);
}
void Player::setOrigin(const float x, const float y){
    this->sprite.setOrigin(x, y);
}
void Player::setRotation(const float angle)
{
    this->sprite.setRotation(angle);
}
void Player::rotate(const float angle)
{
    this->sprite.rotate(angle);
}

//Movement
void Player::move(const float dir_x, const float dir_y)
{
    this->sprite.move(dir_x, dir_y);
}
/**
 * @brief For moving the sprite as per velocity in that instant
 * 
 * @param elapsedTime 
 */
void Player::updateMovement(sf::Time elapsedTime)
{
    float eTime = elapsedTime.asSeconds();
    float dx = eTime* this->velocity.x;
    float dy = eTime* this->velocity.y;
    std::cout<<dx<<" "<<dy<<"::"<<sprite.getPosition().x<<" "<<sprite.getPosition().y<<std::endl;
    this->move(dx, dy);
}
//Update and Render
void Player::update(sf::Time elapsedTime)
{
    this->updateMovement(elapsedTime);
    this->updatePhysics(elapsedTime);
}
void Player::render(sf::RenderTarget& target)
{
    target.draw(this->sprite);
}
// Functions for class NormalPlayer


