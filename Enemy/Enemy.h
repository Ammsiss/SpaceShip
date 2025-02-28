#ifndef ENEMY_H
#define ENEMY_H

#include <deque>

#include "../Entity/Entity.h"
#include "../Bullet/Bullet.h"

#include "../inc/Aggregates.h"

class Player;

class Enemy : public Entity
{
public:
    Enemy() = default;
    Enemy(Vec center, float angle, float turnSpeed, float speed);

    bool offScreen() const;
    float getAngle(Vec playerCenter);
    void timeToShoot(Vec playerCenter);
    static void shoot();
    void hitPlayer(Player& player); 

private:
    static inline std::deque<Bullet> m_bullets{};
};

#endif
