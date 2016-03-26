#ifndef RANDOMENGINE_H
#define RANDOMENGINE_H
#include "boost/random/mersenne_twister.hpp"
#include "boost/random/uniform_int_distribution.hpp"
#include <iostream>
#include <ctime>

class Randomengine
{
public:
    //Randomengine();
    Randomengine(int seed = 0);
    int getNumber();
private:
    int seed;
    boost::random::mt11213b randomgen;
};

#endif // RANDOMENGINE_H
