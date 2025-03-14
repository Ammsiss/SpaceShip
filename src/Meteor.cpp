#include "../cinc/Meteor.h"
#include "../cinc/Entity.h"

#include "../inc/Constants.h"
#include "../inc/Aggregates.h"
#include "../inc/Random.h"
#include "../inc/Helper.h"

Meteor::Meteor(Vec center, float angle, float turnSpeed, float speed, Color color, bool goingRight, Sprite::Type textureType)
: Entity{center, Vec{Constants::meteorSize, Constants::meteorSize}, angle, turnSpeed, speed, color, goingRight, textureType}
{
    updateHitBox();
}

void Meteor::render()
{
    float angle{ Random::getReal((m_angle - 180) - 20, (m_angle - 180) + 20) };
    Vec center{Random::getReal(m_center.x - 15, m_center.x + 15), Random::getReal(m_center.y - 15, m_center.y + 15)};
    EntityManager::spawnParticle(center, angle, true, 2, DARKBROWN);

    DrawTexture(Sprite::getTexture(m_textureType), Helper::toI(m_tl.x), Helper::toI(m_tl.y), WHITE);
}

void Meteor::offScreen()
{
    if (m_tl.x > Constants::windowSize)
        m_dead = true;
}

void Meteor::collisionLogic()
{
    Helper::spawnParticles(DARKBROWN, m_center);
    m_dead = true;
    m_killedByPlayer = true;
}
