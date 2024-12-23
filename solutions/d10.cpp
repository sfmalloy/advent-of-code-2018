#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "solution.hpp"
#include "utils.hpp"

struct vec2
{
    i32 x;
    i32 y;
};

struct star
{
    vec2 pos;
    vec2 vel;

    void
    move()
    {
        pos.x += vel.x;
        pos.y += vel.y;
    }

    void
    back()
    {
        pos.x -= vel.x;
        pos.y -= vel.y;
    }
};

bool
step(std::vector<star>& stars)
{
    for (auto& s : stars)
        s.move();
    for (u32 i = 0; i < stars.size(); ++i)
    {
        bool found = false;
        for (u32 j = 0; j < stars.size(); ++j)
        {
            if (i != j)
            {
                i32 dx = abs(stars[i].pos.x - stars[j].pos.x);
                i32 dy = abs(stars[i].pos.y - stars[j].pos.y);
                if (dy + dx <= 2)
                {
                    found = true;
                    break;
                }
            }
        }
        if (!found)
            return 0;
    }
    return true;
}

template <>
void
solution<10>::solve(std::ifstream& input)
{
    std::string line;
    std::vector<star> stars;
    while (std::getline(input, line))
    {
        auto spline = split(line, "=");
        auto [px, py] = type_split<i32, 2>(spline[1].substr(1, spline[1].size() - 2), ", ");
        auto [vx, vy] = type_split<i32, 2>(spline[2].substr(1, spline[2].size() - 2), ", ");
        stars.push_back({{px, py}, {vx, vy}});
    }

    i32 t;
    for (t = 1; !step(stars); ++t);

    vec2 min{INT32_MAX, INT32_MAX};
    vec2 max{INT32_MIN, INT32_MIN};
    std::unordered_map<i32, std::unordered_map<i32, bool>> grid;
    for (auto& s : stars)
    {
        if (s.pos.x < min.x)
            min.x = s.pos.x;
        if (s.pos.x > max.x)
            max.x = s.pos.x;
        if (s.pos.y < min.y)
            min.y = s.pos.y;
        if (s.pos.y > max.y)
            max.y = s.pos.y;
        grid[s.pos.x][s.pos.y] = true;
    }
    for (i32 y = min.y; y <= max.y; ++y)
    {
        for (i32 x = min.x; x <= max.x; ++x)
        {
            std::cout << (grid[x][y] ? "█" : " ");
        }
        std::cout << '\n';
    }
    std::cout << "\n" << t << '\n';
}
