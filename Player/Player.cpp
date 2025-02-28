#include "../inc/Aggregates.h"
#include "../inc/Constants.h"
#include "../Enemy/Enemy.h"

#include "Player.h"

Player::Player(Vec center, float angle, float turnSpeed, float speed)
: Entity{ center, Vec{ Constants::playerSize, Constants::playerSize }, angle, turnSpeed, speed }
{
    updateHitBox();
}

void Player::updateDirection()
{
    if (IsKeyDown(KEY_A))
        m_angle -= m_turnSpeed;
    if (IsKeyDown(KEY_D))
        m_angle += m_turnSpeed;
}

void Player::timeToShoot()
{
    double currentTime{ GetTime() };
    if (currentTime - m_lastTime < 0.35)
        return;

    m_bullets.push_front(Bullet{ m_center, m_angle, 0, 6 }); 

    m_lastTime = currentTime;
}

void Player::shoot()
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

void Player::hitEnemy(Enemy& enemy)
{
    for (auto& bullet : m_bullets)
    {
        if (bullet.checkCollision(enemy.getTl(), enemy.getBr()))
        {
            bullet.setDead();
            enemy.setDead();
        }            
    }
}

bool Player::offScreen()
{
    return (m_tl.x <= 0 || m_tl.y <= 0 || m_br.x >= Constants::windowSize || m_br.y >= Constants::windowSize);
}


void Player::render()
{
    DrawText(TextFormat("%d", std::size(m_bullets)), 20, 20, 20, RED);
    DrawRectangleLines(toI(m_tl.x), toI(m_tl.y), toI(m_dim.x), toI(m_dim.y), RED);
}
