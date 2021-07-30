SHELL       = /bin/sh

SRC         = src
BIN         = bin
INCLUDE     = include

CC          = gcc-10
CXX         = g++-10

CPPFLAGS    = -I$(INCLUDE)

CFLAGS      =

CXXFLAGS    = -std=c++20
CXXFLAGS   += -Wall -Wextra -Wpedantic -Wshadow -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2  -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast
CXXFLAGS   += -O3 -march=native

all: release

clang: CC        = clang-11
clang: CXX       = clang++-11
clang: CXXFLAGS += -stdlib=libstdc++
clang: CXXFLAGS += -fconstexpr-steps=2147483647
clang: all

debug: CPPFLAGS += -DDEBUG
debug: CXXFLAGS += -g
debug: main

release: CPPFLAGS += -DNDEBUG
release: main

main:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(SRC)/$@.cpp -o $(BIN)/$@.out
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(SRC)/$@.cpp -o $(BIN)/$@.asm -S

clean:
	rm -rf $(BIN) *.o
