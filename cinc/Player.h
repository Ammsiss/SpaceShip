#ifndef PLAYER_H
#define PLAYER_H

#include "../cinc/Entity.h"
#include "../cinc/Sprite.h"

class Enemy;

class Player : public Entity
{
  public:
    Player() = default;
    Player(Vec center, float angle, float turnSpeed, float speed, Color color, bool goingRight, Sprite::Type textureType);

    void updateDirection();
    void timeToShoot();
    void offScreen() override;

  private:
};

#endif
