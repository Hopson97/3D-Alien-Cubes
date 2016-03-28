	#ifndef RANDOM_H_INCLUDED
	#define RANDOM_H_INCLUDED

	#include <ctime>
	#include <cstdlib>

	namespace random
	{
        const int
        num ( const int low, const int high);

        const float
        numF ( const float a, const float b);

        const float
        numF ( const float a, const float b, const int seed);
	}

	#endif // RANDOM_H_INCLUDED
