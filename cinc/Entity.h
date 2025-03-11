#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>

#include "../inc/Aggregates.h"
#include "../cinc/Sprite.h"

class Entity
{
  public:
    Entity() = default;
    virtual ~Entity() = default;

    Entity(Vec center, Vec dim, float angle, float turnSpeed, float speed, Color color, bool goingRight, Sprite::Type textureType);

    void move();
    void render() const;
    void render(Color color) const;
    void checkCollision(Entity &entity);
    virtual void offScreen();
    void updateEntity();

    Vec getCenter() const
    {
        return m_center;
    }

    bool getDead() const;
    void setDead(bool dead);

    bool getKillStatus() const;

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
    bool m_goingRight{ true };
    bool m_killedByPlayer{ false };
    Sprite::Type m_textureType{};

    void updateHitBox();

  private:
};

#endif
