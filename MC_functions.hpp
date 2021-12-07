#define MC_FUNCTIONS_H

#ifndef COMMON_HEADERS_H
#include "common_headers.hpp"
#endif

namespace br = boost::random;

struct Params
{
    size_t L;
//    size_t Lx;
//    size_t Ly;
    size_t N;
    size_t numSamp;
    uint64_t numEqSteps;
//    double beta;
    double temp;
    std::string baseName;
    boost::uuids::uuid uid;
    boost::random::mt19937_64 rng;
    boost::random::uniform_real_distribution<double> dist01;

    Params(size_t, size_t, size_t, uint64_t, double, std::string, 
            boost::uuids::uuid, boost::random::mt19937_64, 
            boost::random::uniform_real_distribution<double>);
    ~Params(){};
    double GetRNG01();
};

// I know the names aren't necessary, but they're convenient bookkeeping
double GetProperties(int64_t *sigma, int64_t *plus1, int64_t *minus1, size_t L);
double Update(Params Pars, int64_t *sigma, 
        br::uniform_int_distribution<size_t> *dist0L, int64_t *plus1, int64_t *minus1);
double GetCurrentMagnetization(int64_t *sigma, size_t L);
void MonteCarlo(Params Pars);
