#include <iostream>
#include <iterator>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>

#include "solution.hpp"

enum direction
{
    NORTH = 0,
    EAST,
    SOUTH,
    WEST
};

enum turn_rule
{
    LEFT,
    STRAIGHT,
    RIGHT
};

struct vec2
{
    i32 r;
    i32 c;

    vec2()
      : r()
      , c()
    { }

    vec2(i32 row, i32 col)
      : r(row)
      , c(col)
    { }

    vec2(const vec2& other)
      : r(other.r)
      , c(other.c)
    { }

    vec2&
    operator=(const vec2& other)
    {
        if (this != &other)
        {
            r = other.r;
            c = other.c;
        }
        return *this;
    }

    bool
    operator==(const vec2& other) const
    {
        return r == other.r && c == other.c;
    }

    vec2
    operator+(const vec2& other)
    {
        return vec2{r + other.r, c + other.c};
    }

    bool
    operator<(const vec2& other)
    {
        return r < other.r || (r == other.r && c < other.c);
    }
};

struct cart
{
    vec2 pos;
    direction dir;
    turn_rule irule;
    i32 idx = -1;

    bool operator<(const cart& other)
    {
        return pos < other.pos;
    }
};

const vec2 deltas[4]
{
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1}
};

inline direction
ccw(direction curr)
{
    if (curr == NORTH)
        return WEST;
    return direction(curr - 1);
}

inline direction
cw(direction curr)
{
    if (curr == WEST)
        return NORTH;
    return direction(curr + 1);
}

template<>
void
solution<13>::solve(std::ifstream& input)
{
    std::vector<cart> carts;
    std::vector<std::string> map(1);
    i32 idx = 0;
    for (i32 row = 0; std::getline(input, map.back()); ++row)
    {
        for (i32 col = 0; col < map.back().size(); ++col)
        {
            char curr = map.back()[col];
            if (curr == '^')
            {
                map.back()[col] = '|';
                carts.push_back({{row, col}, NORTH, LEFT, idx++});
            }
            else if (curr == 'v')
            {
                map.back()[col] = '|';
                carts.push_back({{row, col}, SOUTH, LEFT, idx++});
            }
            else if (curr == '>')
            {
                map.back()[col] = '-';
                carts.push_back({{row, col}, EAST, LEFT, idx++});
            }
            else if (curr == '<')
            {
                map.back()[col] = '-';
                carts.push_back({{row, col}, WEST, LEFT, idx++});
            }
        }
        map.push_back("");
    }
    map.pop_back();

    std::vector<vec2> crash_positions;
    std::unordered_set<i32> crashes;
    while (crashes.size() < carts.size() - 1)
    {
        std::sort(std::begin(carts), std::end(carts));
        for (auto& c : carts)
        {
            if (!crashes.contains(c.idx))
            {
                c.pos = c.pos + deltas[c.dir];
                if (map[c.pos.r][c.pos.c] == '\\')
                {
                    if (c.dir == SOUTH)
                        c.dir = EAST;
                    else if (c.dir == EAST)
                        c.dir = SOUTH;
                    else if (c.dir == NORTH)
                        c.dir = WEST;
                    else
                        c.dir = NORTH;
                }
                else if (map[c.pos.r][c.pos.c] == '/')
                {
                    if (c.dir == NORTH)
                        c.dir = EAST;
                    else if (c.dir == EAST)
                        c.dir = NORTH;
                    else if (c.dir == SOUTH)
                        c.dir = WEST;
                    else
                        c.dir = SOUTH;
                }
                else if (map[c.pos.r][c.pos.c] == '+')
                {
                    if (c.irule == LEFT)
                    {
                        c.dir = ccw(c.dir);
                        c.irule = STRAIGHT;
                    }
                    else if (c.irule == STRAIGHT)
                    {
                        c.irule = RIGHT;
                    }
                    else if (c.irule == RIGHT)
                    {
                        c.dir = cw(c.dir);
                        c.irule = LEFT;
                    }
                }
                for (auto& other : carts)
                {
                    if (!crashes.contains(other.idx) && other.idx != c.idx && c.pos == other.pos)
                    {
                        crashes.insert(c.idx);
                        crashes.insert(other.idx);
                        crash_positions.push_back(c.pos);
                        break;
                    }
                }
            }
        }
    }

    std::cout << crash_positions[0].c << ',' << crash_positions[0].r << '\n';
    for (auto& c : carts)
    {
        if (!crashes.contains(c.idx))
            std::cout << c.pos.c << ',' << c.pos.r << '\n';
    }
}
