#include "utils.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <array>

std::vector<std::string>
split(std::string_view str, const std::string& delim)
{
    std::vector<std::string> split_str;

    size_t idx = 0;
    while (idx != std::string::npos && idx < str.length())
    {
        size_t next = str.find(delim, idx);
        if (next == std::string_view::npos)
            next = str.length();
        split_str.push_back(std::string(str.substr(idx, next - idx)));
        idx = next + delim.size();
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

std::string
readline(std::ifstream& input)
{
    std::string line;
    std::getline(input, line);
    return line;
}
