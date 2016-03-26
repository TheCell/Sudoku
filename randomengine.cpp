#include "randomengine.h"

/*Randomengine::Randomengine()
{
    time_t rawtime = time(0);
    seed = rawtime;
    Randomengine::seed = seed;

    boost::random::mt11213b Randomengine::randomgen(seed);
    boost::random::uniform_int_distribution<> dist(0,9);
}*/

Randomengine::Randomengine(int seed)
{
    if (seed == 0)
    {
        time_t rawtime = time(0);
        seed = rawtime;
        Randomengine::seed = seed;
    }

    Randomengine::randomgen = boost::random::mt11213b (seed);
    boost::random::uniform_int_distribution<> dist(0,9);
}

int Randomengine::getNumber()
{
    int randomNumber = 0;
    boost::random::uniform_int_distribution<> dist(0,9);
    randomNumber = dist(Randomengine::randomgen);
    return randomNumber;
}
