#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <array>
#include <stdexcept>

/*****************************************************************************/
// Non-templated functions

std::vector<std::string>
split(std::string_view str, const std::string& delim);

void
strip(std::string& str);

/*****************************************************************************/
// Templated functions

template <size_t N>
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

template <typename T, size_t N>
std::array<T, N>
map_type(std::array<std::string, N> arr)
{
    std::array<T, N> new_arr;

    for (size_t i = 0; i < N; ++i)
    {
        if (std::is_same<T, int>())
            new_arr[i] = std::stoi(arr[i]);
        else if (std::is_same<T, long>())
            new_arr[i] = std::stol(arr[i]);
        else if (std::is_same<T, unsigned long>())
            new_arr[i] = std::stoul(arr[i]);
        else if (std::is_same<T, unsigned long long>())
            new_arr[i] = std::stoull(arr[i]);
        else if (std::is_same<T, float>())
            new_arr[i] = std::stof(arr[i]);
        else if (std::is_same<T, double>())
            new_arr[i] = std::stod(arr[i]);
        else if (std::is_same<T, long double>())
            new_arr[i] = std::stold(arr[i]);
        else
            throw std::runtime_error("Invalid type conversion");
    }

    return new_arr;
}

template <typename T, size_t N>
std::array<T, N>
type_split(std::string_view str, const std::string& delim)
{
    return map_type<T>(fixed_split<N>(str, delim));
}

template <typename T>
void
print_vector(const std::vector<T>& v)
{
    for (size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << '\n';
}
