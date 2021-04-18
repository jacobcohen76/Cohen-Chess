SHELL = /bin/sh

SRC      = src
BIN      = bin

cc       = gcc-10
CXX      = clang

CPPFLAGS = 
CFLAGS   = 
CXXFLAGS = -std=c++20 -O3 -fconstexpr-steps=1000000000 -lstdc++

all: cohen_chess

cohen_chess: main

main:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(SRC)/$@.cpp -o $(BIN)/$@.out

clean:
	rm -rf $(BIN) *.o