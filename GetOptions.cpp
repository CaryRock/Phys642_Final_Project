// I wanted to figure out how to get this to spit out the help text if one runs
// it without any options (e.g., simply as "executable" sans options), but I
// don't have to time to mess with that at the moment.

#ifndef COMMON_HEADERS_H
#include "common_headers.h"
#endif

#ifndef BOOST_PROGRAM_OPTIONS_SET
#include <boost/program_options.hpp>
#endif

using namespace boost;
namespace po = boost::program_options;

using namespace std;

template<class T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    copy(v.begin(), v.end(), ostream_iterator<T>(os, " "));
    return os;
}

int64_t GetOptions(int64_t ac, char **av, size_t *L, double *beta, 
        size_t *numSamp, uint64_t *numEqSteps)
{
    try
    {
        po::options_description desc("Possible options:");
        desc.add_options()
            ("help,h", "Produce this help message and exit.")
            ("side-length,L", po::value<size_t>(L)->default_value(16),
                "Sets the side length of the lattice. Default: 16 sites.")
            ("beta,B", po::value<double>(beta)->default_value(1),
                "Sets the (inverse) temperature at which to run the simulation. Default: 1.")
            ("numSamp,S", po::value<size_t>(numSamp)->default_value(pow(2,17)),
                "Sets the number of desired output samples written to the file. Default: 2^17.")
            ("numEqSteps,E", po::value<uint64_t>(numEqSteps)->default_value(pow(2,15)),
                "Sets the number of steps to skip as equilibriation. Default: 2^15 (1/4 of 2^17).")
        ;

        po::variables_map vm;
        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);
    
        if(vm.count("help"))
        {
            std::cout << "Usage: options_description [options]\n";
            std::cout << desc;
            return 1;
        }
    }

    catch(std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 2;
    }

    catch(...)
    {
        std::cerr << "Exception of unknown type!\n";
    }

    return 0;
}
