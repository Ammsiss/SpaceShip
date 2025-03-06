#include "../cinc/Bullet.h"

#include "../inc/Constants.h"

class Entity;

Bullet::Bullet(Vec center, float angle, float turnSpeed, float speed, Color color)
: Entity{ center, Vec{ Constants::bulletSize, Constants::bulletSize }, angle, turnSpeed, speed, color }
{
    updateHitBox();
}

bool Bullet::outOfBounds() const
{
    if (m_tl.x > Constants::windowSize || m_br.x < 0)
        return true;

    if (m_tl.y > Constants::windowSize || m_br.y < 0)
        return true;

    return false;
}
