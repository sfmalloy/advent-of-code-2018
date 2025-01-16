#pragma once

#include "types.hpp"
#include <functional>

struct Vec2 {
    i64 r;
    i64 c;

    Vec2(i64 r, i64 c);
    Vec2& operator+=(const Vec2& other);
    i64 manhattan_dist(const Vec2& other);
};

Vec2 operator+(const Vec2& a, const Vec2& b);
Vec2 operator-(const Vec2& a, const Vec2& b);
bool operator==(const Vec2& a, const Vec2& b);

template<>
struct std::hash<Vec2>
{
    std::size_t operator()(const Vec2& v) const {
        return std::hash<i64>()(v.r) ^ (std::hash<i64>()(v.c) << 1);
    }
};
