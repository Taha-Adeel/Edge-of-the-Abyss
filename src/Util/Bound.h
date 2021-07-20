#ifndef BOUNDS_H
#define BOUNDS_H

#include <SFML/Graphics.hpp>

enum class BoundType{BOX, TRIANGLE};
enum class BoundName{TILE, SPIKE, PORTAL};

class BoxBound;
class Bound : public sf::Transformable
{
public:
    BoundType b_type;
    BoundName b_name;
public:
    Bound() = default;
    Bound(BoundType, BoundName);
    virtual ~Bound();

    virtual const float getWidth() = 0;
    virtual const float getHeight() = 0;

    static bool checkCollision(const Bound& b1, const Bound& b2);
};


#endif