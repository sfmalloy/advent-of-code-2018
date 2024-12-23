#include <iostream>
#include <vector>
#include <unordered_map>

#include "solution.hpp"

template<>
void
solution<1>::solve(std::ifstream& input)
{
    std::vector<int> nums;

    int n;
    int sum = 0;
    while (input >> n) 
    {
        sum += n;
        nums.push_back(n);
    }

    std::cout << sum << '\n';

    std::unordered_map<int, int> seen;
    size_t idx = 0;
    sum = 0;
    while (seen[sum] < 2) 
    {
        sum += nums[idx++];
        seen[sum] += 1;
        if (idx == nums.size())
            idx = 0;
    }

    std::cout << sum << '\n';
}