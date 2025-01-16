#include <functional>
#include <limits>
#include <print>
#include <string>
#include <unordered_map>

#include "solution.hpp"
#include "utils.hpp"

struct Vec2i {
    i32 r; // y
    i32 c; // x
};

constexpr const i64 EMPTY = 0;
constexpr const i64 RESTING_WATER = 1;
constexpr const i64 FLOWING_WATER = 2;
constexpr const i64 WALL = 3;
constexpr const i64 VOID = 4;

template<>
struct std::hash<Vec2i>
{
    std::size_t operator()(const Vec2i& v) const {
        return std::hash<i32>()(v.r) ^ (std::hash<i32>()(v.c) << 1);
    }
};

bool operator==(const Vec2i& a, const Vec2i& b) {
    return a.r == b.r and a.c == b.c;
}

i64 fill(std::unordered_map<Vec2i, i32>& map, Vec2i pos, i64 max_r) {
    if (pos.r > max_r) {
        return VOID;
    }
    if (!map.contains(pos)) {
        map[pos] = EMPTY;
    }
    if (map[pos] != EMPTY) {
        return map[pos];
    }

    map[pos] = FLOWING_WATER;
    i64 below = fill(map, Vec2i(pos.r + 1, pos.c), max_r);

    if (below == WALL or below == RESTING_WATER) {
        bool left_resting = true;
        i64 left = pos.c - 1;
        for (; map[Vec2i(pos.r, left)] != WALL; --left) {
            i64 down = fill(map, Vec2i(pos.r + 1, left), max_r);
            if (down != WALL and down != RESTING_WATER) {
                left_resting = false;
                --left;
                break;
            }
        }

        bool right_resting = true;
        i64 right = pos.c + 1;
        for (; map[Vec2i(pos.r, right)] != WALL; ++right) {
            i64 down = fill(map, Vec2i(pos.r + 1, right), max_r);
            if (down != WALL and down != RESTING_WATER) {
                right_resting = false;
                ++right;
                break;
            }
        }

        bool resting = left_resting and right_resting;
        for (i64 c = left + 1; c < right; ++c) {
            map[Vec2i(pos.r, c)] = resting ? RESTING_WATER : FLOWING_WATER;
        }
    }
    return map[pos];
}

template <>
void
solution<17>::solve(std::ifstream& input)
{
    std::unordered_map<Vec2i, i32> map;
    std::string line;
    while (std::getline(input, line)) {
        if (line[0] == 'x') {
            auto [col_str, row_range] = fixed_split<2>(line, ", ");
            i64 c = convert<i64>(col_str.substr(2));
            auto [r_min, r_max] = type_split<i64, 2>(row_range.substr(2), "..");

            for (i64 r = r_min; r <= r_max; ++r) {
                map[Vec2i(r, c)] = WALL;
            }
        } else {
            auto [row_str, col_range] = fixed_split<2>(line, ", ");
            i64 r = convert<i64>(row_str.substr(2));
            auto [c_min, c_max] = type_split<i64, 2>(col_range.substr(2), "..");

            for (i64 c = c_min; c <= c_max; ++c) {
                map[Vec2i(r, c)] = WALL;
            }
        }
    }

    i64 max_r = std::numeric_limits<i64>::min();
    i64 min_r = std::numeric_limits<i64>::max();
    for (const auto& [k, v] : map) {
        if (k.r > max_r) {
            max_r = k.r;
        }
        if (k.r < min_r) {
            min_r = k.r;
        }
    }

    fill(map, Vec2i(0, 500), max_r);

    i64 p1 = 0;
    i64 p2 = 0;
    for (const auto& [k, v] : map) {
        if (k.r >= min_r and k.r <= max_r) {
            if (v == FLOWING_WATER) {
                ++p1;
            } else if (v == RESTING_WATER) {
                ++p1;
                ++p2;
            }
        }
    }


    std::println("{}", p1);
    std::println("{}", p2);
}
