#include "Player.h"
#include "Util/Constants.h"
#include"camera.h"
#include "States/PlayingState.h"

Camera :: Camera(PlayingState& state) : sf::View(sf::FloatRect(0.0f,0.0f,1280.0f ,720.0f)) , playing_state(state)       
        {       
        }




void Camera :: update(sf::Time elapsedTime)
{
   if(playing_state.getPlayer().getPosition().x - sf::View::getCenter().x > CONSTANTS::CAMERA_OFFSET_X )
   {
       sf::View::setCenter(playing_state.getPlayer().getPosition().x-CONSTANTS::CAMERA_OFFSET_X,sf::View::getCenter().y) ;
   }

   Game& game = Game::getGameInstance();
   game.getWindow().setView(*(this)) ;
}


















// void Camera :: update(sf::Time elaspsedTime)
// {
//     if(m_player->getPosition().x - view.getCenter().x > CONSTANTS::CAMERA_OFFSET_X )
//     {
//         view.setCenter(m_player->getPosition().x - CONSTANTS::CAMERA_OFFSET_X,view.getCenter().y) ;
//     }
//     if(view.getCenter().y > CONSTANTS::GROUND_HEIGHT)
//     {
//         view.setCenter(view.getCenter().x , CONSTANTS::GROUND_HEIGHT) ;
//     }

//     m_player->update(elaspsedTime) ;
// }