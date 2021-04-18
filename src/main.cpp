#include "cohen_chess.h"

#include <iostream>

int main(int argc, char* argv[])
{
    using namespace cohen_chess;

    Bitboard occ = 0xAB83EF87C7123;
    std::cout << "occ:" << std::endl;
    std::cout << io::AsciiBoard(occ) << std::endl << std::endl;

    std::cout << "RayBishopAttacks:" << std::endl;
    std::cout << io::AsciiBoard(RayBishopAttacks(occ, kD5)) << std::endl << std::endl;
    cohen_chess::LookupSquareBB(kA2);

    return 0;
}
