#ifndef COHEN_CHESS_TYPES_PIECE_TYPE_H_INCLUDED
#define COHEN_CHESS_TYPES_PIECE_TYPE_H_INCLUDED

#include <cstdint>

namespace cohen_chess
{
    typedef uint8_t PieceType;

    enum : PieceType
    {
        kPieceTypeNone  = 0,
        kPawn           = 1,
        kKnight         = 2,
        kBishop         = 3,
        kRook           = 4,
        kQueen          = 5,
        kKing           = 6,
        kPieceTypeAll   = 7,
        kPieceTypeNB    = 8,
    };
}

#endif