#ifndef BULLET_H
#define BULLET_H

#include "../Entity/Entity.h"

class Bullet : public Entity
{
public:
    Bullet() = default;
    Bullet(Vec center, float angle, float turnSpeed, float speed);

    bool outOfBounds() const;  
    
private:
};

#endif
