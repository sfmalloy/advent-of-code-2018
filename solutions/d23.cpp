#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "solution.hpp"
#include "utils.hpp"

struct Vec3 {
    i64 x;
    i64 y;
    i64 z;

    i64 manhattan_dist(const Vec3& other) {
        return std::abs(x - other.x) + std::abs(y - other.y) + std::abs(z - other.z);
    }

    i64 manhattan_dist(const Vec3& other) const {
        return std::abs(x - other.x) + std::abs(y - other.y) + std::abs(z - other.z);
    }
};

struct Nanobot {
    Vec3 pos;
    i64 r;
    i64 x_min;
    i64 x_max;
    i64 y_min;
    i64 y_max;
    i64 z_min;
    i64 z_max;

    Nanobot()
    : Nanobot(Vec3(), 0)
    { }

    Nanobot(const Vec3& pos, i64 r)
    : pos{pos}
    , r{r}
    , x_min{pos.x - r}
    , x_max{pos.x + r}
    , y_min{pos.y - r}
    , y_max{pos.y + r}
    , z_min{pos.z - r}
    , z_max{pos.z + r}
    { }
};

bool in_range(i64 min, i64 max, i64 n) {
    return n >= min and n <= max;
}

i64 part1(std::vector<Nanobot> nanobots, Nanobot biggest) {
    i64 valid = 0;
    for (const Nanobot& n : nanobots) {
        if (n.pos.manhattan_dist(biggest.pos) < biggest.r) {
            ++valid;
        }
    }

    return valid;
}

i64 part2(std::vector<Nanobot> nanobots, Nanobot biggest) {
    return 0;
}

template <>
void
solution<23>::solve(std::ifstream& input)
{
    std::vector<Nanobot> nanobots;
    std::string line;
    auto biggest = Nanobot();
    while (std::getline(input, line)) {
        auto [pos_ipt, r_ipt] = fixed_split<2>(line, ", ");
        auto [x, y, z] = type_split<i64, 3>(pos_ipt.substr(5, pos_ipt.length() - 6), ",");
        auto r = convert<i64>(split(r_ipt, "=")[1]);

        nanobots.emplace_back(Vec3(x, y, z), r);
        if (biggest.r < r) {
            biggest = nanobots.back();
        }
    }

    std::cout << part1(nanobots, biggest) << '\n';
    std::cout << part2(nanobots, biggest) << '\n';
}
