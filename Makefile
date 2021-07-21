SHELL       = /bin/sh

SRC         = src
BIN         = bin
INCLUDE     = include

CC          = clang-11
CXX         = clang++-11

CPPFLAGS    = -I$(INCLUDE)

CFLAGS      =

CXXFLAGS    = -std=c++20
CXXFLAGS   += -Wall
CXXFLAGS   += -O3 -march=native
CXXFLAGS   += -stdlib=libstdc++
CXXFLAGS   += -fconstexpr-steps=2147483647

all: release

debug: CPPFLAGS += -DDEBUG
debug: CXXFLAGS += -g
debug: main

release: CPPFLAGS += -DNDEBUG
release: main

main:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(SRC)/$@.cpp -o $(BIN)/$@.out

clean:
	rm -rf $(BIN) *.o
