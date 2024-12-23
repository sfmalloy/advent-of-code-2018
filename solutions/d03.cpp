#include <iostream>
#include <string>
#include <vector>

#include "solution.hpp"
#include "utils.hpp"

struct Rect
{
    i32 x;
    i32 y;
    i32 w;
    i32 h;
};

template<>
void
solution<3>::solve(std::ifstream& input)
{
    std::string test;

    std::vector<Rect> areas;
    std::vector<std::vector<i32>> points(1000, std::vector<i32>(1000));

    while (std::getline(input, test))
    {
        auto [num, data] = fixed_split<2>(test, " @ ");
        auto [coords, area] = fixed_split<2>(data, ": ");
        auto [x_str, y_str] = fixed_split<2>(coords, ",");
        auto [w_str, h_str] = fixed_split<2>(area, "x");

        areas.push_back(Rect{convert<i32>(x_str), convert<i32>(y_str), convert<i32>(w_str), convert<i32>(h_str)});
        for (i32 y = areas.back().y; y < areas.back().y + areas.back().h; ++y) 
            for (i32 x = areas.back().x; x < areas.back().x + areas.back().w; ++x)
                ++points[y][x];
    }

    u32 total = 0;
    for (u32 i = 0; i < points.size(); ++i)
        for (u32 j = 0; j < points.size(); ++j)
            if (points[i][j] > 1)
                ++total;

    std::cout << total << '\n';

    for (size_t r = 0; r < areas.size(); ++r)
    {
        bool found = true;
        for (int y = areas[r].y; found && y < areas[r].y + areas[r].h; ++y) 
            for (int x = areas[r].x; found && x < areas[r].x + areas[r].w; ++x)
                if (points[y][x] > 1)
                    found = false;
        if (found)
        {
            std::cout << r + 1 << '\n';
            return;
        }
    }

}
