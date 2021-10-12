#include "coord.h"

Vec2i Vec2i::FromDirection(Direction dir)
{
    switch (dir)
    {
    case Direction::Left:
        return {-1, 0};
    case Direction::Right:
        return {1, 0};
    case Direction::Up:
        return {0, 1};
    case Direction::Down:
        return {0, -1};
    default:
        return {0, 0};
    }
    return {0, 0};
}

bool Vec2i::operator==(const Vec2i &r)
{
    return x == r.x && y == r.y;
}

bool Vec2i::operator!=(const Vec2i &r)
{
    return !(this->operator==(r));
}

Vec2i Vec2i::operator+(const Vec2i &r)
{
    return {x + r.x, y + r.y};
}

Vec2i Vec2i::operator-(const Vec2i &r)
{
    return {x - r.x, y - r.y};
}

Vec2i Vec2i::operator*(int r)
{
    return {x * r, y * r};
}

void Vec2i::operator+=(const Vec2i &r)
{
    x += r.x;
    y += r.y;
}

int Vec2i::operator%(const Vec2i &r)
{
    auto diff = this->operator-(r);
    return abs(diff.x) + abs(diff.y);
}

Vec2i::operator Vec2f()
{
    return {(float)x, (float)y};
}

Vec2f Vec2f::operator-(const Vec2f &r)
{
    return {x - r.x, y - r.y};
}

Vec2f Vec2f::operator*(int r)
{
    return {x * r, y * r};
}

Vec2f::operator Vec2i()
{
    return {(int)x, (int)y};
}