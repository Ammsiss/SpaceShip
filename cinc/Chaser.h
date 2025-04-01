#include "../cinc/Sprite.h"
#include "../cinc/Entity.h"
#include "../cinc/EntityManager.h"

#include "Aggregates.h"
#include "Constants.h"
#include "Random.h"
#include "Helper.h"
#include "cinc/Player.h"

class Chaser : public Entity
{
public:
    Chaser(Vec center, float angle, float turnSpeed, float speed, Color color, bool goingRight, Sprite::Type textureType)
    : Entity{center, Vec{Constants::chaserSize, Constants::chaserSize}, angle, turnSpeed, speed, color, goingRight, textureType}
{
    updateHitBox();
}

    void render() override
    {
        float angle{ Random::getReal((m_angle - 180) - 20, (m_angle - 180) + 20) };
        Vec center{Random::getReal(m_center.x - 15, m_center.x + 15), Random::getReal(m_center.y - 15, m_center.y + 15)};
        EntityManager::spawnParticle(center, angle, true, 2, PURPLE);

        DrawTexture(Sprite::getTexture(m_textureType), Helper::toI(m_tl.x), Helper::toI(m_tl.y), WHITE);
    }

    void offScreen() override
    {
        if (m_tl.x > Constants::windowSize)
            m_dead = true;
    }

    void collisionLogic() override
    {
        Helper::spawnParticles(RED, m_center);
        m_dead = true;
        m_killedByPlayer = true;
    }

    void move() override
    {
        float radians{std::atan2(center.y - m_center.y, center.x - m_center.x)};
        float degrees = Helper::toDeg(radians);

        if (degrees < 0)
        {
            degrees += 360;
        }

        m_angle = degrees;
        m_center.x += (std::cos(Helper::toRad(degrees)) * m_speed);
        m_center.y += (std::sin(Helper::toRad(degrees)) * m_speed);

        updateHitBox();
    }

private:
};


