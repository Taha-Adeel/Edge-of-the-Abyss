#include "Bound.h"
#include "BoxBound.h"
#include "TraingleBound.h"

Bound::Bound(BOUNDTYPE type, BOUNDNAME name)
{
    b_type = type;
    b_name = name;
}
Bound::~Bound(){}

const BOUNDTYPE Bound::getBoundType() const {
    return b_type;
}

const BOUNDNAME Bound::getBoundName() const {
    return b_name;
}

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
    if(b1.b_type == BOUNDTYPE::BOX && b2.b_type == BOUNDTYPE::BOX)
        return BoxBound::checkCollision(static_cast<const BoxBound&>(b1)
            , static_cast<const BoxBound&>(b2));

    else if(b1.b_type == BOUNDTYPE::BOX && b2.b_type == BOUNDTYPE::TRIANGLE)
        return TriangleBound::checkCollision(static_cast<const BoxBound&>(b1)
            , static_cast<const TriangleBound&>(b2));

    else if(b1.b_type == BOUNDTYPE::TRIANGLE && b2.b_type == BOUNDTYPE::BOX)
        return TriangleBound::checkCollision(static_cast<const BoxBound&>(b2)
            , static_cast<const TriangleBound&>(b1));
  
    return false;
}