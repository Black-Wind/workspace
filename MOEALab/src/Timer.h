#pragma once

#include<chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

class Timer
{
public:
    Timer() : m_begin(high_resolution_clock::now()),uncorrelated_time(0){}
    void reset()
    {
        m_begin = high_resolution_clock::now();
        uncorrelated_time = high_resolution_clock::duration(0);
    }

    //
    void uncorrelated_begin(){m_uncorrelated_begin = high_resolution_clock::now();}
    void uncorrelated_end(){uncorrelated_time += (high_resolution_clock::now() - m_uncorrelated_begin);}

    //default(millisecond)
    template<typename Duration=milliseconds>
    int64_t elapsed() const
    {
        return duration_cast<Duration>((high_resolution_clock::now() - m_begin) - uncorrelated_time).count();
    }

    int64_t elapsed_micro() const
    {
        return elapsed<microseconds>();
    }

    int64_t elapsed_nano() const
    {
        return elapsed<nanoseconds>();
    }

    int64_t elapsed_seconds() const
    {
        return elapsed<seconds>();
    }

    int64_t elapsed_minutes() const
    {
        return elapsed<minutes>();
    }

    int64_t elapsed_hours() const
    {
        return elapsed<hours>();
    }

    time_point<high_resolution_clock> m_begin;
    time_point<high_resolution_clock> m_uncorrelated_begin;
    high_resolution_clock::duration uncorrelated_time;
};
