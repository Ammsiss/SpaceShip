#include <raylib.h>

#include "../cinc/Enemy.h"

#include "../cinc/Player.h"

#include "../inc/Aggregates.h"
#include "../inc/Helper.h"

Enemy::Enemy(Vec center, float angle, float turnSpeed, float speed)
: Entity{ center, Vec{ Constants::playerSize, Constants::playerSize }, angle, turnSpeed, speed }
{
    updateHitBox();
}

bool Enemy::offScreen() const
{
    if (m_tl.x > 1000)
        return true;

    return false;
}

float Enemy::getAngle(Vec playerCenter)
{
    float radians{ std::atan2(playerCenter.y - m_center.y, playerCenter.x - m_center.x) };
    float degrees = Helper::toDeg(radians);

    if (degrees < 0)
        degrees += 360;

    return degrees;
}

void Enemy::timeToShoot(Vec playerCenter)
{
    double currentTime{ GetTime() };
    if (currentTime - m_lastTime < 1)
        return;

    m_bullets.push_front(Bullet{ m_center, getAngle(playerCenter), 0, 3 }); 

    m_lastTime = currentTime;
}

void Enemy::shoot()
{
    for (auto& bullet : m_bullets)
    {
        Helper::updateEntity(bullet);
    }

    auto toRemove{ std::remove_if(m_bullets.begin(), m_bullets.end(),
        [](const auto& bullet)
        {
            return bullet.outOfBounds() || bullet.getDead();
        }
    )};
    m_bullets.erase(toRemove, m_bullets.end());
}

void Enemy::hitPlayer(Player& player)
{
    for (auto& bullet : m_bullets)
    {
        if (bullet.checkCollision(player))
        {
            bullet.setDead();
            player.setDead();
        }
    }
}

