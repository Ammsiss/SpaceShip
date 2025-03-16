#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>

#include "../inc/Aggregates.h"
#include "../cinc/Sprite.h"

class Player;

class Entity
{
  public:
    Entity() = default;
    virtual ~Entity() = default;
    Entity(Vec center, Vec dim, float angle, float turnSpeed, float speed, Color color, bool goingRight, Sprite::Type textureType);

    virtual void collisionLogic();

    virtual void move();
    virtual void render();
    void renderParticle();
    void checkCollision(Entity &entity, Sound& sound);
    virtual void offScreen();
    void updateEntity();

    bool getDead() const { return m_dead; }
    void setDead(bool dead) { m_dead = dead; }

    Vec getCenter() const { return m_center; }
    void setCenter(Vec center) { m_center = center; }

    bool getKillStatus() const { return m_killedByPlayer; }
    void setKillStatus(bool killStatus) { m_killedByPlayer = killStatus; }

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
    double m_particleTimer{};
    float alpha{ 1.0f };

    void updateHitBox();

  private:
};

#endif
