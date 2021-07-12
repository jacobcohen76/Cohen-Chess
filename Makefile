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

all: debug

debug: CPPFLAGS += -DDEBUG
debug: CXXFLAGS += -g
debug: main dump

release: CPPFLAGS += -DNDEBUG
release: main dump
 
main:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(SRC)/$@.cpp -o $(BIN)/$@.out

dump:
	objdump -SDge $(BIN)/main.out > $(BIN)/main.asm

clean:
	rm -rf $(BIN) *.o
