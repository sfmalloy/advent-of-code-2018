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

    option_parser parser(argc, argv);
    i32 day = parser.get_int("d") - 1;
    if (day >= DAYS || day < 0) 
    {
        std::cerr << "Invalid day number\n";
        return -1;
    }

    std::string filename = "";
    if (parser.get_str("f") != STR_NOT_FOUND)
        filename = parser.get_str("f");
    
    using func_type = f32(*)(std::string);
    std::array<func_type, DAYS> day_functions = [&]<size_t... Is>(std::index_sequence<Is...>)
    {
        std::array<func_type, DAYS> functions{};
        ((functions[Is] = &time_solve<Is + 1>), ...);
        return functions;
    }(std::make_index_sequence<DAYS>{});

    f32 runtime = day_functions[day](filename);
    std::cout << std::setprecision(3) << std::fixed <<  "Time: " << runtime << "ms\n";
 
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
