#Variable for c++ compiler
CXX := g++

#Variables for C++ compiler flags
CXXFLAGS := -O3 -std=c++11 -Wall -Wextra -Wconversion

TARGET := main
OBJS := main.o CGSolver.o COO2CSR.o matvecops.o sparse.o heat.o
INCS := CGSolver.hpp COO2CSR.hpp matvecops.hpp sparse.hpp heat.hpp

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) 

%.o: %.cpp $(INCS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# For targets that do not produce a file
.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET) *~

.PHONY: run
run: $(TARGET)
	./$(TARGET)