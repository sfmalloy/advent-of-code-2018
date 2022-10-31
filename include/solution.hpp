#pragma once

#include <fstream>
#include <cstdint>

using i32 = std::int32_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using f32 = float;
using f64 = double;
using f128 = long double;

template <unsigned N>
class solution
{
public:
    void solve(std::ifstream& input);
};
