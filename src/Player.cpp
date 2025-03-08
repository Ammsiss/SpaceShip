#include <algorithm>
#include <raylib.h>

#include "../cinc/Player.h"

#include "../cinc/Enemy.h"
#include "../cinc/Entity.h"

#include "../inc/Aggregates.h"
#include "../inc/Constants.h"
#include "../inc/Helper.h"

Player::Player(Vec center, float angle, float turnSpeed, float speed, Color color)
    : Entity{center, Vec{Constants::playerSize, Constants::playerSize}, angle, turnSpeed, speed, color}
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
    static double lastTime{GetTime()};

    double currentTime{GetTime()};
    if (currentTime - lastTime >= 0.35)
    {
        m_bullets.push_front(Bullet{m_center, m_angle, 0, 6, BLUE});
        lastTime = currentTime;
    }
}

void Player::shoot()
{
    timeToShoot();

    for (auto &bullet : m_bullets)
    {
        bullet.updateEntity();
    }

    auto toRemove{std::remove_if(m_bullets.begin(), m_bullets.end(),
                                 [](const auto &bullet) { return bullet.outOfBounds() || bullet.getDead(); })};
    m_bullets.erase(toRemove, m_bullets.end());
}

void Player::hitEntity(Entity &entity)
{
    for (auto &bullet : m_bullets)
    {
        bullet.checkCollision(entity);
    }
}

bool Player::offScreen()
{
    return (m_tl.x <= 0 || m_tl.y <= 0 || m_br.x >= Constants::windowSize || m_br.y >= Constants::windowSize);
}

void Player::render()
{
    DrawText(TextFormat("%d", std::size(m_bullets)), 20, 20, 20, RED);
    DrawRectangleLines(Helper::toI(m_tl.x), Helper::toI(m_tl.y), Helper::toI(m_dim.x), Helper::toI(m_dim.y), RED);
}
