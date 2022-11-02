#include <iostream>
#include <numeric>
#include <vector>

#include "solution.hpp"
#include "utils.hpp"

struct square
{
    i32 x;
    i32 y;
    i32 sum;
    i32 size;
};

square
region_sum(i32 size, std::vector<std::vector<i32>> cells)
{
    std::vector<std::vector<i32>> col_sums(cells.size(), std::vector<i32>(cells[0].size()));
    for (i32 r = 0; r < col_sums.size(); ++r)
    {
        i32 curr_sum = 0;
        for (i32 c = 0; c < size - 1; ++c)
            curr_sum += cells[r][c];
        for (i32 c = size - 1; c < col_sums[r].size(); ++c)
        {
            curr_sum += cells[r][c];
            col_sums[r][c - (size - 1)] = curr_sum;
            curr_sum -= cells[r][c - (size - 1)];
        }
    }

    square s{};
    for (i32 c = 0; c < col_sums[0].size(); ++c)
    {
        i32 rsum = 0;
        for (i32 r = 0; r < size - 1; ++r)
            rsum += col_sums[r][c];
        for (i32 r = size - 1; r < col_sums.size() - size; ++r)
        {
            rsum += col_sums[r][c];
            if (rsum > s.sum)
            {
                s.sum = rsum;
                s.x = c + 1;
                s.y = r + 1;
            }
            rsum -= col_sums[r - (size - 1)][c];
        }
    }

    s.y -= size - 1;
    s.size = size;
    return s;
}

template<>
void
solution<11>::solve(std::ifstream& input)
{
    i32 serial_num = convert<i32>(readline(input));
    std::vector<std::vector<i32>> cells(300, std::vector<i32>(300));
    for (i32 r = 0; r < cells.size(); ++r)
    {
        i32 y = r + 1;
        for (i32 c = 0; c < cells[r].size(); ++c)
        {
            i32 x = c + 1;
            i32 id = x + 10;
            cells[r][c] = (id * y) + serial_num;
            cells[r][c] *= id;
            cells[r][c] = ((cells[r][c] / 100) % 10) - 5;
        }
    }

    square part1 = region_sum(3, cells);
    std::cout << part1.x << ',' << part1.y << '\n';

    square max{0,0,0,0};
    for (i32 i = 1; i < cells.size(); ++i) 
    {
        auto s = region_sum(i, cells);
        if (max.sum < s.sum)
            max = s;
    }
    std::cout << max.x << ',' << max.y << ',' << max.size << '\n';
}
