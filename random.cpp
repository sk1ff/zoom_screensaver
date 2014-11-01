#include "random.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

void Random::init()
{
    ::srand((unsigned) ::time(0));
}

int Random::from_range(int min, int max)
{
    return (::rand() % (max - min + 1)) + min;
}
