// #include <cstdlib>
// #include <cstdio>

#include <boost/program_options.hpp>

using namespace boost;
namespace po = boost::program_options;

#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#define DONE_H
#include "boost_po1.hpp"
#include "boost_po1.cpp"

using namespace std;

int main(int ac, char **av)
{
    int opt;
    int portnum;
    uint64_t result = 1;

    result = GetOptions(ac, av, &opt, &portnum);
    if(result != 0)
    {
        cout << "Poop :(\n";
        return 1;
    }

    else
    {
        cout << "Success! \n";
    }
    
    cout << "In main(), opt is: " << opt << ".\n";
    cout << "In main(), Listen port is: " << portnum << ".\n";

    return 0;
}

