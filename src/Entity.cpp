#include <cmath>
#include <raylib.h>

#include "../cinc/Entity.h"

#include "../inc/Aggregates.h"
#include "../inc/Helper.h"

Entity::Entity(Vec center, Vec dim, float angle, float turnSpeed, float speed, Color color)
    : m_center{center}, m_dim{dim}, m_angle{angle}, m_turnSpeed{turnSpeed}, m_speed{speed}, m_color{color}
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
    DrawRectangleLines(Helper::toI(m_tl.x), Helper::toI(m_tl.y), Helper::toI(m_dim.x), Helper::toI(m_dim.y), m_color);
}

void Entity::checkCollision(Entity &entity)
{
    if ((std::fmax(entity.m_tl.x, m_tl.x) <= std::fmin(entity.m_br.x, m_br.x) &&
         std::fmax(entity.m_tl.y, m_tl.y) <= std::fmin(entity.m_br.y, m_br.y)))
    {
        m_dead = true;
        entity.m_dead = true;
    }
}

Vec Entity::getTl() const
{
    return m_tl;
}
Vec Entity::getBr() const
{
    return m_br;
}

bool Entity::getDead() const
{
    return m_dead;
}
void Entity::setDead()
{
    m_dead = true;
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
}
