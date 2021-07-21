#include "PlanePlayer.h"
#include "../States/PlayingState.h"
#include<iostream>
#include<cmath>
#define PI 3.14

PlanePlayer::PlanePlayer(PlayingState& context):
    Player(context)
{
    this->sprite.setTexture("player/spaceship") ;
    this->initVariables() ;
    this->initPhysics();
    
}

PlanePlayer::~PlanePlayer()
{}

void PlanePlayer::initVariables()
{
    this->playerBounds.setWidth(CONSTANTS::PLANE_WIDTH);
    this->playerBounds.setHeight(CONSTANTS::PLANE_HEIGHT);
    this->sprite.setOrigin(CONSTANTS::PLANE_WIDTH/2, CONSTANTS::TILE_HEIGHT - 19.f/2.f);
    this->setCenter(CONSTANTS::PLANE_SPAWN_POINT_X, CONSTANTS::PLANE_SPAWN_POINT_Y);
}

void PlanePlayer::initPhysics()
{
    this->velocity.x = CONSTANTS::PLANE_SPEED_X;
    this->velocity.y = CONSTANTS::PLANE_SPEED_Y;
}

//Functions

void PlanePlayer::updateRotation(sf::Time elapsedTime) // overriding
{

    this->setRotation(180/PI * (atan(velocity.y / velocity.x))) ;
    // Implement rotation

}


void PlanePlayer::updateVelocity(sf::Time elapsedTime)
{
    
    if(!(this->keyHeld))
    {
        
       this->velocity.y += CONSTANTS::PLANE_ACCELARATION * elapsedTime.asSeconds() ;
       
    }
    else 
    {       
        this->velocity.y -= (CONSTANTS::PLANE_ACCELARATION * elapsedTime.asSeconds()) ;       
    }
    if(this->velocity.y >= CONSTANTS::PLANE_TERMINAL_VELOCITY_Y)
    {
        this->velocity.y = CONSTANTS::PLANE_TERMINAL_VELOCITY_Y;
    }
    if(this->velocity.y <= -(CONSTANTS::PLANE_TERMINAL_VELOCITY_Y))
    {
        this->velocity.y = -(CONSTANTS::PLANE_TERMINAL_VELOCITY_Y) ;
    }
}