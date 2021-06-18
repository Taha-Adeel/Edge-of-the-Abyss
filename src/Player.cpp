#include "Player.h"
#include<iostream>
// Init Functions
void Player::initVariables()
{
    this->playerState = PLAYER_STATES::STAY;
    this->groundHeight = 650;
    this->setPosition( 500, 500);
}
void Player::initPhysics()
{
    this->gravity = 1.f;
    this->velocity.x = 50.f;
    this->velocity.y = 0.f;
    this->timeAbove = 0.f;
    this->maxTimeAbove = 60.f; // 1 second (60 frames)
}

// Accessors
const sf::Vector2f Player::getPosition() const
{
    return this->sprite.getPosition();
}
const sf::FloatRect Player::getGlobalBounds() const
{
    return this->sprite.getGlobalBounds();
}

// Constructors and Destructors
Player::Player():sprite("player/spritesheet", 15)
//Player::Player():sprite(sf::Vector2f(44.f, 44.f))
{
    this->initVariables();
    this->initPhysics();
}
Player::~Player(){}

// Functions
void Player::setPosition(const float x, const float y){
    /*float boundx = static_cast<float>(Game::getGameInstance().getWindow().getPosition().x);
    float boundy = static_cast<float>(Game::getGameInstance().getWindow().getPosition().y);
    if(x<= boundx&&y<=boundy && x>=0&&y>=0) this->sprite.setPosition(x, y);*/
    this->sprite.setPosition(x, y);
}
void Player::resetVelocityY()
{
    this->velocity.y = 0.f;
}

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
   // if(this->sprite.getPosition().y >= groundHeight)
    //this->move(0, dy); // Just move with the velocity in that instant
}
/**
 * @brief For updating and changing velocities
 * 
 * @param elapsedTime 
 */
void Player::updatePhysics(sf::Time elapsedTime)
{
    float eTime = elapsedTime.asSeconds();
    if(this->playerState == PLAYER_STATES::STAY){
        // do nothing
    }
    else if(this->playerState == PLAYER_STATES::JUMPING)
    {
        this->velocity.y -= eTime * this->gravity;
        if(this->sprite.getPosition().y<=this->groundHeight)
        {
            this->resetVelocityY();
            this->playerState = PLAYER_STATES::STAY;
        }

    }
}
void Player::handleEvent(sf::Event ev)
{
    if(playerState == PLAYER_STATES::STAY) // Cannot control player midair
    {
        if(ev.key.code == sf::Keyboard::W)
        {
            std::cout<<"Pressed W"<<std::endl;
            this->velocity.y = 50.f;
            playerState = PLAYER_STATES::JUMPING;
        }
    }
}
/*void Player::updatePlayerState()
{
    if(this->velocity.y >0){
        playerState = PLAYER_STATES::JUMPING;
        timeAbove+=1.f;
    }
    else if(this->velocity.y <0){
        playerState = PLAYER_STATES::FALLING;
        timeAbove +=1.f;
    }
    else playerState = PLAYER_STATES::STAY;
}*/
void Player::update(sf::Time elapsedTime)
{
    //this->updatePlayerState();
    this->updateMovement(elapsedTime);
    this->updatePhysics(elapsedTime);
}
void Player::render(sf::RenderTarget& target)
{
    target.draw(this->sprite);
}