SHELL = /bin/sh

SRC      = src
BIN      = bin

cc       = gcc-10
CXX      = g++-10

CPPFLAGS = 
CFLAGS   = 
CXXFLAGS = -std=c++20

all: cohen_chess

cohen_chess: main

main:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(SRC)/$@.cpp -o $(BIN)/$@.out

clean:
	rm -rf $(BIN) *.o