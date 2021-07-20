#ifndef BOXBOUNDS_H
#define BOXBOUNDS_H
#include "Bound.h"
class BoxBound : public Bound
{
    sf::Vector2f center;
    float height, width, halfHeight, halfWidth;

public:
    BoxBound(sf::Vector2f center, float width, float height);
    BoxBound::BoxBound(sf::Vector2f center, float width, float height, BoundType type, BoundName name);
    virtual ~BoxBound();

    const float getHeight() override;
    const float getWidth() override;
    const float getHalfHeight();
    const float getHalfWidth();
    const sf::Vector2f getCenter();

    bool static checkCollision(BoxBound& b1, BoxBound& b2);
};
#endif