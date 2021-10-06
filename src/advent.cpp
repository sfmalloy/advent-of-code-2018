#include <iostream>
#include <stdexcept>
#include <functional>
#include <iomanip>

#include "option_parser.hpp"
#include "timer.hpp"
#include "solution.hpp"

template <unsigned N>
double
time_solve();

std::string
file_day_num(unsigned num);

std::function<double()>
day_functions[25]
{
    time_solve<1>,
    time_solve<2>,
    time_solve<3>,
    time_solve<4>,
    time_solve<5>,
    time_solve<6>,
    time_solve<7>,
    time_solve<8>,
    time_solve<9>,
    time_solve<10>,
    time_solve<11>,
    time_solve<12>,
    time_solve<13>,
    time_solve<14>,
    time_solve<15>,
    time_solve<16>,
    time_solve<17>,
    time_solve<18>,
    time_solve<19>,
    time_solve<20>,
    time_solve<21>,
    time_solve<22>,
    time_solve<23>,
    time_solve<24>,
    time_solve<25>
};

int 
main(int argc, char* argv[]) 
{
    try 
    {
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
