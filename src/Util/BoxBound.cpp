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
const float BoxBound::getHalfWidth(){return this->halfWidth;}
const float BoxBound::getHalfHeight(){return this->halfHeight;}
const sf::Vector2f BoxBound::getCenter(){return this->center;}

bool static checkCollision(BoxBound& b1, BoxBound& b2)
{
    // check for the collision between two box bounds
    return false;
}
