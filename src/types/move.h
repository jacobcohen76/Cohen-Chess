#ifndef COHEN_CHESS_TYPES_MOVE_H_INCLUDED
#define COHEN_CHESS_TYPES_MOVE_H_INCLUDED

#include "piece.h"

#include <cstdint>

namespace cohen_chess
{
    typedef uint16_t MoveType;

    enum : MoveType
    {
        kQuietMove = 0x0000,
        kPromotion = 0x4000,
        kEnPassant = 0x8000,
        kCastling  = 0xC000,
    };

    typedef uint16_t Move;

    enum : Move
    {
        kMoveNone = 0x0000,
        kMoveNull = 0xFFFF,
    };

    constexpr Move MakeMove(Square from, Square to)
    {
        return (to << 6) | from;
    }

    constexpr Move MakeMove(Square from, Square to, MoveType type)
    {
        return MakeMove(from, to) | type;
    }

    constexpr Square FromSquare(Move move)
    {
        return move & 0x3F;
    }

    constexpr Square ToSquare(Move move)
    {
        return (move >> 6) & 0x3F;
    }

    constexpr MoveType MoveTypeOf(Move move)
    {
        return move & 0xC000;
    }

    constexpr PieceType PromotedTo(Move move)
    {
        return ((move >> 12) & 0x3) + kKnight;
    }

    constexpr MoveType PromotionMoveType(PieceType promoted_to)
    {
        return ((promoted_to - kKnight) << 12) | kPromotion;
    }
}

#endif