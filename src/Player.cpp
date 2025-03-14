#include <raylib.h>

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
    DrawTexture(Sprite::getTexture(m_textureType), Helper::toI(m_tl.x), Helper::toI(m_tl.y), WHITE);
}

void Player::collisionLogic()
{
    Helper::spawnParticles(GREEN, m_center);

    m_dead = true;
}
