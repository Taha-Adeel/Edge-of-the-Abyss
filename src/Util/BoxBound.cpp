#include "BoxBound.h"

BoxBound::BoxBound(sf::Vector2f center, float width, float height)
{
    this->center = center;
    this->height = height;
    this->width = width;
    this->halfHeight = this->height/2;
    this->halfWidth = this->width/2; 
}