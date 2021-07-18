#include "NormalPlayer.h"
#include "../States/PlayingState.h"
#include <iostream>
//Constructor
NormalPlayer::NormalPlayer(PlayingState& context, int index):
    Player(context)
{
    this->sprite.setTexture("player/spritesheet", index);
    this->initVariables();
    this->initPhysics();
}
NormalPlayer::~NormalPlayer(){}
//Init Functions
/**
 * @brief Places the player at the initial position required
 * 
 */
void NormalPlayer::initVariables()
{
    this->onGround = false;
    this->setCenter(CONSTANTS::SPAWNPOINT_X, CONSTANTS::SPAWNPOINT_Y);
    this->setSpriteOrigin(CONSTANTS::PLAYER_WIDTH/2, CONSTANTS::PLAYER_HEIGHT/2);
    this->setRotation(0.f);
}
/**
 * @brief Initialises the required variables for physics calculation and movement
 * 
 */
void NormalPlayer::initPhysics()
{
    this->velocity.x = CONSTANTS::PLAYER_SPEED_X;
    this->velocity.y = CONSTANTS::PLAYER_SPEED_Y;
    // this->timeAbove = 0.f;
}
//Functions
/**
 * @brief Resets the velocity in y direction back to 0
 * 
 */
void NormalPlayer::resetVelocityY()
{
    this->velocity.y = 0.f;
}
/**
 * @brief Sets the boolean onGround to true(as the default parameter) to indicate that it is on ground
 * 
 */
void NormalPlayer::setOnGround(bool _onGround)
{
    if(_onGround){
        // this->timeAbove = 0.f;
        this->onGround = true;
    }
    else this->onGround = false;
}
/**
 * @brief Sets the player sprite orientation to the nearest 90 degree angle so that it is touching the ground
 * 
 */
void NormalPlayer::resetNearestOrientation()
{
   const float angle = this->getRotation(); // get the angle between 0 and 360
   if(angle>=0&&angle<=45)this->setRotation(0.f);
   else if(angle<=135) this->setRotation(90.f);
   else if(angle<=225) this->setRotation(180.f);
   else if(angle<=315) this->setRotation(270.f);
   else this->setRotation(0.f);
}
/**
 * @brief Moving and rotating the sprite each frame as per the velocity and angular velocity
 *         Overridded to implement rotation
 * 
 * @param elapsedTime Time elapsed between the current and last frame in sf::Time
 */
void NormalPlayer::updateMovement(sf::Time elapsedTime) // overriding
{

    this->Player::updateMovement(elapsedTime); // for translation

    //std::cout<<this->getRotation()<<std::endl;

    this->onGround = false;
    // checking for hitting the ground
    if(this->getCenter().y>=CONSTANTS::SPAWNPOINT_Y) // to be replaced with collision detection with tile map and ground
    {
       // std::cout<<"Touching ground at "<<this->velocity.y<<" speed"<<std::endl;
        this->resetVelocityY();
        this->setSpritePosition(getCenter().x, CONSTANTS::SPAWNPOINT_Y);
        // std::cout<<"On air for : "<<this->timeAbove<<std::endl;
        this->setOnGround();
    }
    if(!(this->onGround))
        this->sprite.rotate(CONSTANTS::PLAYER_ANGULAR_VELOCITY* elapsedTime.asSeconds());

    if(this->onGround)
        this->resetNearestOrientation();
}

/**
 * @brief For updating and changing velocities in normal mode and checking when the player reaches the ground
 * 
 * @param elapsedTime Time elapsed between the current and last frame in sf::Time
 */
void NormalPlayer::updateVelocity(sf::Time elapsedTime)
{
    // Update velocity due to player input
    if(this->keyHeld && this->onGround){
        this->velocity.y += CONSTANTS::PLAYER_JUMP_BOOST;
        onGround = false;
    }

    // Update velocity due to acceleration
    float eTime = elapsedTime.asSeconds();
    if(this->onGround){
        // do nothing
        return ;
    }
    else if(!(this->onGround))
    {   
        // this->timeAbove +=eTime;
        this->velocity.y += eTime * CONSTANTS::GRAVITY;
    }
    if(this->velocity.y > CONSTANTS::TERMINAL_SPEED)
    {
        // this->timeAbove +=eTime;
        this->velocity.y = CONSTANTS::TERMINAL_SPEED;
    }
}