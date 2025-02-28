#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>

#include "Aggregates.h"
#include "../Sprite/Sprite.h"

int toI(float value);

class Entity
{
public:
    Entity() = default;
    ~Entity() = default;

    Entity(Vec center, Vec dim, float angle, float turnSpeed, float speed);

    void move();
    void render();
    bool checkCollision(Vec tl, Vec br) const;

    Vec getTl() const;
    Vec getBr() const;

    Vec getCenter() const { return m_center; }

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
    bool m_dead{};
    double m_lastTime{};

    void updateHitBox();
     
private:
};

#endif
