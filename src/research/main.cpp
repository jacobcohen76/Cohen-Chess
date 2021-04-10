#include "bitboard.h"

#include <iostream>

using namespace cohen_chess;

int main(int argc, char* argv[])
{
    const Bitboard const_bb = 20;
    Bitboard bb = 40;
    Bitboard res = bb / const_bb;
    uint64_t val = res;
    std::cout << res << std::endl;
    return 0;
}