#include "cohen_chess.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace cohen_chess;

enum ArgumentIndices
{
    kSlidingPieceType,
    kSquare,
    kMagicNumber,
};

int main(int argc, char* argv[])
{
    std::vector<std::string> arguments(argv + 1, argv + argc);
    Square sq = CoordinateToSquare(arguments[kSquare]);
    Bitboard magic = std::stoull(arguments[kMagicNumber], nullptr, 16);
    Magic m;

    if (arguments[kSlidingPieceType] == "bishop")
    {
        m.mask = MagicBishopMask(sq);
    }
    else if (arguments[kSlidingPieceType] == "rook")
    {
        m.mask = MagicRookMask(sq);
    }
    else
    {
        std::cout << "Error: Piece type must be either 'bishop' or 'rook', but was given as '" << arguments[kSlidingPieceType] << "'." << std::endl;
        exit(1);
    }

    m.begin = 0;
    m.magic = magic;
    m.shift = kSquareNB - PopCount(m.mask);

    size_t evaluation = MagicSize(m);
    std::cout << "Evaluation: " << evaluation << std::endl;

    return 0;
}