#ifndef BOUNDS_H
#define BOUNDS_H
#include <SFML/Graphics.hpp>
enum class BoundType{Box, Triangle};
enum class BoundName{Spike1, Spike2};
enum class Side{TOP, LEFT, RIGHT, BOTTOM, NONE};
Side getOppositeSide(Side side);
class BoxBound;
class Bound : public sf::Transformable
{
protected:
    BoundType b_type;
    BoundName b_name;
public:
    Bound();
    virtual ~Bound();
    Bound(BoundType, BoundName);

    virtual const float getWidth() = 0;
    virtual const float getHeight()=0;

    static bool checkCollision(Bound& b1, Bound& b2);
};


#endif