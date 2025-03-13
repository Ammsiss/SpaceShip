#ifndef HELPER_H
#define HELPER_H

#include <raylib.h>

#include "../cinc/EntityManager.h"

#include "Constants.h"
#include "Aggregates.h"
#include "Random.h"

namespace Helper
{
    template <typename T> inline int toI(T value)
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

    inline void spawnParticles(Color color, Vec center)
    {
        for (int i{ 0 }; i < 30; ++i)
        {
            int angle{ 270 };
            bool goingLeft{ false };
            while ( angle == 270 || angle == 90)
            {
                angle = Random::getInt(0, 360);
            }
            if (angle >= 90 && angle <= 270)
                goingLeft = true;

            EntityManager::spawnParticle(center, static_cast<float>(angle), !goingLeft, Random::getReal(1.0f, 3.0f), color, 8);
        }
    }


}

#endif
