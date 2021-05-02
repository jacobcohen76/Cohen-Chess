SHELL    = /bin/sh

SRC      = src
BIN      = bin

CC       = gcc-10
CXX      = clang++

# c++ standard
CXXSTD = -std=c++20

# c++ optimizations
CXXOPT = -Ofast

# c++ verboisty
CXXVRB = -Wall

CPPFLAGS = 
CFLAGS   = 
CXXFLAGS = $(CXXSTD) $(CXXOPT) $(CXXVRB) -lstdc++ -fconstexpr-steps=2147483647

all: cohen_chess hex_generator magic_generator magic_evaluator speed_test

cohen_chess:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(SRC)/$@.cpp -o $(BIN)/$@

hex_generator:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(SRC)/$@.cpp -o $(BIN)/$@

magic_generator:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(SRC)/$@.cpp -o $(BIN)/$@

magic_evaluator:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(SRC)/$@.cpp -o $(BIN)/$@

speed_test:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(SRC)/$@.cpp -o $(BIN)/$@

clean:
	rm -rf $(BIN) *.o