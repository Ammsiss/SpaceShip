#ifndef BULLET_H
#define BULLET_H

#include "Sprite.h"
#include "Entity.h"

class Bullet : public Entity
{
  public:
    Bullet() = default;
    Bullet(Vec center, float angle, float turnSpeed, float speed, Color color, bool goingRight, Sprite::Type textureType);

    void offScreen() override;

  private:
};

#endif
