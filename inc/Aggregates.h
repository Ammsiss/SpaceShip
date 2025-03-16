#ifndef AGGREGATES_H
#define AGGREGATES_H

#include <raylib.h>

struct Vec
{
    float x{};
    float y{};
};

struct Abomination
{
    Rectangle rec{};
    Vector2 vec{};
    float angle{};
    float alpha{};
};

#endif
