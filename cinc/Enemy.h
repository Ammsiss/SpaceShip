#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

#include "../inc/Aggregates.h"
#include "raylib.h"

class Player;

// Enemy{ Vec center, float angle, float turnSpeed, float speed }
class Enemy : public Entity
{
  public:
    Enemy(Vec center, float angle, float turnSpeed, float speed, Color color, bool goingRight, Sprite::Type textureType);

    float getAngle(Vec playerCenter);
    void timeToShoot(Vec playerCenter);
    void offScreen() override;

  private:
    double m_lastTime{};
};

#endif
