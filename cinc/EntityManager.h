#include <deque>

#include "../cinc/Enemy.h"
#include "../cinc/Entity.h"
#include "../cinc/Bullet.h"

#include "../inc/Random.h"

class EntityManager
{
  public:
    static void spawnEnemy()
    {
        static double lastTime{GetTime()};
        double currentTime{GetTime()};

        if (currentTime - lastTime >= 3)
        {
            lastTime = currentTime;
            s_entities.push_back(new Enemy{Vec{-200, Random::getReal(100.0f, 900.0f)}, 0, 0, 4, RED});
        }
    }

    static void spawnMeteor()
    {
        static double lastTime{GetTime()};
        double currentTime{GetTime()};

        if (currentTime - lastTime >= 0.5)
        {
            lastTime = currentTime;
            s_entities.push_back(new Entity{Vec{-200, Random::getReal(100.0f, 900.0f)}, Vec{20, 20}, 0, 0, 3, BROWN});
        }
    }

    static void spawnBullet(Vec pos, float angle)
    {
        s_entities.push_back(new Bullet{pos, angle, 0, 3, RED});
    }

    static void spawnPlayerBullet(Vec pos, float angle)
    {
        s_playerBullets.push_back(new Bullet{pos, angle, 0, 6, BLUE});
    }

    static void cleanEntities()
    {
        for (auto it = s_entities.begin(); it != s_entities.end();)
        {
            if ((*it)->getDead())
            {
                delete *it;
                it = s_entities.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    static void cleanPlayerBullets()
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

    static std::deque<Entity*>& getEntities()
    {
        return s_entities;
    }

    static std::deque<Entity*>& getPlayerBullets()
    {
        return s_playerBullets;
    }

  private:
    static inline std::deque<Entity*> s_entities{};
    static inline std::deque<Entity*> s_playerBullets{};
};
