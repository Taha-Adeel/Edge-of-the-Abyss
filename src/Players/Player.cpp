#include "Player.h"
#include "../States/PlayingState.h"
#include <iostream>

// Constructors and Destructors
/**
 * @brief Construct a new Player::Player object
 * 
 * @param context Reference to the PlayingState object that player belongs to so that it can access its contents
 */
Player::Player(PlayingState& context):
	m_ref_PlayingState(context)
{
}
Player::~Player(){}

// Accessors
/**
 * @brief Returns the position of the top left corner of the player bounds
 * 
 * @return const sf::Vector2f 
 */
const sf::Vector2f Player::getTopLeftPosition() const
{
    return this->playerBounds.getPosition() - this->playerBounds.getOrigin() ;
}

const BoxBound& Player::getplayerBounds() const
{
    return this->playerBounds;
}

const float Player::getHeight() const
{
    return this->playerBounds.getHeight();
}

const float Player::getWidth() const
{
    return this->playerBounds.getWidth();
}

/**
 * @brief Returns the position of the center of the player bounds
 * 
 * @return const sf::Vector2f 
 */
const sf::Vector2f Player::getCenter() const
{
    return sf::Vector2f(this->getTopLeftPosition().x + this->getWidth()/2.f,
                         this->getTopLeftPosition().y + this->getHeight()/2.f);
}

/**
 * @brief Returns the angle of rotation (0 <= angle <360)
 * 
 * @return const float 
 */
const float Player::getRotation() const
{
    return this->sprite.getRotation();
}

// Modifier
/**
 * @brief Set the new absolute position of the top left corner of the Player Bounds
 * 
 * @param x new x coordinate
 * @param y new y coordinate
 */
void Player::setTopLeftPosition(const float x, const float y){
    this->playerBounds.setPosition(x + this->playerBounds.getOrigin().x ,
         y + this->playerBounds.getOrigin().y);
    this->sprite.setPosition(x + this->sprite.getOrigin().x,
        y + this->sprite.getOrigin().y - (CONSTANTS::TILE_HEIGHT - this->getHeight()));
}

/**
 * @brief Set the new absolute position of the center of the Player bound
 * 
 * @param x new x coordinate
 * @param y new y coordinate
 */
void Player::setCenter(const float x, const float y){
    this->setTopLeftPosition(x-this->getWidth()/2, y-this->getHeight()/2);
}

/**
 * @brief Sets the absolute angle of rotation in clockwise direction
 * 
 * @param angle absolute angle of the final orientation
 */
void Player::setRotation(const float angle)
{
    this->sprite.setRotation(angle);
}

/**
 * @brief Rotates the sprite by given angle clockwise
 * 
 * @param angle angle to rotate the sprite by (clockwise)
 */
void Player::rotate(const float angle)
{
    this->sprite.rotate(angle);
}

/**
 * @brief Resets the velocity in y direction back to 0
 * 
 */
void Player::resetVelocityY()
{
    this->velocity.y = 0;
}

//Movement
/**
 * @brief Moves the sprite by given amount
 * 
 * @param dir_x 
 * @param dir_y 
 */
void Player::move(const float dir_x, const float dir_y)
{
    this->sprite.move(dir_x, dir_y);
    this->playerBounds.move(dir_x, dir_y);
}

/**
 * @brief For moving the sprite as per velocity in that instant.
 * Derived classes will override this if rotation or some other new mechanishm is required 
 * 
 * @param elapsedTime Time elapsed between the current and last frame in sf::Time
 */
void Player::updateMovement(sf::Time elapsedTime)
{
    float eTime = elapsedTime.asSeconds();
    float dx = eTime* this->velocity.x;
    float dy = eTime* this->velocity.y;
    //std::cout<<dx<<" "<<dy<<"::"<<sprite.getPosition().x<<" "<<sprite.getPosition().y<<std::endl;
    this->move(dx, dy);
}

void Player::updateRotation(sf::Time elapsedTime){}

/**
 * @brief If player goes below ground height, its vertical velocity is reset to 0 
 * and its position is snapped to ground height.
 * 
 * @return true If player is colliding with ground
 * @return false Otherwise
 */
bool Player::resolveGroundCollision()
{
    // checking for hitting the ground
    if(this->getTopLeftPosition().y>=CONSTANTS::GROUNDHEIGHT - this->getHeight()) 
    {
        // Resolving ground collision
        this->resetVelocityY();
        this->setTopLeftPosition(this->getTopLeftPosition().x, 
            CONSTANTS::GROUNDHEIGHT - this->getHeight());
        return true;
    }
    return false;
}

// void Player::resolveTileCollision()
// {
//         //
// }



/**
 * @brief Sets keyHeld to true if space, up arrow, or left mouse button is held
 * 
 * @param ev 
 */
void Player::handleEvent(sf::Event ev)
{
    static bool spaceHeld{false}, upArrowHeld{false}, leftClickHeld{false};

    switch(ev.type)
    {
        case sf::Event::KeyPressed:
            switch (ev.key.code)
            {
                case sf::Keyboard::Space:
                    spaceHeld = true;
                    break;
                case sf::Keyboard::Up:
                    upArrowHeld = true;
                    break;        
                default:
                    break;
            }
            break;
        case sf::Event::KeyReleased:
            switch (ev.key.code)
            {
                case sf::Keyboard::Space:
                    spaceHeld = false;
                    break;
                case sf::Keyboard::Up:
                    upArrowHeld = false;
                    break;        
                default:
                    break;
            }
            break;
        case sf::Event::MouseButtonPressed:
            switch(ev.key.code)
            {
                case sf::Mouse::Left:
                    leftClickHeld = true;
                default:
                    break;
            }
            break;
        case sf::Event::MouseButtonReleased:
            switch(ev.key.code)
            {
                case sf::Mouse::Left:
                    leftClickHeld = false;
                default:
                    break;
            }
            break;
        default:
            break;
    }

    keyHeld = spaceHeld || upArrowHeld || leftClickHeld;
}

//Update and Render
/**
 * @brief Updates the new position of the player. Calls updateMovement() to move it and 
 * updateVelocity() to change the velocities as per the acceleration.
 * 
 * @param elapsedTime Time elapsed between the current and last frame in sf::Time
 */
void Player::update(sf::Time elapsedTime)
{
    this->updateMovement(elapsedTime);
    this->resolveGroundCollision();
	for(auto& tile: m_ref_PlayingState.getCurrentLevel().getTileMap()){
		if(Bound::checkCollision(this->playerBounds, tile.getBounds())){
			std::cout << "Colliding!!" << std::endl;
		}
	}
    this->updateRotation(elapsedTime);
    this->updateVelocity(elapsedTime);
}

/**
 * @brief Renders the player sprite for each frame
 * 
 * @param target 
 */
void Player::render(sf::RenderTarget& target)
{
    target.draw(this->sprite);
}