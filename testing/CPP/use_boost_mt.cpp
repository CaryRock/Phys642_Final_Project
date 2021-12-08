#include <cstdlib>
#include <cstdio>

//#include <boost/random.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>

//Test::Test(boost::random::mt19937_64, boost::random::uniform_real_distribution<>);
//Test::~Test();
//Test::double GetRNG01();

struct Test
{
    boost::random::mt19937_64 rng;
    boost::random::uniform_real_distribution<double> dist01;

    Test(boost::random::mt19937_64 engine, boost::random::uniform_real_distribution<double> dist) : rng(engine), dist01(dist) {};
    ~Test() {};

    double GetRNG01()
    {
        return dist01(rng);
    }
};

int main()
{
    boost::random::random_device rd;
    boost::random::mt19937_64 engine(rd);
    boost::random::uniform_real_distribution<double> dist(0,1);

    Test testStruct(engine, dist);
    printf("Result: %f\n", testStruct.GetRNG01());

    return EXIT_SUCCESS;
}

