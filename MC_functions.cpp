# ifndef MC_FUNCTIONS_H
#include "MC_functions.hpp"
# endif

# ifndef COMMON_HEADERS_H
#include "common_headers.hpp"
# endif

#include <iomanip>

#include <boost/random/uniform_int_distribution.hpp>
#include <boost/format.hpp> // It seems like I might as well just include <boost/kitchen_sink.hpp>

using std::string;
namespace br = boost::random;
namespace bu = boost::uuids;

Params::Params(size_t len, size_t LL, size_t samples, uint64_t eqSteps,
        double bta, string bName, bu::uuid id, br::mt19937_64 engine, 
        br::uniform_real_distribution<double> dist)
{
    L = len;
    N = LL;
    numSamp = samples;
    numEqSteps = eqSteps;
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
            (*sigma)[i][j] = shifted < 0.5 ? -1 : 1;
        }
    }
}

// Dumb debugging
void PrintSigma(int64_t ***sigma, size_t L)
{
    for(size_t i = 0; i < L; i++)
    {
        for(size_t j = 0; j < L; j++)
        {
            printf("%+3ld", (*sigma)[i][j]);
        }
        printf("\n");
    }
}

void Update(Params Pars, int64_t ***s, 
        br::uniform_int_distribution<size_t> dist0L, double *expecValues, 
        int64_t *plus1, int64_t *minus1) 
{
    size_t k = 0;
    size_t l = 0;
    double deltaE = 0.0;

//    char ack;     // Dumb debugging
//    PrintSigma(s, Pars.L);
//    printf("\n");
    // Do updates
    for(size_t u = 0; u < Pars.N; u++)
    {
        k = dist0L(Pars.rng);
        l = dist0L(Pars.rng);
        deltaE = 2.0 * (*s)[k][l] * ( (*s)[plus1[k]][l] + (*s)[minus1[k]][l] + 
                                      (*s)[k][plus1[l]] + (*s)[k][minus1[l]] );
        
        if (Pars.GetRNG01() <= exp(-deltaE*Pars.beta))
        {
            (*s)[k][l] *= -1;               // Flip that spin
            expecValues[0] += deltaE;       // Add to energy accumulator
            expecValues[1] += 2*(*s)[k][l]; // Add to magnetization accumulator
        }
    }
//    PrintSigma(s, Pars.L);
//    scanf("%s",&ack);
}

void GetCurrentMagnetization(int64_t ***sigma, double *expecValues, size_t L)
{
    for(size_t i = 0; i < L; i++)
    {
        for(size_t j = 0; j < L; j++)
        {
            expecValues[1] += (*sigma)[i][j];
        }
    }

    expecValues[1] /= (L*L);
}

void MonteCarlo(Params Pars, int64_t ***sigma)
{
    // Expectation value accumulator
    // Order is: E, M
    double expecValues[2] = {0.0, 0.0};
    size_t sampleCount = 0;

    // Miscellaneous variables and utilities
    br::uniform_int_distribution<size_t> dist0L(0, Pars.L-1); 
    string uid_string = bu::to_string(Pars.uid);

    printf("The UUID is: %s\n", uid_string.c_str());
    string Lcomp = "-L_" + std::to_string(Pars.L);
//    string betaComp = "-B_" + std::to_string(Pars.beta);
    boost::format betaFormatter("%06.3f");
    string betaComp = "-B_" + (betaFormatter % Pars.beta).str();
    string fileName = "output"+ Lcomp + betaComp + "-" + uid_string + ".dat";

    FILE *fP;   // File pointer
    fP = fopen(fileName.c_str(), "w");
    fprintf(fP, "# PIMCID: %s\n", uid_string.c_str());
    fprintf(fP, "#\tE\t\tM\n");
    fclose(fP);

    // Create lookup tables for PBCs. Why compute it every time? 
    int64_t plus1[Pars.L];
    int64_t minus1[Pars.L];
    for(size_t i = 0; i < Pars.L; i++)
    {
        plus1[i] = i+1;
        minus1[i] = i-1;
    }
    plus1[Pars.L-1] = 0;
    minus1[0] = Pars.L-1;
    
// === Begin MC loop here =====================================================
    // Equilibriate
    printf("Equlibriating...\n");
    GetCurrentMagnetization(sigma, expecValues, Pars.L);

    for(uint64_t step = 0; step < Pars.numEqSteps; step++)
    {
        // Perform the updates
        Update(Pars, sigma, dist0L, expecValues, plus1, minus1);
    }

    // Collect data
    printf("Collecting data...\n");
    while(sampleCount < Pars.numSamp)
    {
        // Perform the updates
        Update(Pars, sigma, dist0L, expecValues, plus1, minus1);

        fP = fopen(fileName.c_str(), "a");
        fprintf(fP, "%f\t%f\n", expecValues[0]/Pars.N, expecValues[1]/Pars.N);
        fclose(fP);

        sampleCount++;
        if(sampleCount % 1024 == 0)
        {
            printf("Writing to disk sample %ld / %ld\n", sampleCount, Pars.numSamp);
        }
    }
    printf("The UUID is: %s\n", uid_string.c_str());
}
