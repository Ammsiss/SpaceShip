#ifndef HELPER_H
#define HELPER_H

#include "Constants.h"

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
}

#endif
