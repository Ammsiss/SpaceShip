#include "../cinc/Exploder.h"
#include "../cinc/Entity.h"
#include "../cinc/EntityManager.h"
#include "../cinc/Sprite.h"

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
    }
}

void Exploder::explode()
{
    EntityManager::spawnMeteorNow(m_center, 45, true);
    EntityManager::spawnMeteorNow(m_center, 135, false);
    EntityManager::spawnMeteorNow(m_center, 225, false);
    EntityManager::spawnMeteorNow(m_center, 315, true);
}
