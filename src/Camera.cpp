#include "Camera.h"
#include "States/PlayingState.h"
#include "Util/Constants.h"
#include <iostream>

/**
 * @brief Construct a new Camera:: Camera object
 * 
 * @param context refrence to the PlayingState object 
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
 * @brief set center of view according to coordinate 
 * 
 * we are working with top left corner , so to set the center of view by coordinates
 * (respect to top left corner) we had add half size of view
 * 
 * @param coordinates 
 */

void Camera::setPosition(sf::Vector2f coordinates){
	sf::View::setCenter(coordinates + sf::View::getSize()/2.f);
}


void Camera::setPosition(float x, float y){
	(*this).setPosition(sf::Vector2f(x,y));
}

/**
 * @brief lock_x  will lock the camera in  x direction, camera will stop following
 * the player in x_direction
 * 
 * @param x x coordinate of top left corner of our locked view
 */

void Camera::lock_x(float x){
	(*this).setPosition(x, (*this).getPosition().y);
	x_locked = true;
}

/**
 * @brief lock_y  will lock the camera in  y direction, camera will stop following
 * the player in y_direction
 * 
 * @param y y coordinate of top left corner of our locked view
 */

void Camera::lock_y(float y){
	(*this).setPosition((*this).getPosition().x, y);
	y_locked = true;
}
/**
 * @brief unlock the x direction , so that camera again follows the x_direction
 * 
 */
void Camera::unlock_x(){
	x_locked = false;
}

/**
 * @brief unlock the y direction , so that camera again follows the y_direction
 * 
 */
void Camera::unlock_y(){
	y_locked = false;
}

/**
 * @brief reset the center of view by using setPosition
 * also unlock x and y direction
 * 
 */
void Camera::reset(){
	(*this).setPosition(0.f, 0.f);
	(*this).unlock_x();
	(*this).unlock_y();
}

/**
 * @brief update the position of camera 
 *  in x_direction : it will check whether the distance b/w x coordinates of player and camera is 
 * greater than CAMERA_OFFSET_X_LEFT ,if it is ,then update the position of camera 
 * 
 * similarly in y direction 
 * 
 * @param elapsedTime elapsedTime Time elapsed between the current and last frame in sf::Time
 */
void Camera::update(sf::Time elapsedTime){
	const Player& player = m_refPlayingState.getPlayer();

	if(!x_locked && player.getPosition().x - (*this).getPosition().x > CONSTANTS::CAMERA_OFFSET_X_LEFT){
		float camera_position_x = player.getPosition().x - CONSTANTS::CAMERA_OFFSET_X_LEFT;
		(*this).setPosition(camera_position_x, (*this).getPosition().y);
	}

	if(!y_locked && player.getPosition().y - (*this).getPosition().y < CONSTANTS::CAMERA_OFFSET_Y_TOP){
		float camera_position_y = player.getPosition().y - CONSTANTS::CAMERA_OFFSET_Y_TOP;
		(*this).setPosition((*this).getPosition().x, camera_position_y);
	}

	if(!y_locked && player.getPosition().y - (*this).getPosition().y > CONSTANTS::CAMERA_OFFSET_Y_BOTTOM){
		float camera_position_y = player.getPosition().y - CONSTANTS::CAMERA_OFFSET_Y_BOTTOM;
		(*this).setPosition((*this).getPosition().x, camera_position_y);
	}

	if(!y_locked && (*this).getPosition().y > CONSTANTS::CAMERA_OFFSET_GROUND_Y){
		float camera_position_y = CONSTANTS::CAMERA_OFFSET_GROUND_Y;
		(*this).setPosition((*this).getPosition().x, camera_position_y); 
	}

// 	if(!x_locked && (*this).getPosition().x + sf::View::getSize().x 
// 			> m_refPlayingState.getLevel().getMapSize().x){
// 		float camera_position_x = m_refPlayingState.getLevel().getMapSize().x - sf::View::getSize().x ;
// 		(*this).setPosition(camera_position_x, (*this).getPosition().y);
// 	}
}

/**
 * @brief this  will apply view to the window
 * 
 * @param renderer 
 */
void Camera::render(sf::RenderTarget& renderer){
	renderer.setView(*this);
}


















