/*
 *  Submitted as the final project for Dr. Adrian Del Maestro's PHYS 642
 *  Statistical Mechanics (Phase Transitions and Critical Phenomena) class, 
 *  Fall 2021 semester at University of Tennessee, Knoxville.
 *
 *  I did it in C++ because I figured I can get good practice in this way. I
 *  also didn't want to use <iostream> because, other than operator overloading,
 *  it's pretty familiar (not that it really should make a huge difference in
 *  this program one way or the other) - at least, the std::cin/cout part is 
 *  familiar, which is all that I'd really use.
 */

#include <boost/program_options.hpp>
#define BOOST_PROGRAM_OPTIONS_SET

#include "common_headers.hpp"
#include "MC_functions.hpp"
#include "MC_functions.cpp"
#include "GetOptions.cpp"

using std::string;

namespace br = boost::random;
namespace bu = boost::uuids;
namespace po = boost::program_options;

int main(int ac, char **av)
{
    // TODO: GET COMMAND-LINE OPTIONS; SYSTEM SIZE, TEMPERATURE, ETC.
    // Command-line parameters
    size_t L            = 16;
//    double temp         = 1/3;
    double beta         = 1;
    size_t numSamp      = pow(2, 17);   // 2^17 > 10^5
    uint64_t numEqSteps = pow(2, 15);

    uint64_t result = GetOptions(ac, av, &L, &beta, &numSamp, &numEqSteps);

    if(result == 1) {return 0; }

    else if(result != 0 && result != 1)
    {
        printf("Please enter valid options and try again.\n");
        return 2;
    }


    // The rest of the parameters
    size_t N            = L*L;
//    double J            = 1;
//    double kB           = 1;
    bu::uuid id = bu::random_generator()();
    string string_uuid = bu::to_string(id);
    string baseName = string_uuid + ".dat";

    // Accumulators, etc., for desired quantities
    //
    
    br::random_device rd;
    br::mt19937_64 rng(rd);
    br::uniform_real_distribution<double> dist01(0,1);
    Params Pars(L, N, numSamp, numEqSteps, beta, baseName, id, rng, dist01);
    
    int64_t **sigma;    // This one definitely needs to be signed
    Instantiate2DArray(&sigma, L);   // Allocate sigma array
    InitializeConfig(Pars, &sigma, L);

    MonteCarlo(Pars, &sigma);
    
    // Simulation's done, release all that allocated memory just to be extra sure
    // Allocated memory: sigma, 
    for(size_t i = 0; i < L; i++)
    {
        free(sigma[i]);
    }
    free(sigma);

    return 0;
}
