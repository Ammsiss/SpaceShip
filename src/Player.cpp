#include <raylib.h>
#include <deque>

#include "../cinc/Player.h"

#include "../cinc/Enemy.h"
#include "../cinc/Entity.h"
#include "../cinc/EntityManager.h"
#include "../cinc/Sprite.h"

#include "../inc/Aggregates.h"
#include "../inc/Constants.h"
#include "../inc/Helper.h"

Player::Player(Vec center, float angle, float turnSpeed, float speed, Color color, bool goingRight, Sprite::Type textureType)
    : Entity{center, Vec{Constants::playerSize, Constants::playerSize}, angle, turnSpeed, speed, color, goingRight, textureType}
{
    updateHitBox();
}

void Player::updateDirection()
{
    if (IsKeyDown(KEY_A))
        m_angle -= m_turnSpeed;
    if (IsKeyDown(KEY_D))
        m_angle += m_turnSpeed;
}

void Player::timeToShoot(Sound& sound)
{
    if (m_dead)
        return;

    static double lastTime{GetTime()};

    double currentTime{GetTime()};
    if (currentTime - lastTime >= 0.35)
    {
        PlaySound(sound);
        EntityManager::spawnPlayerBullet(m_center, m_angle);
        lastTime = currentTime;
    }
}

void Player::offScreen()
{
    if (m_tl.x <= 0 || m_tl.y <= 0 || m_br.x >= Constants::windowSize || m_br.y >= Constants::windowSize)
    {
        m_dead = true;
        Helper::spawnParticles(GREEN, m_center);
    }
}

void Player::render()
{
    static std::deque<Abomination> aboms{};

    aboms.push_back({{m_center.x, m_center.y, 8, 10}, {4, 3}, m_angle, 1.0f}); 

    for (std::size_t i{ 0 }; i < aboms.size(); ++i)
    {
        aboms[i].alpha -= 0.03f;
        aboms[i].rec.height -= 0.5f;

        DrawRectanglePro(aboms[i].rec, aboms[i].vec, aboms[i].angle, Fade(GREEN, aboms[i].alpha));
    }

    aboms.erase(std::remove_if(aboms.begin(), aboms.end(),
                [](const auto& i)
                {
                    return i.alpha <= 0;
                }), aboms.end());

    float angle{ Random::getReal((m_angle - 180) - 20, (m_angle - 180) + 20) };
    Vec center{ Random::getReal(m_center.x - 5, m_center.x + 5), Random::getReal(m_center.y - 5, m_center.y + 5)};
    EntityManager::spawnParticle(center, angle, true, 1, GREEN, 2.5);

    DrawTexturePro(Sprite::getTexture(m_textureType), { 0, 0, 50, 50 }, { m_center.x, m_center.y, 50, 50 }, { 25, 25 }, m_angle, WHITE);
}

void Player::collisionLogic()
{
    Helper::spawnParticles(GREEN, m_center);

    m_dead = true;
}

