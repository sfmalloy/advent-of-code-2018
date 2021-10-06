#include "utils.hpp"

#include <iostream>
#include <string>
#include <vector>

std::vector<std::string>
split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> split_str;

    size_t idx = 0;
    while (idx != std::string::npos && idx < str.length() - 1)
    {
        size_t next = str.find(delim, idx + 1);
        if (next == std::string::npos)
            next = str.length();
        split_str.push_back(str.substr(idx, next - idx));
        idx = next + delim.size();
        std::cout << idx << '\n';
    }

    return split_str;
}

void
strip(std::string& str)
{
    size_t idx = str.length() - 1;
    while (str[idx] == '\n' || str[idx] == '\r')
        --idx;
    str = str.substr(0, idx + 1);
}
