#include "Enemy.h"

#include "../Player/Player.h"

#include "../inc/Aggregates.h"
#include "../inc/Constants.h"

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
    double radians{ std::atan2(playerCenter.y - m_center.y, playerCenter.x - m_center.x) };
    double degrees = (radians * 180) / Constants::pi;

    if (degrees < 0)
        degrees += 360;

    return static_cast<float>(degrees);
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
        bullet.move();
        bullet.render();
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
        if (bullet.checkCollision(player.getTl(), player.getBr()))
        {
            bullet.setDead();
            player.setDead();
        }            
    }
}

