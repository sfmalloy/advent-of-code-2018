#include <iostream>
#include <stdexcept>
#include <utility>
#include <iomanip>
#include <array>

#include "option_parser.hpp"
#include "timer.hpp"
#include "solution.hpp"

template <unsigned N>
double
time_solve();

std::string
file_day_num(unsigned num);

int 
main(int argc, char* argv[]) 
{
    try 
    {
        // Thanks willkill07 for this epic snippet
        // Creates an array of functions to call on for each day without having to type each one manually
        using func_type = double(*)();
        constexpr const size_t DAYS = 25;
        
        auto day_functions = [&] <size_t ... Is> (std::index_sequence<Is...>) -> std::array<func_type, DAYS> {
            std::array<func_type, DAYS> functions;
            ((functions[Is] = &time_solve<Is + 1>), ...);
            return functions;
        }(std::make_index_sequence<DAYS>{});

        option_parser parser(argc, argv);
        double runtime = day_functions[parser.get_int("d") - 1]();
        std::cout << std::setprecision(3) << "Time: " << runtime << "ms\n";
    }
    catch (const std::exception& e) 
    {
        std::cout << e.what() << '\n';
        return -1;
    }

    return 0;
}

template <unsigned N>
double
time_solve()
{
    std::ifstream input(file_day_num(N));
    solution<N> curr_day;

    timer t;
    curr_day.solve(input);
    t.stop();
    
    return t.get_duration_ms();
}

std::string
file_day_num(unsigned num)
{
    std::string name = "inputs/d";
    if (num < 10)
        name += "0" + std::to_string(num);
    else
        name += std::to_string(num);
    return name + ".in";
}
