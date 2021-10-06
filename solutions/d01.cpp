#include <iostream>

#include "solution.hpp"
#include "utils.hpp"

template <>
void
solution<1>::solve()
{
    std::string need_to_split = "this, is, a, test";
    auto split_str = split(need_to_split, " ");
    for (const auto& s : split_str) {
        std::cout << s << '\n';
    }
}