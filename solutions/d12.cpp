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
      , m_state_num(0)
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
            negative_buffer[negative_buffer.size() + idx] = c;
    }

    bool
    stabalized()
    {
        auto before = positive.substr(positive.find('#'), positive.rfind('#') - positive.find('#'));
        auto after = positive_buffer.substr(positive_buffer.find('#'), positive_buffer.rfind('#') - positive_buffer.find('#'));
        return before == after;
    }

    void
    flush()
    {
        negative = negative_buffer;
        positive = positive_buffer;
        ++m_state_num;
    }

    i64
    state_num()
    {
        return m_state_num;
    }

    void
    set_state_num(i64 new_state)
    {
        m_state_num = new_state;
    }

private:
    std::string negative;
    std::string positive; // also includes 0 which is technically not positive but whatever :P

    std::string negative_buffer;
    std::string positive_buffer;

    i64 m_state_num;
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
    while (s.state_num() < 20)
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

    s.set_state_num(s.state_num() - 1);
    do
    {
        s.flush();
        for (auto idx = s.start(); idx < s.last() - 4; ++idx)
        {
            auto curr = s.substate(idx);
            if (rules.contains(curr))
                s[idx + 2] = rules[curr];
            else
                s[idx + 2] = '.';
        }
    } while (!s.stabalized());

    constexpr const i64 fifty_billion = 50000000000;
    i64 big_sum = 0;
    for (i32 i = s.start(); i < s.last(); ++i)
    {
        big_sum += (s[i] == '#' ? ((i - s.state_num()) + fifty_billion) : 0);
    }
    std::cout << big_sum << '\n';
}
