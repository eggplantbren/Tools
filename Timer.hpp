#ifndef Tools_Timer_hpp
#define Tools_Timer_hpp

#include <chrono> 

using namespace std::chrono; 
  
namespace Tools
{

class Timer
{
    private:
        time_point<steady_clock> t0;

    public:
        Timer();
        void reset();
        double elapsed_seconds();
};

/* IMPLEMENTATIONS FOLLOW */

Timer::Timer()
:t0(steady_clock::now())
{

}

void Timer::reset()
{
    t0 = steady_clock::now();
}

double Timer::elapsed_seconds()
{
    return duration<double>(steady_clock::now() - t0).count();
}

} // namespace

#endif

