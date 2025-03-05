#ifndef HELPER_H
#define HELPER_H

#include "../cinc/Entity.h"

#include "Constants.h"

namespace Helper
{
    inline int toI(float value)
    {
        return static_cast<int>(value);
    }

    inline float toRad(float angle)
    {
        return angle * (Constants::pi / 180.0f);
    }

    inline float toDeg(float radians)
    {
        return (radians * 180) / Constants::pi;
    }

    inline void updateEntity(Entity& entity)
    {
        entity.move();
        entity.render();
    }
}

#endif
