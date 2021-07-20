#include "Bound.h"
#include "BoxBound.h"

Side getOppositeSide(Side side)
{
    if(side == Side::TOP) return Side::BOTTOM;
    else if(side == Side::LEFT) return Side::RIGHT;
    else if(side == Side::RIGHT) return Side::LEFT;
    else if(side == Side::BOTTOM) return Side::RIGHT;
    else return Side::NONE;
}



Bound::Bound()
{
    b_type = BoundType::Box;
    b_name = BoundName::Spike1;
}
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
bool Bound::checkCollision(Bound& b1, Bound& b2)
{
    if(b1.b_type == BoundType::Box && b2.b_type == BoundType::Box)
    {
        return BoxBound::checkCollision((BoxBound&)b1, (BoxBound&)b2);
    }
    return false;
}