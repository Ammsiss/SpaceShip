#ifndef SPRITE_H
#define SPRITE_H

#include <raylib.h>
#include <array>

class Sprite
{
  public:
    enum Type
    {
        player,
        enemy,
        exploder,
        exploderBaby,
        meteor,
        bullet,
        enemyBullet,
        particle,
        max_type,
    };

    static Texture2D& getTexture(Type type)
    {
        return m_textures[type];
    }

    static void cleanTextures()
    {
        for (auto& texture : m_textures)
        {
            UnloadTexture(texture);
        }
    }

    static void loadTextures()
    {
        m_textures[player] = LoadTexture("/Users/ammsiss/Projects/SpaceShip/sprites/player.png");
        m_textures[enemy] = LoadTexture("/Users/ammsiss/Projects/SpaceShip/sprites/enemy.png");
        m_textures[exploder] = LoadTexture("/Users/ammsiss/Projects/SpaceShip/sprites/exploder.png");
        m_textures[exploderBaby] = LoadTexture("/Users/ammsiss/Projects/SpaceShip/sprites/exploderBaby.png");
        m_textures[meteor] = LoadTexture("/Users/ammsiss/Projects/SpaceShip/sprites/meteor.png");
        m_textures[bullet] = LoadTexture("/Users/ammsiss/Projects/SpaceShip/sprites/bullet.png");
        m_textures[enemyBullet] = LoadTexture("/Users/ammsiss/Projects/SpaceShip/sprites/enemyBullet.png");
    }

  private:
    static inline std::array<Texture2D, 7> m_textures{};
};

#endif
