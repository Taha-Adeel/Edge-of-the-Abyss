#ifndef BOXBOUNDS_H
#define BOXBOUNDS_H
#include "Bound.h"
class BoxBound : public Bound
{
    sf::Vector2f center;
    float height, width, halfHeight, halfWidth;

public:
    BoxBound(sf::Vector2f center, float width, float height, BoundType type=BoundType::BOX, BoundName name=BoundName::TILE);
    virtual ~BoxBound();

    const float getHeight() override;
    const float getWidth() override;
    const float getHalfHeight() const;
    const float getHalfWidth() const;
    const sf::Vector2f getCenter() const;
    const float getLeft() const;
    const float getRight() const;
    const float getTop() const;
    const float getBottom() const;
    bool static checkCollision(BoxBound& b1, BoxBound& b2);
};
#endif