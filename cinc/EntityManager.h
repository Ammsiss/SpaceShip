#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <raylib.h>
#include <deque>

#include "../cinc/Entity.h"

class EntityManager
{
  public:
    static void spawnEnemy();
    static void spawnMeteorNow(Vec position, float angle, bool goingRight);
    static void spawnMeteor();
    static void spawnExploder();
    static void spawnBullet(Vec pos, float angle);
    static void spawnPlayerBullet(Vec pos, float angle);
    static void spawnParticle(Vec pos, float angle, bool goingRight, float speed, Color color, float size = 3);
    static void cleanParticles();
    static void cleanEntities(int& score);
    static void cleanPlayerBullets();
    static std::deque<Entity*>& getEntities();
    static std::deque<Entity*>& getPlayerBullets();
    static std::deque<Entity*>& getParticles();

  private:
    static inline std::deque<Entity*> s_entities{};
    static inline std::deque<Entity*> s_playerBullets{};
    static inline std::deque<Entity*> s_particles{};
};

#endif
