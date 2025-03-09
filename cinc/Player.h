#ifndef PLAYER_H
#define PLAYER_H



#include "../cinc/Entity.h"

class Enemy;

class Player : public Entity
{
  public:
    Player() = default;
    Player(Vec center, float angle, float turnSpeed, float speed, Color color);

    void updateDirection();
    void timeToShoot();
    void offScreen() override;
    void render();

  private:
};

#endif
