#include "PlanePlayer.h"
#include "../States/PlayingState.h"
#include<iostream>
#include<cmath>
#define PI 3.141592

PlanePlayer::PlanePlayer(PlayingState* context):
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
    this->sprite.setScale(1.f,1.f*this->gravity_state);
}

void PlanePlayer::flipGravity()
{
    Player::flipGravity();
    this->sprite.scale(1.f,-1.f);
}


void PlanePlayer::initPhysics()
{
    this->velocity.x = CONSTANTS::PLANE_SPEED_X;
    this->velocity.y = CONSTANTS::PLANE_SPEED_Y;
}

//Functions
void PlanePlayer::resolveTileCollision(const BoxBound& tile){
    SIDE collidingSide = this->playerBounds.getCollisionSide(tile);
    if(collidingSide == SIDE::BOTTOM || collidingSide == SIDE::TOP){
        resetVelocityY();
        this->snapToSide(tile, collidingSide);
    }
    else{
        this->die();
    }
}

void PlanePlayer::updateRotation(sf::Time elapsedTime)
{
    this->setRotation(180/PI * (atan(velocity.y / velocity.x))) ;
}


void PlanePlayer::updateVelocity(sf::Time elapsedTime)
{
    
    if(!(this->keyHeld))
    {
       this->velocity.y += CONSTANTS::PLANE_ACCELARATION * elapsedTime.asSeconds()*gravity_state ;
    }
    else 
    {       
        this->velocity.y -= (CONSTANTS::PLANE_ACCELARATION * elapsedTime.asSeconds()*gravity_state) ;       
    }
    if(fabs(this->velocity.y) >= CONSTANTS::PLANE_TERMINAL_VELOCITY_Y)
    {
        this->velocity.y = velocity.y > 0 ? CONSTANTS::PLANE_TERMINAL_VELOCITY_Y  
            : -CONSTANTS::PLANE_TERMINAL_VELOCITY_Y;
    }
}