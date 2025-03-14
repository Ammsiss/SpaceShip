#include "../cinc/Bullet.h"
#include "../cinc/Sprite.h"
#include "../cinc/EntityManager.h"

#include "../inc/Constants.h"
#include "../inc/Random.h"
#include "../inc/Helper.h"

class Entity;

Bullet::Bullet(Vec center, float angle, float turnSpeed, float speed, Color color, bool goingRight, Sprite::Type textureType)
: Entity{center, Vec{Constants::bulletSize, Constants::bulletSize}, angle, turnSpeed, speed, color, goingRight, textureType}
{
    updateHitBox();
}

void Bullet::offScreen()
{
    if (m_tl.x > Constants::windowSize || m_tl.y > Constants::windowSize || m_br.x < 0 || m_br.y < 0)
        m_dead = true;
}

void Bullet::render()
{
    float angle{ Random::getReal((m_angle - 180) - 20, (m_angle - 180) + 20) };
    Vec center{ Random::getReal(m_center.x - 5, m_center.x + 5), Random::getReal(m_center.y - 5, m_center.y + 5)};
    EntityManager::spawnParticle(center, angle, true, 1, DARKGRAY);

    DrawTexture(Sprite::getTexture(m_textureType), Helper::toI(m_tl.x), Helper::toI(m_tl.y), WHITE);
}
