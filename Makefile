SHELL    = /bin/sh

SRC      = src
BIN      = bin

CC       = gcc-10
CXX      = g++-10

# c++ standard
CXXSTD = -std=c++20

# c++ optimizations
CXXOPT = -Ofast

# c++ verboisty
CXXVRB = -Wall

CPPFLAGS = 
CFLAGS   = 
CXXFLAGS = $(CXXSTD) $(CXXOPT) $(CXXVRB) -lstdc++

all: cohen_chess magic_generator magic_evaluator

cohen_chess:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(SRC)/$@.cpp -o $(BIN)/$@

magic_generator:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(SRC)/$@.cpp -o $(BIN)/$@

magic_evaluator:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(SRC)/$@.cpp -o $(BIN)/$@

clean:
	rm -rf $(BIN) *.o