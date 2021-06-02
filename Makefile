SHELL     = /bin/sh

SRC       = src
BIN       = bin

CC        = clang
CXX       = clang++

CPPNDEBUG = -DNDEBUG

CXXVER    = -std=c++20
CXXVRB    = -Wall
CXXOPT    = -Ofast
CXXINCL   = -Isrc

CXXSTDLIB = -stdlib=libstdc++
CXXLIMITS = -fconstexpr-steps=2147483647

CPPFLAGS  = $(CPPNDEBUG)
CFLAGS    = 
CXXFLAGS  = $(CXXVER) $(CXXVRB) $(CXXOPT) $(CXXINCL) -S

ifeq ($(CXX),clang++)
	CXXFLAGS += $(CXXSTDLIB)
	CXXFLAGS += $(CXXLIMITS)
endif

all: cohen_chess

cohen_chess:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(SRC)/$@.cpp -o $(BIN)/$@

clean:
	rm -rf $(BIN) *.o