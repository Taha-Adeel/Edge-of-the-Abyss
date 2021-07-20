#include"PlanePlayer.h"
#include<iostream>

PlanePlayer::PlanePlayer()
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
   
    this->onAir  = true ;
    this->setCenter(CONSTANTS::PLANE_SPAWN_POINT_X, CONSTANTS::PLANE_SPAWN_POINT_Y);
    //this->setSpriteOrigin(CONSTANTS::PLAYER_WIDTH/2, CONSTANTS::PLAYER_HEIGHT/2);
    //this->setRotation(0.f);
}

void PlanePlayer::initPhysics()
{
    this->velocity.x = CONSTANTS::PLANE_SPEED_X;
    this->velocity.y = CONSTANTS::PLANE_SPEED_Y;
    // this->timeAbove = 0.f;
}
//Functions
/**
 * @brief Resets the velocity in y direction back to 0
 * 
 */
void PlanePlayer::resetVelocityY()
{
    this->velocity.y = 0.f;
}
/**
 * @brief Sets the boolean onGround to true(as the default parameter) to indicate that it is on ground
 * 
 */
void PlanePlayer::setOnAir(bool _onAir)
{
    if(_onAir){
        // this->timeAbove = 0.f;
        this->onAir = true;
    }
    else this->onAir = false;
}


void PlanePlayer::updateMovement(sf::Time elapsedTime) // overriding
{

    this->Player::updateMovement(elapsedTime); // for translation

}


void PlanePlayer::updateVelocity(sf::Time elapsedTime)
{
    
    if(!(this->keyHeld))
    {
         
       this->resetVelocityY() ;
       //std::cout<<"key not held" <<" : " << velocity.y ; 
       this->velocity.y = CONSTANTS::PLANE_SPEED_Y;
       if(this->getSpritePosition().y > CONSTANTS::PLANE_MIN_HEIGHT)
       {
          this->resetVelocityY();
       }
       
    }
    else 
    {   
         //std::cout<<"Key heled ::" <<velocity.y  ;
         this->resetVelocityY();
          this->velocity.y =  -(CONSTANTS::PLANE_SPEED_Y);
         if(this->getSpritePosition().y < CONSTANTS::PLANE_MAX_HEIGHT)
         {
            this->resetVelocityY();
         }
         
        // this->timeAbove +=eTime;
       
    }
    if(this->velocity.y > CONSTANTS::TERMINAL_SPEED)
    {
        // this->timeAbove +=eTime;
        this->velocity.y = CONSTANTS::TERMINAL_SPEED;
    }
}