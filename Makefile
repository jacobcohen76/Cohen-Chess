SHELL    := /bin/sh

SRC      := src
BIN      := bin

CC       := gcc-10
CXX      := clang++

# C++ standard
CXXSTD := -std=c++20

# C++ verboisty
CXXVRB := -Wall

# C++ optimizations
CXXOPT := -Ofast

# include paths
INCL   := -I $(SRC)

CPPFLAGS := $(INCL)
CFLAGS   := 
CXXFLAGS := $(CXXSTD) $(CXXVRB) $(CXXOPT) -fconstexpr-steps=2147483647

all: cohen_chess

cohen_chess:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SRC)/$@.cpp -o $(BIN)/$@

clean:
	rm -rf $(BIN) *.o