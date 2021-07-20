#ifndef BOXBOUNDS_H
#define BOXBOUNDS_H
#include "Bound.h"
class BoxBound : public Bound
{
    sf::Vector2f center;
    float height, width, halfHeight, halfWidth;

public:
    BoxBound(sf::Vector2f center, float width, float height);
    float getHeight() override;
    float getWidth() override;

    bool static checkCollision(BoxBound& b1, BoxBound& b2)
    {
        float dx = 2;
    }
};
#endif