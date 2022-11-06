#include <iostream>
#include <string>
#include <vector>

#include "solution.hpp"

enum direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

struct cart {
    u32 x;
    u32 y;
    direction dir;
    u32 irule;
};

template<>
void
solution<13>::solve(std::ifstream& input)
{
    std::vector<std::string> map(1);
    while (std::getline(input, map.back()))
        map.push_back("");
    map.pop_back();
}

/**
intersections:
    1. go left
    2. go straight
    3. go right
    4. repeat from 1
*/
