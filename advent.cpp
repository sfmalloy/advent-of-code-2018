#include <iostream>
#include <stdexcept>
#include <functional>

#include "option_parser.hpp"
#include "timer.hpp"
#include "solution.hpp"

template <int N>
double
time_solve();

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
        std::cout << parser.get_str("d") << '\n';

        timer t;
        for (unsigned i = 0; i < 10000000; ++i)
        {
            int x = 1;
            int y = 2;
            int z = x + y;
        }
        t.stop();
        
        std::cout << t.get_duration_ms() << '\n';
        day_functions[parser.get_int("d") - 1]();
    } 
    catch (const std::exception& e) 
    {
        std::cout << e.what() << '\n';
    }

    return 0;
}

template <int N>
double
time_solve()
{
    timer t;
    solution<N> curr_day;
    curr_day.solve();
    t.stop();
    
    return t.get_duration_ms();
}