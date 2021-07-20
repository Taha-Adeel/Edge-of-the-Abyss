#include "Camera.h"
#include "States/PlayingState.h"
#include "Util/Constants.h"
#include <iostream>

/**
 * @brief Construct a new Camera:: Camera object
 * 
 * @param context Reference to the PlayingState object 
 * 			(to access the player object)
 */

Camera::Camera(PlayingState& context):
	sf::View(sf::FloatRect(0.0f, 0.0f, CONSTANTS::WINDOW_WIDTH, CONSTANTS::WINDOW_HEIGHT)),
	m_refPlayingState(context),
	x_locked(false),
	y_locked(false)
{
}

/**
 * @brief return the postion of top left corner of view
 * 
 * @return const sf::Vector2f 
 */
const sf::Vector2f Camera::getPosition() const {
	return sf::View::getCenter() - (sf::View::getSize()/2.f);
}

/**
 * @brief Set the top left corner of view to the coordinates given as parameter. 
 * 
 * We are working with the top left corner, while sf::View works with the center of the view.
 * So to set the top left corner to coordinates, we set the center to coordiinates plus 
 * half the size of the view.
 * 
 * @param coordinates 
 */
void Camera::setPosition(sf::Vector2f coordinates){
	sf::View::setCenter(coordinates + sf::View::getSize()/2.f);
}

/**
 * @brief Set the top left corner of view to the coordinates given as parameter. 
 * 
 * We are working with the top left corner, while sf::View works with the center of the view.
 * So to set the top left corner to coordinates, we set the center to coordiinates plus 
 * half the size of the view.
 * 
 * @param x
 * @param y
 */
void Camera::setPosition(float x, float y){
	setPosition(sf::Vector2f(x,y));
}

/**
 * @brief lock_x  will lock the camera in  x direction, i.e camera will stop following
 * the player in x_direction
 * 
 * @param x x coordinate of top left corner of our locked view
 */

void Camera::lock_x(float x){
	setPosition(x, getPosition().y);
	x_locked = true;
}

/**
 * @brief lock_y  will lock the camera in  y direction, i.e camera will stop following
 * the player in y_direction
 * 
 * @param y y coordinate of top left corner of our locked view
 */

void Camera::lock_y(float y){
	(*this).setPosition((*this).getPosition().x, y);
	y_locked = true;
}
/**
 * @brief Unlock the x direction , so that camera again follows the player in the x_direction
 * 
 */
void Camera::unlock_x(){
	x_locked = false;
}

/**
 * @brief Unlock the y direction , so that camera again follows the player in the y_direction
 * 
 */
void Camera::unlock_y(){
	y_locked = false;
}

/**
 * @brief Resets the view to the start by using setPosition
 * also unlocks x and y direction
 * 
 */
void Camera::reset(){
	(*this).setPosition(0.f, 0.f);
	(*this).unlock_x();
	(*this).unlock_y();
	old_pos.x = 0.f;
	old_pos.y = 0.f;
}

/**
 * @brief Update the position of camera 
 * 
 * In x_direction : it will check whether the distance b/w x coordinates (of top left corner)
 * of player and camera is greater than CAMERA_OFFSET_X_LEFT, if it is, then update the 
 * position of camera.
 * 
 * Similarly in y direction 
 * 
 * @param elapsedTime elapsedTime Time elapsed between the current and last frame in sf::Time
 */
void Camera::update(sf::Time elapsedTime){
	const Player& player = m_refPlayingState.getPlayer();

	// Checks whether distance between player and left edge of the screen is greater than
	// CAMERA_OFFSET_X_LEFT. If it is, then the camera is snapped to be at CAMERA_OFFSET_X_LEFT
	// behind the player.(Prevents player from going too far right on the screen)
	if(!x_locked && player.getTopLeftPosition().x - this->getPosition().x 
													> CONSTANTS::CAMERA_OFFSET_X_LEFT){
		float camera_position_x = player.getTopLeftPosition().x - CONSTANTS::CAMERA_OFFSET_X_LEFT;
		this->setPosition(camera_position_x, this->getPosition().y);
	}

	// Checks whether distance between player and top of the screen is less than
	// CAMERA_OFFSET_Y_TOP. If it is, then the camera is snapped to be at CAMERA_OFFSET_Y_TOP
	// above the player.(Prevents player from going too far high on the screen)
	if(!y_locked && player.getTopLeftPosition().y - this->getPosition().y
													< CONSTANTS::CAMERA_OFFSET_Y_TOP){
		float camera_position_y = player.getTopLeftPosition().y - CONSTANTS::CAMERA_OFFSET_Y_TOP;
		this->setPosition(this->getPosition().x, camera_position_y);
	}

	// Checks whether distance between player and top of the screen is greater than
	// CAMERA_OFFSET_Y_BOTTOM. If it is, then the camera is snapped to be at 
	// CAMERA_OFFSET_Y_BOTTOM above the player. (Prevents player from going too below on the screen)
	if(!y_locked && player.getTopLeftPosition().y - this->getPosition().y
													> CONSTANTS::CAMERA_OFFSET_Y_BOTTOM){
		float camera_position_y = player.getTopLeftPosition().y - CONSTANTS::CAMERA_OFFSET_Y_BOTTOM;
		this->setPosition(this->getPosition().x, camera_position_y);
	}

	// Checks whether the y-coordinate of the top left corner of our camera is greater than
	// CAMERA_OFFSET_GROUND_Y. If it is, then the camera is snapped to be at 
	// CAMERA_OFFSET_GROUND_Y. (Prevents camera from going too low (Below the ground))
	if(!y_locked && this->getPosition().y > CONSTANTS::CAMERA_OFFSET_GROUND_Y){
		float camera_position_y = CONSTANTS::CAMERA_OFFSET_GROUND_Y;
		this->setPosition(this->getPosition().x, camera_position_y); 
	}


	// Checks if camera's view goes beyond the map size. If it does, then the camera is 
	// snapped to be at the maps end.
// 	if(!x_locked && (*this).getPosition().x + sf::View::getSize().x 
// 			> m_refPlayingState.getLevel().getMapSize().x){
// 		float camera_position_x = m_refPlayingState.getLevel().getMapSize().x - sf::View::getSize().x ;
// 		(*this).setPosition(camera_position_x, (*this).getPosition().y);
// 	}

	//Velocity calculation and update
	sf::Vector2f cur_pos = this->getPosition();
	m_velocity = (cur_pos - old_pos)/(elapsedTime.asSeconds());
	old_pos = cur_pos;
}

/**
 * @brief This  will apply the view to the window
 * 
 * @param renderer 
 */
void Camera::render(sf::RenderTarget& renderer){
	renderer.setView(*this);
}

/**
 * @brief Get the camera's velocity
 * 
 * @return const sf::Vector2f 
 */
const sf::Vector2f Camera::getVelocity() const {
	return m_velocity;
}