CXX          = g++
CXX_FLAGS    = -O3 -std=c++11
LINKER_FLAGS = -lbenchmark -lpthread -fopenmp

matrixMultiply : matrixMultiply.cpp
	$(CXX) matrixMultiply.cpp $(CXX_FLAGS) $(LINKER_FLAGS) -o matrixMultiply

clean : 
	rm -rf matrixMultiply
