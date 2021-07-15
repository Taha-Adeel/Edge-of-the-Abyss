#ifndef CAMERA_H
#define CAMERA_H

// #include <SFML/Graphics.hpp>
// #include <SFML/Window.hpp>
// #include <SFML/System.hpp>
// #include <SFML/Audio.hpp>
#include "Player.h"
#include"Game.h"

class PlayingState ; 

class Camera : public sf::View{
    
    protected :
        //sf::View view ;
        //Player *m_player = NULL ;
        PlayingState& playing_state ; // 
        
        
        
    public :

        Camera(PlayingState& state )  ;          
        void update(sf::Time elapsedTime);

};



#endif
