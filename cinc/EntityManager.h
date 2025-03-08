#include "../cinc/Enemy.h"
#include "../cinc/Entity.h"

#include "../inc/Random.h"

class EntityManager
{
  public:
    EntityManager(int a, int b, int c) : x{a}, y{b}, z{c}
    {
    }

    Entity *spawnEnemy()
    {
        static double lastTime{GetTime()};

        double currentTime{GetTime()};
        if (currentTime - lastTime >= 3)
        {
            lastTime = currentTime;
            return new Enemy{Vec{-200, Random::getReal(100.0f, 900.0f)}, 0, 0, 4, RED};
        }

        return nullptr;
    }

    Entity *spawnMeteor()
    {
        static double lastTime{GetTime()};

        double currentTime{GetTime()};
        if (currentTime - lastTime >= 0.5)
        {
            lastTime = currentTime;
            return new Entity{Vec{-200, Random::getReal(100.0f, 900.0f)}, Vec{20, 20}, 0, 0, 3, BROWN};
        }

        return nullptr;
    }

  private:
    int x{};
    int y{};
    int z{};
};
