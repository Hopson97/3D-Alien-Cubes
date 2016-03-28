#include "rand.h"

#include <cassert>

namespace random
{

const int
num( const int low, const int high)	//Call this method f
{
    return rand() % (high - low + 1) + low;
}

const float
numF( const float min, const float max)
{
    assert(max > min);
    float random = ((float) rand()) / (float) RAND_MAX;

    float range = max - min;
    return (random*range) + min;
}

const float
numF( const float min, const float max, const int seed)
{
    assert(max > min);
    float random = ((float) seed) / (float) RAND_MAX;

    float range = max - min;
    return (random*range) + min;
}

} //Namespace random


