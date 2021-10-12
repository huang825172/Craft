#pragma once

#include <math.h>

enum Direction
{
    Left = 0,
    Right = 1,
    Up = 2,
    Down = 3,
    Size = 4
};

class Vec2f;

class Vec2i
{
public:
    int x = 0;
    int y = 0;

    static Vec2i FromDirection(Direction dir);
    bool operator==(const Vec2i &r);
    bool operator!=(const Vec2i &r);
    Vec2i operator+(const Vec2i &r);
    Vec2i operator-(const Vec2i &r);
    Vec2i operator*(int r);
    void operator+=(const Vec2i &r);
    int operator%(const Vec2i &r);
    operator Vec2f();
};

class Vec2f
{
public:
    float x;
    float y;

    Vec2f operator-(const Vec2f &r);
    Vec2f operator*(int r);
    operator Vec2i();
};