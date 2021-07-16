#include "NormalPlayer.h"
#include <iostream>
//Constructor
NormalPlayer::NormalPlayer(int index)
{
    this->sprite = Sprite("player/spritesheet", index);
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
    this->playerState = PLAYER_STATES::ON_GROUND;
    this->setSpritePosition(CONSTANTS::SPAWNPOINT_X, CONSTANTS::SPAWNPOINT_Y);
    this->setSpriteOrigin(CONSTANTS::PLAYER_WIDTH/2, CONSTANTS::PLAYER_HEIGHT/2);
    //this->setCenter(CONSTANTS::SPAWNPOINT_X, CONSTANTS::SPAWNPOINT_Y);
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
    this->timeAbove = 0.f;
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
 * @brief Resets the position of the player so that it touches the ground
 * 
 */
void NormalPlayer::resetPositionY()
{
    this->sprite.setPosition(Player::getSpritePosition().x, CONSTANTS::SPAWNPOINT_Y);
}
/**
 * @brief Resets the playerState to PLAYER_STATES::ON_GROUND to indicate that it is on ground
 * 
 */
void NormalPlayer::resetPlayerState()
{
    this->timeAbove = 0.f;
    this->playerState = PLAYER_STATES::ON_GROUND;
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
    if(this->playerState != PLAYER_STATES::ON_GROUND)
    this->sprite.rotate(CONSTANTS::PLAYER_ANGULAR_VELOCITY* elapsedTime.asSeconds());
    //std::cout<<this->getRotation()<<std::endl;
}

/**
 * @brief For updating and changing velocities in normal mode and checking when the player reaches the ground
 * 
 * @param elapsedTime Time elapsed between the current and last frame in sf::Time
 */
void NormalPlayer::updatePhysics(sf::Time elapsedTime)
{
    float eTime = elapsedTime.asSeconds();
    if(this->playerState == PLAYER_STATES::ON_GROUND){
        // do nothing
        return ;
    }
    else if(this->playerState == PLAYER_STATES::ON_AIR)
    {   
        this->timeAbove +=eTime;
        this->velocity.y += eTime * CONSTANTS::GRAVITY;
        if(this->velocity.y >= CONSTANTS::TERMINAL_SPEED)
        {
            this->playerState = PLAYER_STATES::ON_AIR_TERMINAL;
            //std::cout<<"Terminal velocity achieved"<<std::endl;
        }
    }
    else if(this->playerState == PLAYER_STATES::ON_AIR_TERMINAL)
    {
        this->timeAbove +=eTime;
        this->velocity.y = CONSTANTS::TERMINAL_SPEED;

    }
    // checking for hitting the ground
    if(this->sprite.getPosition().y>=CONSTANTS::SPAWNPOINT_Y) // to be replaced with checking the height at that x coordinate
    {
       // std::cout<<"Touching ground at "<<this->velocity.y<<" speed"<<std::endl;
        this->resetVelocityY();
        this->resetPositionY();
        this->resetNearestOrientation(); 
        //std::cout<<"On air for : "<<this->timeAbove<<std::endl;
        this->resetPlayerState();
    }
}
/**
 * @brief Handling the key presses for jumping
 * 
 * @param ev 
 */
void NormalPlayer::handleEvent(sf::Event ev)
{
    if(playerState == PLAYER_STATES::ON_GROUND) // Cannot control player midair
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)||sf::Keyboard::isKeyPressed(sf::Keyboard::Up)||sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            //std::cout<<"Pressed Jump"<<std::endl;
            this->velocity.y += CONSTANTS::PLAYER_JUMP_BOOST;
            playerState = PLAYER_STATES::ON_AIR;
        }
    }
}
