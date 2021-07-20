#include "Bound.h"
#include "BoxBound.h"


Bound::Bound(BoundType type, BoundName name)
{
    b_type = type;
    b_name = name;
}
Bound::~Bound(){}

/**
 * @brief Checks for collision between two Bound objects by calling the relevant checking function
 * 
 * @param b1 
 * @param b2 
 * @return true if colliding
 * @return false if not colliding
 */
bool Bound::checkCollision(const Bound& b1, const Bound& b2)
{
    if(b1.b_type == BoundType::BOX && b2.b_type == BoundType::BOX)
    {
        return BoxBound::checkCollision(static_cast<const BoxBound&>(b1), static_cast<const BoxBound&>(b2));
    }
    return false;
}