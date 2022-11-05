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
    { }

    char&
    operator[](i64 idx)
    {
        if (idx >= 0)
            return positive[idx];
        else
            return negative[negative.size() + idx];
    }

    std::string
    substate(i64 start)
    {
        if (start >= 0)
            return positive.substr(start, 5);
        else if (start < -4)
            return negative.substr(negative.size() + start) + positive.substr(0, 5 + start);
        return negative.substr(negative.size() + start);
    }

    std::string
    get()
    {
        return negative + positive;
    }

private:
    std::string negative;
    std::string positive; // also includes 0 which is technically not positive but whatever :P
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
}
