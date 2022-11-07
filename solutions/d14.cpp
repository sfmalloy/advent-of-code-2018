#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <string>

#include "solution.hpp"
#include "utils.hpp"

template<>
void
solution<14>::solve(std::ifstream& input)
{
    u32 iters = convert<i32>(readline(input));
    std::vector<i32> sequence;
    u32 seq = iters;
    while (seq > 0)
    {
        sequence.push_back(seq % 10);
        seq /= 10;
    }
    std::reverse(std::begin(sequence), std::end(sequence));

    std::vector<i32> scores{3, 7};
    scores.reserve((2 * iters) + 2);

    u32 a = 0;
    u32 b = 1;
    for (u32 i = 0; scores.size() < iters + 10; ++i)
    {
        u32 next = scores[a] + scores[b];
        u32 first = next >= 10;
        u32 second = first ? next - 10 : next;
        if (first)
            scores.push_back(first);
        scores.push_back(second);
        a = (1 + a + scores[a]) % scores.size();
        b = (1 + b + scores[b]) % scores.size();
    }

    for (u32 i = iters; i < iters + 10; ++i)
        std::cout << scores[i];
    std::cout << '\n';

    scores = {3, 7};
    a = 0;
    b = 1;
    std::deque<u32> potential;
    for (;;)
    {
        u32 next = scores[a] + scores[b];
        u32 first = next >= 10;
        u32 second = first ? next - 10 : next;
        if (first)
            scores.push_back(first);
        scores.push_back(second);
        if (second == sequence[0])
            potential.push_back(scores.size() - 1);
      
        a = (1 + a + scores[a]) % scores.size();
        b = (1 + b + scores[b]) % scores.size();

        for (i32 p = 0; p < potential.size(); ++p)
        {
            if (potential[p] + sequence.size() >= scores.size())
                break;
            bool found = true;
            for (u32 i = 0; found && i < sequence.size(); ++i)
            {
                if (scores[potential[p] + i] != sequence[i])
                    found = false;
            }
            if (found)
            {
                std::cout << potential[p] << '\n';
                return;
            }
            else
            {
                potential.pop_front();
                --p;
            }
        }
    }
}