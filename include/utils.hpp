#pragma once

#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>
#include <array>
#include <stdexcept>

#include "solution.hpp"

/*****************************************************************************/
// Non-templated functions

std::vector<std::string>
split(std::string_view str, const std::string& delim = " ");

void
strip(std::string& str);

std::string
readline(std::ifstream& input);

/*****************************************************************************/
// Templated functions

template<size_t N>
std::array<std::string, N>
fixed_split(std::string_view str, const std::string& delim = " ")
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
T
convert(const std::string& str)
{
    if (std::is_same<T, i32>())
        return std::stoi(str);
    else if (std::is_same<T, i64>())
        return std::stol(str);
    else if (std::is_same<T, u64>() || std::is_same<T, u32>())
        return std::stoul(str);
    else if (std::is_same<T, f32>())
        return std::stof(str);
    else if (std::is_same<T, f64>())
        return std::stod(str);
    else if (std::is_same<T, f128>())
        return std::stold(str);
    else
        throw std::runtime_error("Invalid type conversion");
}

template<typename T, class ReadIt, class WriteIt>
void
map_type(ReadIt begin, ReadIt end, WriteIt write)
{
    for (auto it = begin; it != end; ++it, ++write)
        *write = convert<T>(*it);
}

template<typename T, size_t N>
std::array<T, N>
type_split(std::string_view str, const std::string& delim = " ")
{
    auto split_arr = fixed_split<N>(str, delim);
    std::array<T, N> new_arr;
    map_type<T>(std::begin(split_arr), std::end(split_arr), std::begin(new_arr));
    return new_arr;
}

template<typename T>
std::vector<T>
type_split(std::string_view str, const std::string& delim = " ")
{
    auto split_vec = split(str, delim);
    std::vector<T> vec(split_vec.size());
    map_type<T>(std::begin(split_vec), std::end(split_vec), std::begin(vec));
    return vec;
}

template<class Iter>
void 
print_collection(Iter begin, Iter end)
{
    std::cout << "[ ";
    for (auto it = begin; it != end; ++it)
        std::cout << *it << (it + 1 == end ? "" : ", ");
    std::cout << " ]\n";
}
