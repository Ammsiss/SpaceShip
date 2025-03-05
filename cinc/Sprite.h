#ifndef SPRITE_H
#define SPRITE_H

#include <raylib.h>
#include <string>

class Sprite
{
public:
    Sprite() = default;

    Sprite(std::string name)
    : m_texture{ LoadTexture(("../sprites/" + name).c_str()) }
    {}

    ~Sprite()
    {
        if (m_texture.id != 0)
            UnloadTexture(m_texture);
    }

    Sprite(const Sprite& sprite) = delete;
    Sprite& operator=(const Sprite& sprite) = delete;

    Sprite(Sprite&& sprite) noexcept
    {
        m_texture.id = sprite.m_texture.id;
        sprite.m_texture.id = 0;
    }

    Sprite& operator=(Sprite&& sprite) noexcept
    {
        m_texture.id = sprite.m_texture.id;
        sprite.m_texture.id = 0;

        return *this;
    }

private:
    Texture2D m_texture{};
};

#endif
