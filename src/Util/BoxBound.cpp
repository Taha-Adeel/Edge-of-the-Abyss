#include "BoxBound.h"

BoxBound::BoxBound(sf::Vector2f center, float width, float height):Bound(BoundType::Box, BoundName::Spike1)
{
    this->center = center;
    this->height = height;
    this->width = width;
    this->halfHeight = this->height/2;
    this->halfWidth = this->width/2; 
}
BoxBound::BoxBound(sf::Vector2f center, float width, float height, BoundType type, BoundName name):Bound(type, name)
{
    this->center = center;
    this->height = height;
    this->width = width;
    this->halfHeight = this->height/2;
    this->halfWidth = this->width/2;
}
BoxBound::~BoxBound(){}


const float BoxBound::getWidth(){return this->width;}
const float BoxBound::getHeight(){return this->height;}
const float BoxBound::getHalfWidth() const{return this->halfWidth;}
const float BoxBound::getHalfHeight() const{return this->halfHeight;}
const sf::Vector2f BoxBound::getCenter() const{return this->center;}
const float BoxBound::getLeft() const{return this->center.x - this->halfWidth;}
const float BoxBound::getRight() const{return this->center.x + this->halfWidth;}
const float BoxBound::getTop() const{return this->center.y - this->halfHeight;}
const float BoxBound::getBottom() const{return this->center.y + this->halfHeight;}

bool static checkCollision(BoxBound& b1, BoxBound& b2)
{
    // check for the collision between two box bounds
    if(b1.getLeft() <= b2.getRight() && b1.getRight() >= b2.getLeft())
    {
        if(b1.getTop() <= b2.getBottom() && b1.getBottom() >= b2.getTop())
            return true;
    }
    return false;
}
