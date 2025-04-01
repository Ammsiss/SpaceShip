#include <cmath>
#include <raylib.h>

#include "../cinc/EntityManager.h"
#include "../cinc/Enemy.h"
#include "../cinc/Player.h"

#include "../inc/Aggregates.h"
#include "../inc/Constants.h"
#include "../inc/Helper.h"

Enemy::Enemy(Vec center, float angle, float turnSpeed, float speed, Color color, bool goingRight, Sprite::Type textureType)
    : Entity{center, Vec{Constants::enemySize, Constants::enemySize}, angle, turnSpeed, speed, color, goingRight, textureType}
{
    updateHitBox();
}

float Enemy::getAngle(Vec playerCenter)
{
    float radians{std::atan2(playerCenter.y - m_center.y, playerCenter.x - m_center.x)};
    float degrees = Helper::toDeg(radians);

    if (degrees < 0)
        degrees += 360;

    return degrees;
}

void Enemy::timeToShoot(Vec playerCenter)
{
    double currentTime{GetTime()};

    static double spawnTime{ 3 };
    if (currentTime - m_lastTime >= spawnTime)
    {
        EntityManager::spawnBullet(m_center, getAngle(playerCenter));
        m_lastTime = currentTime;

        if (spawnTime >= 0.5)
            spawnTime -= 0.01;
    }
}

void Enemy::offScreen()
{
    if (m_tl.x > Constants::windowSize)
        m_dead = true;
}

void Enemy::render()
{
    float angle{ Random::getReal((m_angle - 180) - 20, (m_angle - 180) + 20) };
    Vec center{Random::getReal(m_center.x - 15, m_center.x + 15), Random::getReal(m_center.y - 15, m_center.y + 15)};
    EntityManager::spawnParticle(center, angle, true, 2, RED);

    DrawTexture(Sprite::getTexture(m_textureType), Helper::toI(m_tl.x), Helper::toI(m_tl.y), WHITE);
}

void Enemy::collisionLogic()
{
    Helper::spawnParticles(RED, m_center);
    m_dead = true;
    m_killedByPlayer = true;
}

void test()
{
    int* s_ptr_a{ new int{ 5 } };
    delete s_ptr_a;

    int* s_ptr_m{ static_cast<int*>(operator new(sizeof(int))) };
    operator delete(s_ptr_m);

    int* m_ptr_a{ new int[]{ 5 } };
    delete[] m_ptr_a;

    int* m_ptr_m{ static_cast<int*>(operator new(sizeof(int) * 2)) };
    // for ()
    // {
    //     m_ptr_m->constructor()
    // }
    // for ()
    // {
    //      m_ptr_m->desctructor()
    //  }
    operator delete(m_ptr_m);
}
