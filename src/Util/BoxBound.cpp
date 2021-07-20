#include "BoxBound.h"

Side getOppositeSide(Side side)
{
    if(side == Side::TOP) return Side::BOTTOM;
    else if(side == Side::LEFT) return Side::RIGHT;
    else if(side == Side::RIGHT) return Side::LEFT;
    else if(side == Side::BOTTOM) return Side::RIGHT;
    else return Side::NONE;
}

BoxBound::BoxBound(){
    this->b_type = BoundType::BOX;
}

BoxBound::BoxBound(sf::Vector2f position, float width, float height, BoundName name):
    Bound(BoundType::BOX, name)
{
    sf::Transformable::setPosition(position);
    this->height = height;
    this->width = width;
    this->halfHeight = this->height/2;
    this->halfWidth = this->width/2;
}
BoxBound::~BoxBound(){}


const float BoxBound::getWidth(){return this->width;}
const float BoxBound::getHeight(){return this->height;}
void BoxBound::setWidth(float _width){this->width = _width;}
void BoxBound::setHeight(float _height){this->height = _height;}
const float BoxBound::getHalfWidth() const{return this->halfWidth;}
const float BoxBound::getHalfHeight() const{return this->halfHeight;}
const sf::Vector2f BoxBound::getCenter() const{return sf::Transformable::getPosition()+sf::Vector2f(halfWidth, halfHeight);}
const float BoxBound::getLeft() const{return this->getCenter().x - this->halfWidth;}
const float BoxBound::getRight() const{return this->getCenter().x + this->halfWidth;}
const float BoxBound::getTop() const{return this->getCenter().y - this->halfHeight;}
const float BoxBound::getBottom() const{return this->getCenter().y + this->halfHeight;}

bool BoxBound::checkCollision(const BoxBound& b1, const BoxBound& b2)
{
    // check for the collision between two box bounds
    if(b1.getLeft() <= b2.getRight() && b1.getRight() >= b2.getLeft())
    {
        if(b1.getTop() <= b2.getBottom() && b1.getBottom() >= b2.getTop())
            return true;
    }
    return false;
}
