# Phys642_Final_Project
Final project for Prof. Adrian Del Maestro's Physics 642 (Phase Transitions and Critical Phenomena) class at the University of Tennessee, Knoxville.

# Compilation
## Libraries
This code requires boost's random\_device.hpp, mersenne\_twister.hpp, and uniform\_real\_distribution.hpp from boost/random.

## Compiler commands
To compile the code itself, simply invoke `g++ -lboost_random IsingMC_FinalProject.cpp` and set the name of the binary that's output to whatever is desired. Don't forget to `chmod +x $executableName`. Alternatively, simply invoke `make project` to do the same.
