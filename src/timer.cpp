#include <chrono>

#include "timer.hpp"

timer::timer()
    : m_start(),
      m_stop()
{ 
    start();
}

void
timer::start()
{
    m_start = clock::now();
}

void
timer::stop()
{
    m_stop = clock::now();
}

double
timer::get_duration_ms()
{
    std::chrono::duration<double, std::milli> diff = m_stop - m_start;
    return diff.count();
}
