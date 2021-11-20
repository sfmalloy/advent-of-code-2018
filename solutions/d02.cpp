#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <unordered_map>

#include "solution.hpp"

template<>
void
solution<2>::solve(std::ifstream& input)
{
    std::vector<std::string> ids {
        std::istream_iterator<std::string>(input), 
        std::istream_iterator<std::string>()
    };

    unsigned twos = 0;
    unsigned threes = 0;

    std::unordered_map<char, unsigned> counts;
    for (const auto& id : ids) 
    {
        for (const char c : id) 
            ++counts[c];
        bool found_two = false;
        bool found_three = false;
        for (auto& [chr, count] : counts)
        {
            found_two = found_two || count == 2;
            found_three = found_three || count == 3;
        }

        twos += found_two;
        threes += found_three;
        counts.clear();
    }

    std::cout << twos * threes << '\n';
    std::unordered_map<std::string, unsigned> id_counts;
    for (size_t i = 0; i < ids[0].size(); ++i)
    {
        for (const auto& id : ids)
            id_counts[id.substr(0, i) + id.substr(i + 1, id.length() - i + 1)] += 1;
        for (const auto& [id, count] : id_counts)
        {
            if (count == 2)
            {
                std::cout << id << '\n';
                return;
            }
        }
        id_counts.clear();
    }
}
