#include <cstdlib>
#include <cstdio>
#include <random>
#include <sstream>
#include <string>
#include <iostream>

#include <boost/random/random_device.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

using boost::uuids::uuid;

struct Test
{
    uuid id;
    boost::random::mt19937_64 rng;
    boost::random::uniform_real_distribution<double> dist01;

    Test(boost::random::mt19937_64 engine, boost::random::uniform_real_distribution<double> dist) : id(boost::uuids::random_generator()()), rng(engine), dist01(dist) {};
    ~Test(){};

    double Shift(double delta=0.75)
    {
        return dist01(rng);
    }
};

int main()
{
    boost::random::random_device rd;
    boost::random::mt19937_64 engine(rd);
    boost::random::uniform_real_distribution<double> dist(0,1);
    std::string id;

    Test testStruct(engine, dist);
    id = boost::uuids::to_string(testStruct.id);
    
    // Converting from UUID -> stringstream -> printf'able output is rough. Use std::cout instead
    // printf("UUID: %s",id.c_str());
    std::cout << "UUID: " << id << "\n";
    for(int i = 0; i < 16; i++)
    {
        printf("%f\n", testStruct.Shift());
    }

    return 0;
}
