#include "BoxBound.h"

SIDE getOppositeSide(SIDE side)
{
    if(side == SIDE::TOP) return SIDE::BOTTOM;
    else if(side == SIDE::LEFT) return SIDE::RIGHT;
    else if(side == SIDE::RIGHT) return SIDE::LEFT;
    else if(side == SIDE::BOTTOM) return SIDE::RIGHT;
    else return SIDE::NONE;
}

BoxBound::BoxBound(){
    this->b_type = BOUNDTYPE::BOX;
}

BoxBound::BoxBound(sf::Vector2f position, float width, float height, BOUNDNAME name):
    Bound(BOUNDTYPE::BOX, name)
{
    sf::Transformable::setPosition(position);
    this->width = width;
    this->height = height;
}
BoxBound::~BoxBound(){}

const float BoxBound::getWidth() const {return this->width;}
const float BoxBound::getHeight() const {return this->height;}
void BoxBound::setWidth(float _width){this->width = _width;}
void BoxBound::setHeight(float _height){this->height = _height;}

const float BoxBound::getLeft() const{return this->getPosition().x;}
const float BoxBound::getRight() const{return this->getLeft() + this->width;}
const float BoxBound::getTop() const{return this->getPosition().y;}
const float BoxBound::getBottom() const{return this->getTop() + this->height;}


bool BoxBound::checkCollision(const BoxBound& b1, const BoxBound& b2)
{
    // check for the collision between two box bounds
    if(b1.getLeft() <= b2.getRight() && b1.getRight() >= b2.getLeft() 
        && b1.getTop() <= b2.getBottom() && b1.getBottom() >= b2.getTop())
            return true;

    return false;
}
