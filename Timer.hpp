#ifndef Tools_Timer_hpp
#define Tools_Timer_hpp

#include <chrono>
#include <iostream>

using namespace std::chrono;

namespace Tools
{

class Timer
{
    private:
        time_point<steady_clock> t0;
        double seconds;

    public:

        // Timer starts upon construction
        inline Timer();

        // Stops the timer and returns the number of seconds
        inline double stop();
};

/* IMPLEMENTATIONS FOLLOW */

inline Timer::Timer()
:t0(steady_clock::now())
,seconds(0.0)
{

}

inline double Timer::stop()
{
    return duration<double>(steady_clock::now() - t0).count();
}

} // namespace

#endif

