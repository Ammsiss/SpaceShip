#ifndef ENEMY_H
#define ENEMY_H

#include <deque>

#include "Entity.h"
#include "Bullet.h"

#include "../inc/Aggregates.h"
#include "raylib.h"

class Player;

// Enemy{ Vec center, float angle, float turnSpeed, float speed }
class Enemy : public Entity
{
public:
    Enemy() = default;
    Enemy(Vec center, float angle, float turnSpeed, float speed, Color color);

    void offScreen();
    float getAngle(Vec playerCenter);
    void timeToShoot(Vec playerCenter);
    static void shoot();
    static void hitPlayer(Player& player); 

    static void printBullet()
    {
        DrawText(TextFormat("%d", s_bullets.size()), 20, 20, 20, RED);
    }

private:
    static inline std::deque<Bullet> s_bullets{};
};

#endif
