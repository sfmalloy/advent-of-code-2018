#include "vec.hpp"
#include <cstdlib>

Vec2::Vec2(i64 r, i64 c)
  : r{r}
  , c{c}
{ }

Vec2& Vec2::operator+=(const Vec2& other) {
    this->r += other.r;
    this->c += other.c;
    return *this;
}

i64 Vec2::manhattan_dist(const Vec2& other) {
    return std::abs(this->r - other.r) + std::abs(this->c - other.c);
}

Vec2 operator+(const Vec2& a, const Vec2& b) {
    return Vec2(a.r + b.r, a.c + b.c);
}

Vec2 operator-(const Vec2& a, const Vec2& b) {
    return Vec2(a.r - b.r, a.c - b.c);
}

bool operator==(const Vec2& a, const Vec2& b) {
    return a.r == b.r and a.c == b.c;
}
