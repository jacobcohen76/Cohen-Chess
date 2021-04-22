#include "cohen_chess.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace cohen_chess;

enum ArgumentIndices
{
    kMagicType,
    kSlidingPieceType,
    kSquare,
    kMagicNumber,
};

int main(int argc, char* argv[])
{
    std::vector<std::string> arguments(argv + 1, argv + argc);
    size_t evaluation = 0;
    Square sq = CoordinateToSquare(arguments[kSquare]);
    Bitboard magic = std::stoull(arguments[kMagicNumber], nullptr, 16);
    if (arguments[kMagicType] == "fancy")
    {
        FancyMagic m;
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
        evaluation = MagicSize(m);
    }
    else if(arguments[kMagicType] == "black")
    {
        BlackMagic m;
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
        evaluation = MagicSize(m);
    }
    else
    {
        std::cout << "Error: Magic type must be either 'fancy' or 'black', but was given as '" << arguments[kMagicType] << "'." << std::endl;
        exit(1);
    }
    std::cout << "Evaluation: " << evaluation << std::endl;
    return 0;
}