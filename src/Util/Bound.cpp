#include "Bound.h"
#include "BoxBound.h"
bool Bound::checkCollision(Bound& b1, Bound& b2)
{
    if(b1.b_type == BoundType::Box && b2.b_type == BoundType::Box)
    {
        return BoxBound::checkCollision((BoxBound&)b1, (BoxBound&)b2);
    }
    return false;
}