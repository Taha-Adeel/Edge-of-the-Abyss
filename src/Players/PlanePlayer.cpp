#include "PlanePlayer.h"
#include "../States/PlayingState.h"
#include<iostream>

PlanePlayer::PlanePlayer(PlayingState& context):
    Player(context)
{
    this->sprite.setTexture("player/spaceship") ;
    this->initVariables() ;
    std::cout << "Constructor called \n" ;
    this->initPhysics();
}

PlanePlayer::~PlanePlayer()
{}

void PlanePlayer::initVariables()
{
    this->setCenter(CONSTANTS::PLANE_SPAWN_POINT_X, CONSTANTS::PLANE_SPAWN_POINT_Y);
    this->playerBounds.setWidth(CONSTANTS::PLAYER_WIDTH);
    this->playerBounds.setHeight(CONSTANTS::PLAYER_HEIGHT);
    //this->setSpriteOrigin(CONSTANTS::PLAYER_WIDTH/2, CONSTANTS::PLAYER_HEIGHT/2);
    //this->setRotation(0.f);
}

void PlanePlayer::initPhysics()
{
    this->velocity.x = CONSTANTS::PLANE_SPEED_X;
    this->velocity.y = CONSTANTS::PLANE_SPEED_Y;
}

//Functions

void PlanePlayer::updateRotation(sf::Time elapsedTime) // overriding
{

    // Implement rotation

}


void PlanePlayer::updateVelocity(sf::Time elapsedTime)
{
    
    if(!(this->keyHeld))
    {
         
       this->resetVelocityY() ;
       //std::cout<<"key not held" <<" : " << velocity.y ; 
       //this->velocity.y = CONSTANTS::PLANE_SPEED_Y;
       this->velocity.y += CONSTANTS::GRAVITY * elapsedTime.asSeconds() ;
    //    if(this->getSpritePosition().y > CONSTANTS::PLANE_MIN_HEIGHT)//Not needed, but if used, use getTopLeft() instead of getSpritePosition
    //    {
    //       this->resetVelocityY();
    //    }
       
    }
    else 
    {   
        //std::cout<<"Key heled ::" <<velocity.y  ;
        this->resetVelocityY();
        //this->velocity.y =  -(CONSTANTS::PLANE_SPEED_Y);
        this->velocity.y -= (CONSTANTS::GRAVITY * elapsedTime.asSeconds()) ;
        //  if(this->getSpritePosition().y < CONSTANTS::PLANE_MAX_HEIGHT)
        //  {
        //     this->resetVelocityY();
        //  }       
    }
    if(this->velocity.y >= CONSTANTS::TERMINAL_SPEED)
    {
        this->velocity.y = CONSTANTS::TERMINAL_SPEED;
    }
}