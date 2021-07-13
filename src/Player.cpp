#include "Player.h"
#include "Util/Constants.h"
#include <iostream>

// Init Functions
void Player::initVariables()
{
    this->playerState = PLAYER_STATES::STAY;
    this->setPosition(CONSTANTS::SPAWNPOINT_X, CONSTANTS::SPAWNPOINT_Y);
}
void Player::initPhysics()
{
    this->velocity.x = CONSTANTS::PLAYER_SPEED_X;
    this->velocity.y = CONSTANTS::PLAYER_SPEED_Y;
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
Player::Player():sprite("player/spritesheet", 29)
{
    this->initVariables();
    this->initPhysics();
}
Player::~Player(){}

// Functions
void Player::setPosition(const float x, const float y){
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
    // std::cout<<dx<<" "<<dy<<"::"<<sprite.getPosition().x<<" "<<sprite.getPosition().y<<std::endl;
    this->move(dx, dy);
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
        this->velocity.y += eTime * CONSTANTS::GRAVITY;
        if(this->sprite.getPosition().y+42>=CONSTANTS::GROUNDHEIGHT)
        {
            this->resetVelocityY();
            this->sprite.setPosition(Player::getPosition().x, CONSTANTS::GROUNDHEIGHT-42);
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
            // std::cout<<"Pressed W"<<std::endl;
            this->velocity.y += CONSTANTS::PLAYER_JUMP_BOOST;
            playerState = PLAYER_STATES::JUMPING;
        }
    }
}

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