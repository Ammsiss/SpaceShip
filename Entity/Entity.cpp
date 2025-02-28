#include <cmath>

#include "Entity.h"
#include "Aggregates.h"
#include "Constants.h"

Entity::Entity(Vec center, Vec dim, float angle, float turnSpeed, float speed)
: m_center{ center },
m_dim{ dim },
m_angle{ angle }, 
m_turnSpeed{ turnSpeed }, 
m_speed{ speed},
m_lastTime{ GetTime() }
{}

void Entity::move()
{
    m_center.x += (std::cos(m_angle * (Constants::pi / 180.0f)) * m_speed);
    m_center.y += (std::sin(m_angle * (Constants::pi / 180.0f)) * m_speed); 

    updateHitBox();
}

void Entity::render()
{
    DrawRectangleLines(toI(m_tl.x), toI(m_tl.y), toI(m_dim.x), toI(m_dim.y), RED);
}

bool Entity::checkCollision(Vec tl, Vec br) const
{
    return (std::fmax(tl.x, m_tl.x) <= std::fmin(br.x, m_br.x) &&
    std::fmax(tl.y, m_tl.y) <= std::fmin(br.y, m_br.y));
}

Vec Entity::getTl() const { return m_tl; }
Vec Entity::getBr() const { return m_br; } 

bool Entity::getDead() const { return m_dead; }
void Entity::setDead() { m_dead = true; }

void Entity::updateHitBox()
{
    m_tl.x = m_center.x - (m_dim.x / 2);
    m_tl.y = m_center.y - (m_dim.y / 2);

    m_br.x = m_center.x + (m_dim.x / 2);
    m_br.y = m_center.y + (m_dim.y / 2);
}

