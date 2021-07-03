SHELL     = /bin/sh

SRC       = src
BIN       = bin

CC        = clang
CXX       = clang++-11

CXXVER    = -std=c++20
CXXVRB    = -Wall
CXXOPT    = -Ofast
CXXINCL   = -Iinclude

CXXSTDLIB = -stdlib=libstdc++
CXXLIMITS = -fconstexpr-steps=2147483647

CPPFLAGS  = # -DNDEBUG
CFLAGS    = 
CXXFLAGS  = $(CXXVER) $(CXXVRB) $(CXXOPT) $(CXXINCL) # -S -fverbose-asm

ifeq ($(CXX),clang++-11)
	CXXFLAGS += $(CXXSTDLIB)
	CXXFLAGS += $(CXXLIMITS)
endif

all: main

main:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(SRC)/$@.cpp -o $(BIN)/$@.out

clean:
	rm -rf $(BIN) *.o
