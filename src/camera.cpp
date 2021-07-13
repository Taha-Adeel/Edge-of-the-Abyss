#include "Player.h"
#include "Util/Constants.h"
#include"camera.h"

void Camera :: InitView()
{
    view.setCenter(m_player->getPosition()) ;
    view.setSize(CONSTANTS::TILE_WIDTH , CONSTANTS::TILE_HEIGHT) ;
}

void Camera :: update(sf::Time elaspsedTime)
{
    if(m_player->getPosition().x - view.getCenter().x > CONSTANTS::CAMERA_OFFSET_X )
    {
        view.setCenter(m_player->getPosition().x - CONSTANTS::CAMERA_OFFSET_X,view.getCenter().y) ;
    }
    if(view.getCenter().y > CONSTANTS::GROUND_HEIGHT)
    {
        view.setCenter(view.getCenter().x , CONSTANTS::GROUND_HEIGHT) ;
    }

    m_player->update(elaspsedTime) ;
}