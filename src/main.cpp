#include "engine.h"
#include "hash.h"
#include "io.h"
#include "types.h"
#include "util.h"

#include <iostream>

using namespace cohen_chess;

int main(int argc, char* argv[])
{
    direction::InitRayBetween();
    bitboard::InitLineBitboards();
    bitboard::InitBetweenBitboards();

    //int x = 0xFA;
    //std::cout << util::BinaryString<12>(x) << std::endl;
    //std::cout << io::AsciiBoard<kWhite>(RankBB(kRank4) | DiagBB(kDiag4)) << std::endl << std::endl;

    Board board;

    board.put(kWhiteRook, kA1);

    board.put(kWhitePawn, kA2);
    board.put(kWhitePawn, kB2);
    board.put(kWhitePawn, kC2);
    board.put(kWhitePawn, kD2);
    board.put(kWhitePawn, kE2);
    board.put(kWhitePawn, kF2);
    board.put(kWhitePawn, kG2);
    board.put(kWhitePawn, kH2);

    board.put(kBlackRook, kA8);

    board.put(kBlackPawn, kA7);
    board.put(kBlackPawn, kB7);
    board.put(kBlackPawn, kC7);
    board.put(kBlackPawn, kD7);
    board.put(kBlackPawn, kE7);
    board.put(kBlackPawn, kF7);
    board.put(kBlackPawn, kG7);
    board.put(kBlackPawn, kH7);

    std::cout << io::AsciiBoard<kWhite>(board) << std::endl;
    return 0;
}
