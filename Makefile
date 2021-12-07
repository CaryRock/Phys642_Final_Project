CXX=g++
CLANGXX=clang++
CXXFLAGS=-I. --std=c++17 -O3
LIBS=-l boost_random -l boost_program_options
DEPS = common_headers.hpp MC_functions.hpp
OBJ = MC_functions.o GetOptions.o IsingMC_FinalProject.o
OBJC= MC_functions.oc GetOptions.oc IsingMC_FinalProject.oc

%.o: %.cpp $(DEPS)
	$(CXX) $(LIBS) -c -o $@ $< $(CXXFLAGS)

2dIsing: $(OBJ)
	$(CXX) $(LIBS) -o $@ $^ $(CXXFLAGS)

%.oc: %.cpp $(DEPS)
	$(CLANGXX) $(LIBS) -c -o $@ $< $(CXXFLAGS)

2dIsingClang: $(OBJC)
	$(CLANGXX) $(LIBS) -o $@ $^ $(CXXFLAGS)

clean: 
	rm *.o *.oc *.dat
