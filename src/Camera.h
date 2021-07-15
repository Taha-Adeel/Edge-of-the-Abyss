#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

// Forward Declared Dependencies
class PlayingState ; 

/**
 * @brief Camera class is wrapper for sf::view
 * 
 * This will just take care of what region  to be seen on the window.
 * you can scroll, rotate or zoom the entire scene without altering the way 
 * that your drawable objects are drawn.
 * 
 */
class Camera:public sf::View{
private:
    // private member variables
    PlayingState& m_refPlayingState;
    bool x_locked;
    bool y_locked;

public:
    // constructors
    Camera(PlayingState& context) ;         

    // public member functions
    void update(sf::Time elapsedTime);
    void render(sf::RenderTarget& renderer);

    // public accessors and setters
    const sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f);
    void setPosition(float x, float y);

    // public member functions
    void lock_x(float x);
    void lock_y(float y);

    void unlock_x();
    void unlock_y();

    void reset();
};
#endif