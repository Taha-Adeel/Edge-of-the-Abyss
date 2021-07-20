#ifndef BOUNDS_H
#define BOUNDS_H

#include <SFML/Graphics.hpp>

enum class BOUNDTYPE {BOX, TRIANGLE};
enum class BOUNDNAME {TILE, SPIKE, PORTAL};
class Bound : public sf::Transformable
{
protected:
    BOUNDTYPE b_type;
    BOUNDNAME b_name;
public:
    Bound() = default;
    Bound(BOUNDTYPE, BOUNDNAME);
    virtual ~Bound();

    virtual const float getWidth() const = 0;
    virtual const float getHeight() const = 0;
    const BOUNDTYPE getBoundType() const ;
    const BOUNDNAME getBoundName() const ;

    static bool checkCollision(const Bound& b1, const Bound& b2);
};


#endif