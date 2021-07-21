#ifndef BOXBOUNDS_H
#define BOXBOUNDS_H

#include "Bound.h"

enum class SIDE{TOP, LEFT, RIGHT, BOTTOM, NONE};
SIDE getOppositeSide(SIDE side);
class BoxBound : public Bound
{
    // sf::Vector2f center;
    float height, width, halfHeight, halfWidth;

public:
    BoxBound();
    BoxBound(sf::Vector2f position, float width, float height, BOUNDNAME name = BOUNDNAME::TILE);
    virtual ~BoxBound();

    const float getWidth() const override;
    const float getHeight() const override;
    void setWidth(float width);
    void setHeight(float weight);
    const float getHalfWidth() const;
    const float getHalfHeight() const;
    const sf::Vector2f getCenter() const;
    const float getLeft() const;
    const float getRight() const;
    const float getTop() const;
    const float getBottom() const;
    const float getThresholdTop() const;
    static bool checkCollision(const BoxBound& b1, const BoxBound& b2);
};
#endif