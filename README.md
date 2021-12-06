# Phys642_Final_Project
Final project for Prof. Adrian Del Maestro's Physics 642 (Phase Transitions and Critical Phenomena) class at the University of Tennessee, Knoxville.

# Compilation
## Libraries
This code requires boost's random\_device.hpp, mersenne\_twister.hpp, and uniform\_real\_distribution.hpp from boost/random.

## Compiler commands
To compile the code itself, simply invoke `g++ -I /usr/include/boost -lboost_random -lboost_program_options IsingMC_FinalProject.cpp` for GCC version 11.2 and set the name of the binary that's output to whatever is desired. Alternatively, simply invoke `make project` to do the same. If compiling manually, make sure that the option `-I` points to wherever the boost libraries are installed (if they aren't installaed in `/usr/include/boost` and if gcc does not automatically search there already).
