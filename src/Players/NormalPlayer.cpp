#include "NormalPlayer.h"
#include "../States/PlayingState.h"
#include <iostream>
#include <cmath>

//Constructor
NormalPlayer::NormalPlayer(PlayingState* context, int index):
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
    this->playerBounds.setWidth(CONSTANTS::PLAYER_WIDTH - 4.f);
    this->playerBounds.setHeight(CONSTANTS::PLAYER_HEIGHT - 4.f);
    this->sprite.setOrigin(CONSTANTS::PLAYER_WIDTH/2, CONSTANTS::PLAYER_HEIGHT/2);
    this->setCenter(CONSTANTS::SPAWNPOINT_X, CONSTANTS::SPAWNPOINT_Y);
    this->onSurface = false;
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
}

//Functions
/**
 * @brief Sets the boolean onGround to true(as the default parameter) to indicate that it is on ground
 * 
 */
void NormalPlayer::setOnSurface(bool _onSurface)
{
    this->onSurface = _onSurface;
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
 * @brief Overrides base class method to set onGround to true if its colliding with the ground.
 * 
 * @return true 
 * @return false 
 */
bool NormalPlayer::resolveGroundCollision()
{
    this->onSurface = Player::resolveGroundCollision();
    return this->onSurface;
}

void NormalPlayer::resolveTileCollision(const BoxBound& tile){
    SIDE collidingSide = this->playerBounds.getCollisionSide(tile);
    if(gravity_state == GRAVITY_STATE::NORMAL)    {
        if(collidingSide == SIDE::BOTTOM){
            this->resetVelocityY();
            this->setOnSurface();
            this->snapToSide(tile, collidingSide);
        }
        else{
            this->die();
        }
    }
    else if(gravity_state == GRAVITY_STATE::FLIPPED)    {
        if(collidingSide == SIDE::TOP){
            this->resetVelocityY();
            this->setOnSurface();
            this->snapToSide(tile, collidingSide);
        }
        else{
            this->die();   
        }
    }
}

/**
 * @brief Rotating the sprite each frame as per the angular velocity
 *         Overridded to implement rotation when jumping
 * 
 * @param elapsedTime Time elapsed between the current and last frame in sf::Time
 */
void NormalPlayer::updateRotation(sf::Time elapsedTime) // overriding
{    
    if(!(this->onSurface))
        this->sprite.rotate(CONSTANTS::PLAYER_ANGULAR_VELOCITY* elapsedTime.asSeconds()*gravity_state);

    if(this->onSurface)
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
    if(this->keyHeld and this->onSurface){
        this->velocity.y = CONSTANTS::PLAYER_JUMP_BOOST*gravity_state;
        onSurface = false;
    }

    // Update velocity due to acceleration
    float eTime = elapsedTime.asSeconds();
    if(!(this->onSurface))
    {   
        // this->timeAbove +=eTime;
        this->velocity.y += eTime * CONSTANTS::GRAVITY*gravity_state;
    }
    if(fabs(this->velocity.y) >= CONSTANTS::TERMINAL_SPEED)
    {
        this->velocity.y = velocity.y > 0 ? CONSTANTS::TERMINAL_SPEED  
            : - CONSTANTS::TERMINAL_SPEED;
    }
}