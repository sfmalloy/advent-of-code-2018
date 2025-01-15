#pragma once

#include "types.hpp"

struct Vec2 {
    i32 x;
    i32 y;

    Vec2(i32 x, i32 y);
    Vec2& operator+=(const Vec2& other);
};

Vec2 operator+(const Vec2& a, const Vec2& b);
Vec2 operator-(const Vec2& a, const Vec2& b);
