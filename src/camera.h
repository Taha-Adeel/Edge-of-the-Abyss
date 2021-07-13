#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"

class Camera : public sf::View{
    
    protected :
        sf::View view ;
        Player *m_player = NULL ;
        
        
        
    public :

        Camera(Player& m_player) : m_player(&m_player) 
        {
            InitView() ;
        }
        void InitView() ;
        void update(sf::Time elapsedTime);

};



#endif
