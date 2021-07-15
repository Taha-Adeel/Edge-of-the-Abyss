#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

// Forward Declared Dependencies
class PlayingState ; 

class Camera:public sf::View{
private:
    PlayingState& m_refPlayingState;
    bool x_locked;
    bool y_locked;

public:
    Camera(PlayingState& context) ;         

    const sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f);
    void setPosition(float x, float y);

    void update(sf::Time elapsedTime);
    void render(sf::RenderTarget& renderer);

    void lock_x(float x);
    void lock_y(float y);

    void unlock_x();
    void unlock_y();

    void reset();
};
#endif