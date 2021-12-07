CXX=g++
CXXFLAGS=-I. --std=c++17
LIBS=-l boost_random -l boost_program_options
DEPS = common_headers.hpp MC_functions.hpp
OBJ = MC_functions.o GetOptions.o IsingMC_FinalProject.o

%.o: %.cpp $(DEPS)
	$(CXX) $(LIBS) -c -o $@ $< $(CXXFLAGS)

2dIsing: $(OBJ)
	$(CXX) $(LIBS) -o $@ $^ $(CXXFLAGS)

clean: 
	rm *.o *.dat
