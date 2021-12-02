#define MC_FUNCTIONS

#ifndef COMMON_HEADERS
#include "common_headers.hpp"
#endif

struct Params
{
    size_t L;
    size_t N;
    size_t numSamp;
    uint64_t numEqSteps;
    uint64_t obsSkip;
    double beta;
    std::string baseName;
    boost::uuids::uuid uid;
    boost::random::mt19937_64 rng;
    boost::random::uniform_real_distribution<double> dist01;

    Params(size_t, size_t, size_t, uint64_t, uint64_t, double, std::string, 
            boost::uuids::uuid, boost::random::mt19937_64, 
            boost::random::uniform_real_distribution<double>);
    ~Params(){};
    double GetRNG01();
};
