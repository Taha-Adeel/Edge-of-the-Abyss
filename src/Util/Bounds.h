#ifndef BOUNDS_H
#define BOUNDS_H
#include <SFML/Graphics.hpp>
//#include "BoxBounds.h"
enum class BoundsType{Box, Triangle};
class Bounds : public sf::IntRect
{
protected:
    BoundsType type;
public:
    virtual float getWidth() = 0;
    virtual float getHeight()=0;

    bool static checkCollision(Bounds& b1, Bounds& b2)
    {
        if(b1.type == BoundsType::Box && b2.type == BoundsType::Box)
        {
            return BoxBounds::checkCollision((BoxBounds&)b1, (BoxBounds&)b2);
        }
        return false;
    }
};
class BoxBounds : public Bounds 
{
    float height, width, halfHeight, halfWidth;

public:
    BoxBounds(float width, float height)
    {
        this->height = height;
        this->width = width;
        this->halfHeight = this->height/2;
        this->halfWidth = this->width/2; 
    }
    float getHeight() override;
    float getWidth() override;

    bool static checkCollision(BoxBounds& b1, BoxBounds& b2)
    {
        
    }
};

#endif