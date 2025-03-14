#include <cmath>
#include <raylib.h>

#include "../cinc/Entity.h"
#include "../cinc/Sprite.h"

#include "../inc/Aggregates.h"
#include "../inc/Helper.h"

Entity::Entity(Vec center, Vec dim, float angle, float turnSpeed, float speed, Color color, bool goingRight, Sprite::Type textureType)
    : m_center{center}, m_dim{dim}, m_angle{angle}, m_turnSpeed{turnSpeed}, m_speed{speed}, m_color{color}, m_goingRight{ goingRight }, m_textureType{ textureType }
{
}

void Entity::move()
{
    m_center.x += (std::cos(Helper::toRad(m_angle)) * m_speed);
    m_center.y += (std::sin(Helper::toRad(m_angle)) * m_speed);

    updateHitBox();
}

void Entity::render()
{
    float angle{ Random::getReal((m_angle - 180) - 20, (m_angle - 180) + 20) };
    Vec center{Random::getReal(m_center.x - 15, m_center.x + 15), Random::getReal(m_center.y - 15, m_center.y + 15)};
    EntityManager::spawnParticle(center, angle, true, 2, DARKBROWN);

    DrawTexture(Sprite::getTexture(m_textureType), Helper::toI(m_tl.x), Helper::toI(m_tl.y), WHITE);
}

void Entity::renderParticle()
{
    double currentTime{ GetTime() };
    if (currentTime - m_particleTimer >= 0.1)
    {
        alpha -= 0.1f;
        if (alpha <= 0)
            m_dead = true;

        m_particleTimer = currentTime;
    }

    DrawRectangle(Helper::toI(m_center.x), Helper::toI(m_center.y), Helper::toI(m_dim.x), Helper::toI(m_dim.y), Fade(m_color, alpha));
}

void Entity::collisionLogic()
{
    Helper::spawnParticles(GRAY, m_center);

    m_dead = true;
    m_killedByPlayer = true;
}

void Entity::checkCollision(Entity& entity, Sound& sound)
{
    if (m_dead)
        return;

    if ((std::fmax(entity.m_tl.x, m_tl.x) <= std::fmin(entity.m_br.x, m_br.x) &&
         std::fmax(entity.m_tl.y, m_tl.y) <= std::fmin(entity.m_br.y, m_br.y)))
    {
        PlaySound(sound);

        this->collisionLogic();
        entity.collisionLogic();
    }
}

void Entity::offScreen()
{
    if (m_goingRight)
    {
        if (m_tl.x > Constants::windowSize)
            m_dead = true;
    }
    else
    {
        if (m_br.x < 0)
            m_dead = true;
    }
}

void Entity::updateHitBox()
{
    m_tl.x = m_center.x - (m_dim.x / 2);
    m_tl.y = m_center.y - (m_dim.y / 2);

    m_br.x = m_center.x + (m_dim.x / 2);
    m_br.y = m_center.y + (m_dim.y / 2);
}

void Entity::updateEntity()
{
    if (m_dead)
        return;

    move();
    render();
    offScreen();
}
