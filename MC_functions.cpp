# ifndef MC_FUNCTIONS
#include "MC_functions.hpp"
# endif

# ifndef COMMON_HEADERS
#include "common_headers.hpp"
# endif

using std::string;

Params::Params(size_t len, size_t LL, size_t samples, uint64_t eqSteps, uint64_t obs, 
        double bta, string bName, boost::random::mt19937_64 engine, 
        boost::random::uniform_real_distribution<double> dist)
{
    L = len;
    N = LL;
    numSamp = samples;
    numEqSteps = eqSteps;
    obsSkip = obs;
    beta = bta;
    baseName = bName;

    rng = engine;
    dist01 = dist;
}

double Params::GetRNG01()
{
    return dist01(rng);
}

void Instantiate1DArray(int64_t *array, size_t L)
{
    array = (int64_t *) malloc(L*sizeof(int64_t));
}

void Instantiate2DArray(int64_t **sigma, size_t L)
{
    sigma = (int64_t**) malloc(L*sizeof(int64_t*));
    for(size_t i = 0; i < L; i++)
    {
        sigma[i] = (int64_t*) malloc(L*sizeof(int64_t));
    }
}

void InitializeConfig(Params Pars, int64_t **sigma, size_t L)
{
    double shifted = 0;
    // Initializes a random spin configuration for matrix sigma
    for(size_t i = 0; i < L; i++)
    {
        for(size_t j = 0; j < L; j++)
        {
            shifted = Pars.GetRNG01();
            sigma[i][j] = shifted < 0.5 ? -1 : 1;
        }
    }
}

bool ProposeUpdate(int64_t **sigma, size_t L)
{
    return true;
    return false;
}

void MonteCarlo(Params Pars)
{
    // Lookup table for PBCs. Sure, I could have done this for an unrolled loop,
    // but this isn't the time for 
    // sigma[i]*(sigma[plus1[i] + L*j] ) + sigma(sigma[minus1[i] + L*j] + ...)
    int64_t plus1[Pars.L] = {0};
    int64_t minus1[Pars.L] = {0};

    for(size_t i = 0; i < Pars.L; i++)
    {
        plus1[i] = i+1;
        minus1[i] = i-1;
    }
    plus1[Pars.L] = 0;
    minus1[0] = Pars.L-1;
}
