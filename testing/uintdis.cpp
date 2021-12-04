#include <cstdlib>
#include <cstdio>

#include <boost/random/random_device.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

int main()
{
    size_t L = 100;

    boost::random::random_device rd;
    boost::random::mt19937_64 rng(rd);
    boost::random::uniform_int_distribution<int64_t> dist0L(0,L);

    printf("Maximum value of distribution: %ld\n\n", dist0L.max());
    for(size_t i = 0; i < 10; i++)
    {
        printf("%ld\n",dist0L(rng));
    }

    return EXIT_SUCCESS;
}

