# Phys642_Final_Project
Final project for Prof. Adrian Del Maestro's Physics 642 (Phase Transitions and Critical Phenomena) class at the University of Tennessee, Knoxville.

# Compilation
## Libraries
This code requires boost's random\_device.hpp, mersenne\_twister.hpp, and uniform\_real\_distribution.hpp from boost/random.

## Compiler commands
To compile the code manually, invoke `g++ -I. -lboost_random -lboost_program_options IsingMC_FinalProject.cpp MC_functions.cpp GetOptions.cpp --std=c++17` for GCC and set the name of the binary that's output to whatever is desired. For Clang/LLVM, change `g++` to `clang++`.

Alternatively, simply invoke `make 2dIsing` to do the same using GCC, `make 2dIsingClang` for Clang. If compiling manually, make sure that the option `-I` points to wherever the boost libraries are installed (if they aren't installaed in `/usr/include/boost` and if gcc does not automatically search there already).

# Running the program
To see a list of commands available, run the program with the `--help` options. In short, the temperature, the side length (the program assumes a square lattice), the desired number of equlibriation steps, and the desired number of samples to write out are all options that can be used. Any options not specified will use their default values (listed in the `--help` description). 

Since the program itself only performs a simulation on a single configuration of input values, it is highly recommended to use GNU Parallel for the launch options. On my desktop (12-Core/24-Thread Ryzen 9 3900X, 64 GB RAM, NVME SSD), the command `parallel 2dIsing -T {} ::: $(seq 0.5 0.05 3.45)` takes around 5 seconds to simulate 60 configurations and write them all to disk. Another (James Christie) reported that a single simulation on their 2015 Mac Pro (Intel CPU - x86-64) took ~10 seconds. 

Only the most minimal error checking was included, so while the program is definitely functional, input that is not exactly what the program is looking for (e.g., integer lattice sides, etc.) will result in undefined behavior.

# Acknowledgements and Thanks
1.) I would like to thank Dr. Adrian del Maestro for his help debugging the pointers. It turns out I wasn't passing the RNG by reference but by value, meaning that every call was getting a copy of the state of the generator. Passing by reference, unsurprisingly, fix that issue.
2.) James Christie for his help on making sure that another computer (or two or three) that does not run a rolling-release Linux distro would be able to compile and run the code and for his advice on C++ praxis.
3.) Yaks. They always need shaving.
