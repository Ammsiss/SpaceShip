#include "../cinc/Exploder.h"
#include "../cinc/Entity.h"
#include "../cinc/EntityManager.h"
#include "../cinc/Sprite.h"
#include "../inc/Helper.h"

#include "../inc/Constants.h"


Exploder::Exploder(Vec center, float angle, float turnSpeed, float speed, Color color, bool goingRight, Sprite::Type textureType)
: Entity{ center, Vec{ Constants::exploderSize, Constants::exploderSize }, angle, turnSpeed, speed, color, goingRight, textureType }
{
    updateHitBox();
}

void Exploder::takeHit()
{
    ++m_hitCount;

    if (m_hitCount >= 2)
    {
        explode();
        m_killedByPlayer = true;
        m_dead = true;
        Helper::spawnParticles(PURPLE, m_center);
    }
}

void Exploder::explode()
{
    EntityManager::spawnMeteorNow(m_center, 45, true);
    EntityManager::spawnMeteorNow(m_center, 135, false);
    EntityManager::spawnMeteorNow(m_center, 225, false);
    EntityManager::spawnMeteorNow(m_center, 315, true);
}

void Exploder::render()
{
    float angle{ Random::getReal((m_angle - 180) - 20, (m_angle - 180) + 20) };
    Vec center{m_center.x - 30, Random::getReal(m_center.y + 30, m_center.y - 30)};
    EntityManager::spawnParticle(center, angle, true, 2, PURPLE);

    DrawTexture(Sprite::getTexture(m_textureType), Helper::toI(m_tl.x), Helper::toI(m_tl.y), WHITE);
}

void Exploder::collisionLogic()
{
    takeHit();
}
