#ifndef BOXBOUNDS_H
#define BOXBOUNDS_H

#include "Bound.h"

enum class SIDE{TOP, LEFT, RIGHT, BOTTOM, NONE};
SIDE getOppositeSide(SIDE side);

/**
 * @brief Class for rectangular bounds.
 * 
 * Provides collision detection between two boxBounds, and the side they are colliding on.
 * 
 */
class BoxBound : public Bound
{
    float height;
    float width;
    float enclosingRadius;
    float tolerance = 20;

public:
    BoxBound();
    BoxBound(sf::Vector2f position, float width, float height, BOUNDNAME name = BOUNDNAME::TILE);
    virtual ~BoxBound();

    void setWidth(float width);
    void setHeight(float weight);
    const float getWidth() const override;
    const float getHeight() const override;
    const float getEnclosingRadius() const;

    // Deleting the origin setters to ensure Position property is always of top left corner;
    void setOrigin(float, float) = delete;
    void setOrigin(const sf::Vector2f&) = delete;

    const float getLeft() const;
    const float getRight() const;
    const float getTop() const;
    const float getBottom() const;
    const sf::Vector2f getCenter() const;

    static bool checkCollision(const BoxBound& b1, const BoxBound& b2);
    SIDE getCollisionSide(const BoxBound& tile);
};
#endif