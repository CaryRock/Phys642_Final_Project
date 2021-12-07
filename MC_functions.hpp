#define MC_FUNCTIONS_H

#ifndef COMMON_HEADERS_H
#include "common_headers.hpp"
#endif

namespace br = boost::random;
namespace bu = boost::uuids;

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
    bu::uuid uid;
    br::mt19937_64 rng;
    br::uniform_real_distribution<double> dist01;

    Params(size_t, size_t, size_t, uint64_t, double, std::string, 
            bu::uuid, br::mt19937_64, br::uniform_real_distribution<double>);
    ~Params(){};
    double GetRNG01();
};

// I know the names aren't necessary, but they're convenient bookkeeping
// GetOptions.cpp
template<class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v);
int64_t GetOptions(int64_t ac, char **av, size_t *L, double *T, 
        size_t *numSamp, uint64_t *numEqSteps);

// MC_functions.cpp
double GetProperties(int64_t *sigma, int64_t *plus1, int64_t *minus1, size_t L);
double Update(Params Pars, int64_t *sigma, 
        br::uniform_int_distribution<size_t> *dist0L, int64_t *plus1, int64_t *minus1);
double GetCurrentMagnetization(int64_t *sigma, size_t L);
void MonteCarlo(Params Pars);
