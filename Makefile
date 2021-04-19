SHELL = /bin/sh

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
CXXFLAGS = $(CXXSTD) $(CXXOPT) $(CXXVRB)

# for clang
# -fconstexpr-steps=1000000000 -lstdc++

all: main

main:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(SRC)/main.cpp -o cohen_chess

clean:
	rm -rf $(BIN) *.o