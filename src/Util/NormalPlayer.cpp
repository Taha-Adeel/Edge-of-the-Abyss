#include "NormalPlayer.h"
#include <iostream>
//Constructor
NormalPlayer::NormalPlayer()
{
    this->initVariables();
    this->initPhysics();
}
NormalPlayer::~NormalPlayer(){}
//Init Functions
void NormalPlayer::initVariables()
{
    this->playerState = PLAYER_STATES::ON_GROUND;
    this->setPosition(CONSTANTS::SPAWNPOINT_X, CONSTANTS::SPAWNPOINT_Y);
    this->setOrigin(CONSTANTS::PLAYER_WIDTH/2, CONSTANTS::PLAYER_HEIGHT/2);
    this->setRotation(0.f);
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
void NormalPlayer::resetPositionY()
{
    this->sprite.setPosition(Player::getPosition().x, CONSTANTS::SPAWNPOINT_Y);
}
void NormalPlayer::resetPlayerState()
{
    this->timeAbove = 0.f;
    this->playerState = PLAYER_STATES::ON_GROUND;
}
void NormalPlayer::resetNearestOrientation()
{
   const float angle = this->getRotation(); // get the angle between 0 and 360
   if(angle>=0&&angle<=45)this->setRotation(0.f);
   else if(angle<=135) this->setRotation(90.f);
   else if(angle<=225) this->setRotation(180.f);
   else if(angle<=315) this->setRotation(270.f);
   else this->setRotation(0.f);

}

void NormalPlayer::updateMovement(sf::Time elapsedTime) // overriding
{
    float eTime = elapsedTime.asSeconds();
    float dx = eTime* this->velocity.x;
    float dy = eTime* this->velocity.y;
    //std::cout<<dx<<" "<<dy<<"::"<<sprite.getPosition().x<<" "<<sprite.getPosition().y<<std::endl;
    this->move(dx, dy);
    if(this->playerState == PLAYER_STATES::ON_AIR)
    this->sprite.rotate(CONSTANTS::PLAYER_ANGULAR_VELOCITY);
    std::cout<<this->getRotation()<<std::endl;
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
        this->timeAbove +=eTime;
        this->velocity.y += eTime * CONSTANTS::GRAVITY;
        if(this->sprite.getPosition().y>=CONSTANTS::SPAWNPOINT_Y)
        {
            this->resetVelocityY();
            this->resetPositionY();
            this->resetNearestOrientation(); 
            std::cout<<"On air for : "<<this->timeAbove<<std::endl;
            this->resetPlayerState();
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
