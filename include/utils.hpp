#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <array>

/*****************************************************************************/
// Non-templated functions

std::vector<std::string>
split(std::string_view str, const std::string& delim);

void
strip(std::string& str);

/*****************************************************************************/
// Templated functions

template<size_t N>
std::array<std::string, N>
fixed_split(std::string_view str, const std::string& delim)
{
    std::array<std::string, N> split_str;

    size_t idx = 0;
    for (size_t i = 0; i < N; ++i)
    {
        size_t next = str.find(delim, idx + 1);
        if (next == std::string_view::npos)
            next = str.length();
        split_str[i] = str.substr(idx, next - idx);
        idx = next + delim.size();
    }

    return split_str;
}

template<typename T>
void
print_vector(const std::vector<T>& v)
{
    for (size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << '\n';
}
