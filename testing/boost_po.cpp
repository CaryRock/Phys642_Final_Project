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

using namespace std;

// A helper function to simplify the main part - copied directly from the 
// example file ("options_description.cpp")
template<class T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    copy(v.begin(), v.end(), ostream_iterator<T>(os, " "));
    return os;
}

int main(int ac, char *av[])
{
    try
    {
        int opt;
        int portnum;

        po::options_description desc("Allowed options");
        desc.add_options()
            ("help,h", "Produce this help message and exit.")
            ("optimization,o", po::value<int>(&opt)->default_value(10),
                "Sets the optimization level.")
            ("verbose,v", po::value<int>()->implicit_value(1),
                "Enable verbosity (default = 1)")
            ("listen,l", po::value<int>(&portnum)->implicit_value(1001)
                ->default_value(0,"no"), "Listen on a port.")
            ("include-path,I", po::value< vector<string> >(),
             "Sets the path to look for inclusions.")
            ("input-file,i", po::value< vector<string> >(), "Input file")
            ("compression,c", po::value<int>(), "Sets the compression level")
        ;
        
        po::positional_options_description p;
        p.add("input-file", -1);

        po::variables_map vm;
        po::store(po::parse_command_line(ac, av, desc).
                  options(desc).positional(p).run(), vm);
        po::notify(vm);
        
        if (vm.count("help"))
        {
            cout << "Usage: options_description [options]\n";
            cout << desc;
            return 0;
        }
        
        if(vm.count("include-path"))
        {
            cout << "Include paths are: "
                      << vm["include-path"].as< vector<string> >() << "\n";
        }

        if(vm.count("input-file"))
        {
            cout << "Input files are: "
                      << vm["input-file"].as< vector<string> >() << "\n";
        }

        if (vm.count("verbose"))
        {
            cout << "Verbosity enabled. Level is " 
                      << vm["verbose"].as<int>() << "\n";
        }

        cout << "Optimazation level is: " << opt << "\n";
        cout << "Listen port is: " << portnum << "\n";
                
        if (vm.count("compression"))
        {
            cout << "Compression level was set to "
                    << vm["compression"].as<int>() << ".\n";
        }
        else
        {
            cout << "Compression level was not set.\n";
        }
    }

    catch(std::exception &e)
    {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    
    catch(...)
    {
        cerr << "Exception of unknown type!\n";
    }

    return 0;
}

