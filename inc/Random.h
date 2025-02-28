#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Random
{
public:
    template <typename T>
    static int getInt(T min, T max)
    {
        std::uniform_int_distribution<T> range{ min, max };

        return range(mt);
    }

    template <typename T>
    static T getReal(T min, T max)
    {
        std::uniform_real_distribution<T> range{ min, max };

        return range(mt);
    }

private:
    // Should probably improve in future
    static inline std::mt19937 mt{ std::random_device{}() };
};


#endif
