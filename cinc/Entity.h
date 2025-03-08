#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>

#include "../inc/Aggregates.h"

class Entity
{
  public:
    Entity() = default;
    virtual ~Entity() = default;

    Entity(Vec center, Vec dim, float angle, float turnSpeed, float speed, Color color);

    void move();
    void render() const;
    void checkCollision(Entity &entity);
    void updateEntity();

    Vec getTl() const;
    Vec getBr() const;

    Vec getCenter() const
    {
        return m_center;
    }

    bool getDead() const;
    void setDead();

  protected:
    Vec m_center{};
    Vec m_dim{};
    Vec m_tl{};
    Vec m_br{};
    float m_angle{};
    float m_turnSpeed{};
    float m_speed{};
    bool m_dead{false};
    Color m_color{RED};

    void updateHitBox();

  private:
};

#endif
