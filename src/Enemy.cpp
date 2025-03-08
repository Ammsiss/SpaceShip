#include <algorithm>
#include <cmath>
#include <raylib.h>

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

void Enemy::offScreen()
{
    if (m_tl.x > 1000)
        m_dead = true;
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
        s_bullets.push_front(Bullet{m_center, getAngle(playerCenter), 0, 3, RED});
        m_lastTime = currentTime;
    }
}

void Enemy::shoot()
{
    for (auto &bullet : s_bullets)
    {
        bullet.updateEntity();
    }

    auto toRemove{std::remove_if(s_bullets.begin(), s_bullets.end(),
                                 [](const auto &bullet) { return bullet.outOfBounds() || bullet.getDead(); })};
    s_bullets.erase(toRemove, s_bullets.end());
}

void Enemy::hitPlayer(Player &player)
{
    for (auto &bullet : s_bullets)
    {
        player.checkCollision(bullet);
    }
}
