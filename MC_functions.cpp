# ifndef MC_FUNCTIONS
#include "MC_functions.hpp"
# endif

# ifndef COMMON_HEADERS
#include "common_headers.hpp"
# endif

#include <boost/random/uniform_int_distribution.hpp>

using std::string;
namespace br = boost::random;
namespace bu = boost::uuids;

Params::Params(size_t len, size_t LL, size_t samples, uint64_t eqSteps, uint64_t obs, 
        double bta, string bName, bu::uuid id, br::mt19937_64 engine, 
        br::uniform_real_distribution<double> dist)
{
    L = len;
    N = LL;
    numSamp = samples;
    numEqSteps = eqSteps;
    obsSkip = obs;
    beta = bta;
    baseName = bName;
    uid = id;
    rng = engine;
    dist01 = dist;
}

double Params::GetRNG01()
{
    return dist01(rng);
}

void Instantiate1DArray(int64_t **array, size_t L)
{
    *array = (int64_t *) malloc(L*sizeof(int64_t));
}

void Instantiate2DArray(int64_t ***sigma, size_t L)
{
    *sigma = (int64_t **) malloc(L*sizeof(int64_t *));
    for(size_t i = 0; i < L; i++)
    {
        (*sigma)[i] = (int64_t *) malloc(L*sizeof(int64_t));
    }
}

void InitializeConfig(Params Pars, int64_t ***sigma, size_t L)
{
    double shifted = 0;
    // Initializes a random spin configuration for matrix sigma
    for(size_t i = 0; i < L; i++)
    {
        for(size_t j = 0; j < L; j++)
        {
            shifted = Pars.GetRNG01();
//            printf("sigma: %ld\n", (*sigma)[i][j]);
            (*sigma)[i][j] = shifted < 0.5 ? -1 : 1;
        }
    }
}

bool ProposeUpdate(int64_t ***sigma, size_t L)
{
    return true;
    return false;
//    (*sigma)[][]...;
}

inline int64_t ExpecMvalue(int64_t ***sigma, size_t i, size_t j)
{
    return (*sigma)[i][j];
}

inline double ExpecEvalue(int64_t ***sigma, int64_t *plus1, int64_t *minus1, 
        size_t i, size_t j)
{
    return 1/2 * (*sigma)[i][j] * ((*sigma)[plus1[i]][j] + 
            (*sigma)[minus1[i]][j] + (*sigma)[i][plus1[j]] + 
            (*sigma)[i][minus1[j]]);
}

void GetProperties(Params Pars, int64_t ***sigma, int64_t *plus1, 
        int64_t *minus1, double *expecValues)
{
    double M = 0;
    double E = 0;
    for(size_t i = 0; i < Pars.L; i++)
    {
        for(size_t j = 0; j < Pars.L; j++)
        {
            M += ExpecMvalue(sigma, i, j);
            E -= ExpecEvalue(sigma, plus1, minus1, i, j);
        }
    }

    expecValues[0] = E/(Pars.N);
    expecValues[1] = M/(Pars.N);
}

void MonteCarlo(Params Pars, int64_t ***sigma)
{
    // Expectation value accumulator
    // Order is: E, M
    double expecValues[2] = {0.0, 0.0};
    size_t sampleCount = 0;
    std::string fileName = "test_output.dat";

    // Miscellaneous variables and utilities
    br::uniform_int_distribution<size_t> dist0L(0, Pars.L-1); // -1 since [a,b], not [a,b)
    size_t k = 0;
    size_t l = 0;
    double deltaE = 0.0;
    std::string uid_string = bu::to_string(Pars.uid);

    FILE *fP;   // File pointer
    fP = fopen(fileName.c_str(), "a");
    fprintf(fP, "# PIMCID: %s\n", uid_string.c_str());
    fprintf(fP, "#\tE\t\tM\n");
    fclose(fP);

    // Create lookup tables for PBCs. Why compute it every time? 
    int64_t plus1[Pars.L] = {0};
    int64_t minus1[Pars.L] = {0};
    
    for(size_t i = 0; i < Pars.L; i++)
    {
        plus1[i] = i+1;
        minus1[i] = i-1;
    }
    plus1[Pars.L] = 0;
    minus1[0] = Pars.L-1;

// Begin MC loop here
    // Equilibriate
    printf("Equlibriating...\n");
    for(uint64_t step = 0; step < Pars.numEqSteps; step++)
    {
        // Get current magnetization
        for(size_t i = 0; i < Pars.L; i++)
        {
            for(size_t j = 0; j < Pars.L; j++)
            {
                expecValues[1] += (*sigma)[i][j];
            }
        }

        // Do updates
        for(size_t u = 0; u < Pars.N; u++)
        {
            k = dist0L(Pars.rng);
            l = dist0L(Pars.rng);

            deltaE = 4*ExpecEvalue(sigma, plus1, minus1, k, l);

            if (Pars.dist01(Pars.rng) <= exp(-deltaE*Pars.beta))
            {
                (*sigma)[k][l] *= -1;
                expecValues[1] += 2*(*sigma)[k][l];
            }
        }
    }

    // Collect data
    printf("Collecting data...\n");
    while(sampleCount < Pars.numSamp)
    {
        // Get current magnetization
        for(size_t i = 0; i < Pars.L; i++)
        {
            for(size_t j = 0; j < Pars.L; j++)
            {
                expecValues[1] += (*sigma)[i][j];
            }
        }
        
        // Do updates
        for(size_t u = 0; u < Pars.N; u++)
        {
            k = dist0L(Pars.rng);
            l = dist0L(Pars.rng);

            deltaE = 4*ExpecEvalue(sigma, plus1, minus1, k, l);
            
            if (Pars.dist01(Pars.rng) <= exp(-deltaE*Pars.beta))
            {
                (*sigma)[k][l] *= -1;
                expecValues[1] += 2*(*sigma)[k][l];
            }
        }
        
        // Any skipping would go here
        //

        // Any MC binning would go here
        //

        GetProperties(Pars, sigma, plus1, minus1, expecValues);

        fP = fopen(fileName.c_str(), "a");
        fprintf(fP, "%f\t%f\n", expecValues[0], expecValues[1]);
        fclose(fP);

        sampleCount++;
        printf("Writing to disk sample %ld / %ld\n", sampleCount, Pars.numSamp);
    }
}
