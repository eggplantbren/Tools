#ifndef Tools_Misc_hpp
#define Tools_Misc_hpp

#include <algorithm>
#include <boost/math/special_functions/erf.hpp>
#include <cassert>
#include <cmath>
#include <vector>

namespace Tools
{

// Minus infinity
static constexpr double minus_infinity
                            = -std::numeric_limits<double>::infinity();

// Logsumexp etc
double logsumexp(const std::vector<double>& logv);
double logdiffexp(double b, double a);

// Modulo and related things
int mod(int y, int x);
void wrap(double& x, double min=0.0, double max=1.0);

// Inverse CDF for a standard normal distribution
double qnorm(double p);

/* IMPLEMENTATIONS FOLLOW */

inline double logsumexp(const std::vector<double>& logv)
{
    double max = *max_element(logv.begin(), logv.end());
    double answer = 0.0;
    for(size_t i=0; i<logv.size(); ++i)
        answer += exp(logv[i] - max);
    answer = max + log(answer);
    return answer;
}

inline double logdiffexp(double b, double a)
{
    assert(b >= a);
    return b + log(1 - exp(a-b));
}

inline double mod(double y, double x)
{
    assert(x > 0.0);
    return (y/x - floor(y/x))*x;
}

inline int mod(int y, int x)
{
    assert(x > 0);
    if(y >= 0)
        return y - (y/x)*x;
    else
        return (x-1) - Tools::mod(-y-1, x);
}

inline void wrap(double& x, double min, double max)
{
    x = Tools::mod(x - min, max - min) + min;
}

inline double qnorm(double p)
{
    return sqrt(2.0)*boost::math::erf_inv(2.0*p - 1.0);
}


} // namespace

#endif

