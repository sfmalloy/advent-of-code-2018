#include <ios>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <iomanip>
#include <array>

#include "option_parser.hpp"
#include "timer.hpp"
#include "solution.hpp"

template <u32 N>
float
time_solve(std::string filename);

std::string
file_day_num(u32 num);

int 
main(int argc, char* argv[]) 
{
    constexpr const size_t DAYS = 25;
    using func_type = f32(*)(std::string);
    std::array<func_type, DAYS> day_functions = [&]<size_t... Is>(std::index_sequence<Is...>)
    {
        std::array<func_type, DAYS> functions{};
        ((functions[Is] = &time_solve<Is + 1>), ...);
        return functions;
    }(std::make_index_sequence<DAYS>{});

    option_parser parser(argc, argv);
    auto all_days = parser.has("a");
    if (all_days)
    {
        f32 total = 0;
        // disable printing output for timing all days
        std::cout.setstate(std::ios_base::failbit);
        std::array<f32, DAYS> times;
        for (i32 d = 0; d < DAYS; ++d)
        {
            times[d] = day_functions[d]("");
            total += (times[d] < 1 ? 0 : times[d]);
        }

        std::cout.clear();
        std::cout << " Day " << " | " << "    Time " << '\n';
        std::cout << "------+-------------" << '\n';
        for (i32 d = 0; d < DAYS; ++d)
        {
            std::cout << std::fixed << std::setw(5) << d + 1 << " | " << std::setprecision(3) << std::setw(8) << std::right << (times[d] < 0.001f ? 0 : times[d]) << " ms\n";
        }
        std::cout << "------+-------------" << '\n';
        std::cout << "Total" << " | " << total << " ms\n";
    }
    else
    {
        i32 day = parser.get_int("d") - 1;
        if (day >= DAYS || day < 0) 
        {
            std::cerr << "Invalid day number\n";
            return -1;
        }

        std::string filename = "";
        if (parser.get_str("f") != STR_NOT_FOUND)
            filename = parser.get_str("f");

        f32 runtime = day_functions[day](filename);
        std::cout << std::setprecision(3) << std::fixed <<  "Time: " << runtime << "ms\n";
    }
 
    return 0;
}

template <u32 D>
f32
time_solve(std::string filename)
{
    if (filename == "")
        filename = file_day_num(D);
    std::ifstream input(filename);
    solution<D> curr_day;

    timer t;
    curr_day.solve(input);
    t.stop();
    
    return t.get_duration_ms();
}

std::string
file_day_num(u32 num)
{
    std::string name = "inputs/d";
    if (num < 10)
        name += "0" + std::to_string(num);
    else
        name += std::to_string(num);
    return name + ".in";
}
