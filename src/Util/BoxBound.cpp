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
    this->height = height;
    this->width = width;
    this->halfHeight = this->height/2;
    this->halfWidth = this->width/2;
}
BoxBound::~BoxBound(){}


const float BoxBound::getWidth() const {return this->width;}
const float BoxBound::getHeight() const {return this->height;}
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
    // // check for the collision between two box bounds
    // if(b1.getLeft() <= b2.getRight() && b1.getRight() >= b2.getLeft())
    // {
    //     if(b1.getTop() <= b2.getBottom() && b1.getBottom() >= b2.getTop())
    //         return true;
    // }
    // return false;
    return sf::FloatRect(b1.getLeft(), b1.getTop(), b1.getWidth(), b1.getHeight()).intersects(
            sf::FloatRect(b2.getLeft(), b2.getTop(), b2.getWidth(), b2.getHeight())
    );
}
