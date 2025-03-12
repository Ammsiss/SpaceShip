#include "../cinc/EntityManager.h"
#include "../cinc/Exploder.h"
#include "../cinc/Enemy.h"
#include "../cinc/Entity.h"
#include "../cinc/Bullet.h"
#include "../cinc/Sprite.h"

#include "../inc/Random.h"

void EntityManager::spawnEnemy()
{
    static double lastTime{GetTime()};
    double currentTime{GetTime()};

    static double spawnTime{ 10 };
    if (currentTime - lastTime >= spawnTime)
    {
        lastTime = currentTime;
        s_entities.push_back(new Enemy{Vec{-200, Random::getReal(200.0f, 800.0f)},
            (Random::getInt(0, 1)) ? Random::getReal(330.0f, 360.0f) : Random::getReal(0.0f, 30.0f),
            0, 3, RED, true, Sprite::Type::enemy
        });

        if (spawnTime >= 2)
            spawnTime -= 0.25;
    }
}

void EntityManager::spawnMeteorNow(Vec position, float angle, bool goingRight)
{
    s_entities.push_back(new Entity{position, Vec{30, 30}, angle, 0, 2, PURPLE, goingRight, Sprite::Type::exploderBaby});
}

void EntityManager::spawnMeteor()
{
    static double lastTime{GetTime()};
    double currentTime{GetTime()};

    static double spawnTime{ 3 };
    if (currentTime - lastTime >= spawnTime)
    {
        lastTime = currentTime;
        s_entities.push_back(new Entity{Vec{-200, Random::getReal(100.0f, 900.0f)}, Vec{25, 25}, 0, 0, 3, BROWN, true, Sprite::Type::meteor});

        if (spawnTime >= 0.50)
            spawnTime -= 0.025;
    }
}

void EntityManager::spawnExploder()
{
    static double lastTime{ GetTime() };
    double currentTime{ GetTime() };

    static double spawnTime{ 30 };
    if (currentTime - lastTime >= spawnTime)
    {
        lastTime = currentTime;
        s_entities.push_back(new Exploder{ Vec{-200, Random::getReal(100.0f, 900.0f)}, 0, 0, 2, PURPLE, true, Sprite::Type::exploder});

        if (spawnTime >= 6)
            spawnTime -= 4;
    }
}

void EntityManager::spawnBullet(Vec pos, float angle)
{
    s_entities.push_back(new Bullet{pos, angle, 0, 4.5, RED, true, Sprite::Type::enemyBullet});
}

void EntityManager::spawnPlayerBullet(Vec pos, float angle)
{
    s_playerBullets.push_back(new Bullet{pos, angle, 0, 6, BLUE, true, Sprite::Type::bullet});
}

void EntityManager::spawnParticle(Vec pos, float angle, bool goingRight, float speed, Color color)
{
    s_particles.push_back(new Entity{pos, Vec{30, 30}, angle, 0, speed, color, goingRight, Sprite::Type::particle});
}

void EntityManager::cleanParticles()
{
    for (auto it = s_particles.begin(); it != s_particles.end();)
    {
        if ((*it)->getDead())
        {
            delete *it;
            it = s_particles.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void EntityManager::cleanEntities(int& score)
{
    for (auto it = s_entities.begin(); it != s_entities.end();)
    {
        if ((*it)->getDead())
        {
            if ((*it)->getKillStatus())
            {
                if (dynamic_cast<Enemy*>(*it))
                {
                    score += 100;
                }
                else if (dynamic_cast<Exploder*>(*it))
                {
                    score += 100;
                }
                else if (dynamic_cast<Bullet*>(*it))
                {
                    score += 10;
                }
                else
                {
                    score += 50;
                }
            }

            delete *it;
            it = s_entities.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void EntityManager::cleanPlayerBullets()
{
    for (auto it = s_playerBullets.begin(); it != s_playerBullets.end();)
    {
        if ((*it)->getDead())
        {
            delete *it;
            it = s_playerBullets.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

std::deque<Entity*>& EntityManager::getEntities()
{
    return s_entities;
}

std::deque<Entity*>& EntityManager::getPlayerBullets()
{
    return s_playerBullets;
}

std::deque<Entity*>& EntityManager::getParticles()
{
    return s_particles;
}
