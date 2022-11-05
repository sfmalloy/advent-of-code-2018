#include <iostream>
#include <string>
#include <unordered_map>

#include "solution.hpp"
#include "utils.hpp"

class state
{
public:
    state(const std::string& init)
      : negative("....")
      , positive(init)
      , negative_buffer("....")
      , positive_buffer(init)
    { }

    char&
    operator[](i64 idx)
    {
        if (idx >= 0)
            return positive_buffer[idx];
        else
            return negative_buffer[negative_buffer.size() + idx];
    }

    std::string
    substate(i64 start)
    {
        if (start >= 0)
            return positive.substr(start, 5);
        else if (start >= -4)
            return negative.substr(negative.size() + start) + positive.substr(0, 5 + start);
        return negative.substr(negative.size() + start, 5);
    }

    std::string
    get()
    {
        return negative + positive;
    }

    i64
    start()
    {
        // while (negative.size() > 0 && negative.substr(0, 4) != "....") {
        //     negative = negative.substr(1);
        // }
        while (positive.substr(positive.size() - 4) != "....") {
            positive += '.';
        }
        negative_buffer = negative;
        positive_buffer = positive;
        return -negative.size();
    }

    i64
    last()
    {
        return positive.size();
    }

    void
    buffer(i32 idx, char c)
    {
        if (idx >= 0)
            positive_buffer[idx] = c;
        else
            negative_buffer[negative_buffer.size() + idx];
    }

    void
    flush()
    {
        negative = negative_buffer;
        positive = positive_buffer;
    }

private:
    std::string negative;
    std::string positive; // also includes 0 which is technically not positive but whatever :P

    std::string negative_buffer;
    std::string positive_buffer;
};

template<>
void
solution<12>::solve(std::ifstream& input)
{
    auto [_, init_state] = fixed_split<2>(readline(input), ": ");
    readline(input);
    std::string line;
    std::unordered_map<std::string, char> rules;
    while (std::getline(input, line))
    {
        auto [rule, result] = fixed_split<2>(line, " => ");
        rules[rule] = result[0];
    }


    state s{init_state};
    for (u64 i = 0; i < 20; ++i)
    {
        for (auto idx = s.start(); idx < s.last() - 4; ++idx)
        {
            auto curr = s.substate(idx);
            if (rules.contains(curr))
                s[idx + 2] = rules[curr];
            else
                s[idx + 2] = '.';
        }
        s.flush();
    }

    i32 sum = 0;
    for (i32 i = s.start(); i < s.last(); ++i)
    {
        sum += s[i] == '#' ? i : 0;
    }
    std::cout << sum << '\n';
}
