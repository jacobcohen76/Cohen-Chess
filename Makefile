SHELL       = /bin/sh

SRC         = src
BIN         = bin
INCLUDE     = include

CC          = clang-11
CXX         = clang++-11

CPPFLAGS    =
CFLAGS      =

CXXFLAGS    = -I$(INCLUDE)
CXXFLAGS   += -stdlib=libstdc++
CXXFLAGS   += -std=c++20
CXXFLAGS   += -Wall
CXXFLAGS   += -O3
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
	objdump -SDge $(BIN)/$@.out > $(BIN)/$@.asm

clean:
	rm -rf $(BIN) *.o
