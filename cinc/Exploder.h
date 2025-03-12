#ifndef EXPLODER_H
#define EXPLODER_H

#include "../cinc/Entity.h"
#include "../cinc/Sprite.h"

#include "../inc/Aggregates.h"


class Exploder : public Entity
{
public:
    Exploder(Vec center, float angle, float turnSpeed, float speed, Color color, bool goingRight, Sprite::Type textureType);

    void takeHit(Entity& entity);
    void explode();

private:
    int m_hitCount{ 0 };
};

#endif
