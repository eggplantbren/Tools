#ifndef Tools_RNG_hpp
#define Tools_RNG_hpp

#include <cmath>
#include <cstring>
#include <ctime>
#include "Skilling.hpp"
#include <vector>

namespace Tools
{

/*
* An object of this class represents a random number generator state
*/
class RNG
{
    private:

        // One of John's things
        Rand64_t skilling_rng;

    public:

        // Pass the seed, or alternatively, it will use the unix time
        RNG(int seed = time(0));

        // Set the seed
        void set_seed(int seed);

        // Uniform(0, 1)
        double rand();

        // Normal(0, 1)
        double randn();

        // A heavy-tailed distribution for proposals
        double randh();

        // Cauchy
        double randc();

        // Integer from {0, 1, 2, ..., N-1}
        int rand_int(int N);

        // Laplacian
        double randl();

        // State to blob
        std::vector<char> to_blob() const;

}; // class RNG


/* IMPLEMENTATION FOLLOWS */

inline RNG::RNG(int seed)
{
    set_seed(seed);
}

inline void RNG::set_seed(int seed)
{
    Ran64Init(skilling_rng, seed);
}

inline double RNG::rand()
{
    return RanDouble(skilling_rng);
}

inline double RNG::randn()
{
    return RanGauss(skilling_rng);
}

inline double RNG::randh()
{
    return pow(10.0, 1.0 - std::abs(this->randc()))*this->randn();
}

inline double RNG::randc()
{
    return tan(M_PI*(this->rand() - 0.5));
}

inline int RNG::rand_int(int N)
{
    return static_cast<int>(floor(N*this->rand()));
}

inline double RNG::randl()
{
    double x = -log(this->rand());
    if(this->rand() <= 0.5)
        x *= -1.0;
    return x;
}

inline std::vector<char> RNG::to_blob() const
{
    int chars_per_element = sizeof(unsigned long)/sizeof(char);
    int chars_needed = 4*chars_per_element;
    std::vector<char> result(chars_needed);
    int j = 0;
    for(int i=0; i<4; ++i)
    {
        std::memcpy(&result[j], &(skilling_rng[i]), sizeof(unsigned long));
        j += chars_per_element;
    }
    return result;
}

} // namespace

#endif

