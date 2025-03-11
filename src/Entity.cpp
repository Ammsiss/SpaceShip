#include <cmath>
#include <raylib.h>

#include "../cinc/Entity.h"
#include "../cinc/EntityManager.h"
#include "../cinc/Enemy.h"
#include "../cinc/Exploder.h"
#include "../cinc/Sprite.h"

#include "../inc/Aggregates.h"
#include "../inc/Helper.h"
#include "../inc/Random.h"

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

void Entity::render() const
{
    DrawTexture(Sprite::getTexture(m_textureType), Helper::toI(m_tl.x), Helper::toI(m_tl.y), WHITE);
}

void Entity::render(Color color) const
{
     DrawRectangle(Helper::toI(m_tl.x), Helper::toI(m_tl.y), 3, 3, color);
}

void Entity::checkCollision(Entity& entity)
{
    if ((std::fmax(entity.m_tl.x, m_tl.x) <= std::fmin(entity.m_br.x, m_br.x) &&
         std::fmax(entity.m_tl.y, m_tl.y) <= std::fmin(entity.m_br.y, m_br.y)))
    {
        bool none{ true };
        Exploder* exploder{ dynamic_cast<Exploder*>(&entity) };
        if (exploder)
        {
            exploder->takeHit();
            none = false;
        }
        Enemy* enemy{ dynamic_cast<Enemy*>(&entity) };
        if (enemy)
        {
            for (int i{ 0 }; i < 90; ++i)
            {
                int angle{ 270 };
                bool goingLeft{ false };
                while ( angle == 270 || angle == 90)
                {
                    angle = Random::getInt(0, 360);
                }
                if (angle >= 90 && angle <= 270)
                    goingLeft = true;

                EntityManager::spawnParticle(m_center, static_cast<float>(angle), goingLeft, Random::getReal(1.0f, 3.0f));
            }

            none = false;
            m_dead = true;
            entity.m_dead = true;
            entity.m_killedByPlayer = true;
        }

        if (none)
        {
            m_dead = true;
            entity.m_dead = true;
            entity.m_killedByPlayer = true;
        }
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

bool Entity::getDead() const
{
    return m_dead;
}
void Entity::setDead(bool dead)
{
    m_dead = dead;
}

bool Entity::getKillStatus() const
{
    return m_killedByPlayer;
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
    move();
    render();
    offScreen();
}
