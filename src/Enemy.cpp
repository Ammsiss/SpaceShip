#include <cmath>
#include <raylib.h>

#include "../cinc/EntityManager.h"
#include "../cinc/Enemy.h"
#include "../cinc/Player.h"

#include "../inc/Aggregates.h"
#include "../inc/Constants.h"
#include "../inc/Helper.h"

Enemy::Enemy(Vec center, float angle, float turnSpeed, float speed, Color color)
    : Entity{center, Vec{Constants::enemySize, Constants::enemySize}, angle, turnSpeed, speed, color}
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
    if (currentTime - m_lastTime >= 0.5)
    {
        EntityManager::spawnBullet(m_center, getAngle(playerCenter));
        m_lastTime = currentTime;
    }
}

void Enemy::offScreen()
{
    if (m_tl.x > Constants::windowSize)
        m_dead = true;
}
