#include "NormalPlayer.h"
#include <iostream>
//Constructor
NormalPlayer::NormalPlayer()
{
    // Player() automatically called, thus initVariables() and initPhysics() are called implicitly 
}
NormalPlayer::~NormalPlayer(){}
//Init Functions
void NormalPlayer::initVariables()
{
    this->playerState = PLAYER_STATES::ON_GROUND;
    this->setPosition(CONSTANTS::SPAWNPOINT_X, CONSTANTS::SPAWNPOINT_Y);
}
void NormalPlayer::initPhysics()
{
    this->velocity.x = CONSTANTS::PLAYER_SPEED_X;
    this->velocity.y = CONSTANTS::PLAYER_SPEED_Y;
    this->timeAbove = 0.f;
    this->maxTimeAbove = 60.f; // 1 second (60 frames)
}
//Functions
void NormalPlayer::resetVelocityY()
{
    this->velocity.y = 0.f;
}
/**
 * @brief For updating and changing velocities in normal mode
 * 
 * @param elapsedTime 
 */
void NormalPlayer::updatePhysics(sf::Time elapsedTime)
{
    float eTime = elapsedTime.asSeconds();
    if(this->playerState == PLAYER_STATES::ON_GROUND){
        // do nothing
    }
    else if(this->playerState == PLAYER_STATES::ON_AIR)
    {   
        this->velocity.y += eTime * CONSTANTS::GRAVITY;
        if(this->sprite.getPosition().y>=CONSTANTS::GROUNDHEIGHT)
        {
            this->resetVelocityY();
            this->sprite.setPosition(Player::getPosition().x, CONSTANTS::GROUNDHEIGHT);
            this->playerState = PLAYER_STATES::ON_GROUND;
        }

    }
}
void NormalPlayer::handleEvent(sf::Event ev)
{
    if(playerState == PLAYER_STATES::ON_GROUND) // Cannot control player midair
    {
        if(ev.key.code == sf::Keyboard::Up || ev.key.code == sf::Keyboard::Space)
        {
            std::cout<<"Pressed Jump"<<std::endl;
            this->velocity.y += CONSTANTS::PLAYER_JUMP_BOOST;
            playerState = PLAYER_STATES::ON_AIR;
        }
    }
}
