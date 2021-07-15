#include "Camera.h"
#include "States/PlayingState.h"
#include "Util/Constants.h"
#include <iostream>

Camera::Camera(PlayingState& context):
	sf::View(sf::FloatRect(0.0f, 0.0f, CONSTANTS::WINDOW_WIDTH, CONSTANTS::WINDOW_HEIGHT)),
	m_refPlayingState(context),
	x_locked(false),
	y_locked(false)
{
}

const sf::Vector2f Camera::getPosition() const {
	return sf::View::getCenter() - (sf::View::getSize()/2.f);
}

void Camera::setPosition(sf::Vector2f coordinates){
	sf::View::setCenter(coordinates + sf::View::getSize()/2.f);
}

void Camera::setPosition(float x, float y){
	(*this).setPosition(sf::Vector2f(x,y));
}

void Camera::lock_x(float x){
	(*this).setPosition(x, (*this).getPosition().y);
	x_locked = true;
}

void Camera::lock_y(float y){
	(*this).setPosition((*this).getPosition().x, y);
	y_locked = true;
}

void Camera::unlock_x(){
	x_locked = false;
}

void Camera::unlock_y(){
	y_locked = false;
}

void Camera::reset(){
	(*this).setPosition(0.f, 0.f);
	(*this).unlock_x();
	(*this).unlock_y();
}

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

void Camera::render(sf::RenderTarget& renderer){
	renderer.setView(*this);
}


















