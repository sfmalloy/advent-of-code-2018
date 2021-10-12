#include <iostream>
#include <string>
#include <unordered_map>

#include "solution.hpp"
#include "utils.hpp"

struct Point
{
    int x;
    int y;

    bool
    operator==(const Point& other) const
    {
        return x == other.x && y == other.y;
    }
};

struct Rect
{
    int x;
    int y;
    int w;
    int h;
};

namespace std
{
    template<> 
    struct hash<Point>
    {
        size_t operator()(const Point& r) const noexcept
        {
            return std::hash<int>{}(r.x)
                ^ (std::hash<int>{}(r.y) << 1);
        }
    };
}

template<>
void
solution<3>::solve(std::ifstream& input)
{
    std::string test;

    std::vector<Rect> areas;
    std::unordered_map<Point, int> points;

    while (std::getline(input, test))
    {
        auto [num, data] = fixed_split<2>(test, " @ ");
        auto [coords, area] = fixed_split<2>(data, ": ");
        auto [x_str, y_str] = fixed_split<2>(coords, ",");
        auto [w_str, h_str] = fixed_split<2>(area, "x");

        areas.push_back(Rect{std::stoi(x_str), std::stoi(y_str), std::stoi(w_str), std::stoi(h_str)});
        for (int y = areas.back().y; y < areas.back().y + areas.back().h; ++y) 
            for (int x = areas.back().x; x < areas.back().x + areas.back().w; ++x)
                ++points[Point{x,y}];
    }

    unsigned total = 0;

    for (const auto& [pt, count] : points)
        if (count > 1)
            total += 1;
    
    std::cout << total << '\n';

    for (size_t r = 0; r < areas.size(); ++r)
    {
        bool found = true;
        for (int y = areas[r].y; found && y < areas[r].y + areas[r].h; ++y) 
            for (int x = areas[r].x; found && x < areas[r].x + areas[r].w; ++x)
                if (points.at(Point{x, y}) > 1)
                    found = false;
        if (found)
        {
            std::cout << r + 1 << '\n';
            return;
        }
    }

}
