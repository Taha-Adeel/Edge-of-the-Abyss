#include "BoxBound.h"
#include <cmath>
#include <assert.h>

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
const float BoxBound::getEnclosingRadius() const {return this->enclosingRadius;}

void BoxBound::setWidth(float _width){
    this->width = _width;
    this->enclosingRadius = sqrt(width*width + height*height)/2.f;
}
void BoxBound::setHeight(float _height){
    this->height = _height;
    this->enclosingRadius = sqrt(width*width + height*height)/2.f;    
}

const float BoxBound::getLeft() const{return this->getPosition().x;}
const float BoxBound::getRight() const{return this->getLeft() + this->width;}
const float BoxBound::getTop() const{return this->getPosition().y;}
const float BoxBound::getBottom() const{return this->getTop() + this->height;}
const sf::Vector2f BoxBound::getCenter() const {
    return sf::Vector2f(getLeft() + width/2.f, getTop() + height/2.f);
}


bool BoxBound::checkCollision(const BoxBound& b1, const BoxBound& b2)
{
    // check for the collision between two box bounds
    if(b1.getLeft() <= b2.getRight() && b1.getRight() > b2.getLeft() 
        && b1.getTop() <= b2.getBottom() && b1.getBottom() >= b2.getTop())
            return true;

    return false;
}

/**
 * @brief Returns the side of *this which is colliding with tile.
 * 
 * precondition - *this and tile are colliding.
 * 
 * @param tile 
 * @return SIDE 
 */
SIDE BoxBound::getCollisionSide(const BoxBound& tile){
    // assert(checkCollision(*this, tile));

	float amtRight = this->getRight() - tile.getLeft();
	float amtLeft = this->getLeft() - tile.getRight();
	float amtTop = this->getTop() - tile.getBottom();
	float amtBottom = this->getBottom() - tile.getTop();

	float lowest =  std::min({fabs(amtRight), fabs(amtLeft), fabs(amtTop), fabs(amtBottom)});

	return
        (lowest == fabs(amtBottom) || fabs(amtBottom) < tolerance) ? SIDE::BOTTOM :
        (lowest == fabs(amtTop) || fabs(amtTop) < tolerance) ? SIDE::TOP :
        lowest == fabs(amtLeft) ? SIDE::LEFT : SIDE::RIGHT;
}