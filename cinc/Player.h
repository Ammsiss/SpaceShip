#ifndef PLAYER_H
#define PLAYER_H

#include <deque>

#include "Bullet.h"

#include "../cinc/Entity.h"

class Enemy;

class Player : public Entity
{
public: 
    Player() = default;
    Player(Vec center, float angle, float turnSpeed, float speed);

    void updateDirection();
    void timeToShoot();
    void shoot();
    void hitEnemy(Enemy& enemy);
    bool offScreen();
    void render();

private:
    std::deque<Bullet> m_bullets{};
};

#endif
