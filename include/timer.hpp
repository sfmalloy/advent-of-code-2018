#pragma once

#include <chrono>

class timer
{
public:
    // Default ctor that also starts the timer
    timer();

    // Set the start time
    void
    start();

    // Set the stop time
    void
    stop();

    // Return the duration from start to stop in milliseconds
    float
    get_duration_ms();

private:
    using clock = std::chrono::high_resolution_clock;
    using time_point = std::chrono::time_point<clock>;

    time_point m_start;
    time_point m_stop;
};
