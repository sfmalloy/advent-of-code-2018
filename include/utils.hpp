#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <array>
#include <stdexcept>

#include "solution.hpp"

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

template<typename T, size_t N>
std::array<T, N>
map_type(std::array<std::string, N> arr)
{
    std::array<T, N> new_arr;

    for (size_t i = 0; i < N; ++i)
    {
        if (std::is_same<T, i32>())
            new_arr[i] = std::stoi(arr[i]);
        else if (std::is_same<T, i64>())
            new_arr[i] = std::stol(arr[i]);
        else if (std::is_same<T, u64>() || std::is_same<T, u32>())
            new_arr[i] = std::stoul(arr[i]);
        else if (std::is_same<T, f32>())
            new_arr[i] = std::stof(arr[i]);
        else if (std::is_same<T, f64>())
            new_arr[i] = std::stod(arr[i]);
        else if (std::is_same<T, f128>())
            new_arr[i] = std::stold(arr[i]);
        else
            throw std::runtime_error("Invalid type conversion");
    }

    return new_arr;
}

template<typename T, size_t N>
std::array<T, N>
type_split(std::string_view str, const std::string& delim)
{
    return map_type<T>(fixed_split<N>(str, delim));
}

template<typename T>
void
print_vector(const std::vector<T>& v)
{
    std::cout << "[ ";
    for (size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << (i < v.size() - 1 ? ", " : "");
    std::cout << " ]";
}

template <typename T, size_t N>
void
print_array(const std::array<T, N>& arr) 
{
    for (const auto& elem : arr)
        std::cout << elem << '\n';
}
