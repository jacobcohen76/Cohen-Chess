#ifndef COHEN_CHESS_TYPES_MOVE_H_INCLUDED
#define COHEN_CHESS_TYPES_MOVE_H_INCLUDED

#include "move_type.h"
#include "piece_type.h"

#include <cstdint>

namespace cohen_chess
{
    typedef uint16_t Move;

    enum : Move
    {
        kMoveNone = 0x0000,
        kMoveNull = 0xFFFF,
    };

    constexpr Move MakeMove(Square from, Square to)
    {
        return Move(uint16_t(from) | (uint16_t(to) << 6));
    }

    constexpr Move MakeMove(MoveType type, Square from, Square to)
    {
        return Move(MakeMove(from, to) | type);
    }

    constexpr Square FromSquare(Move move)
    {
        return Square(move & 0x3F);
    }

    constexpr Square ToSquare(Move move)
    {
        return Square((move >> 6) & 0x3F);
    }

    constexpr MoveType MoveTypeOf(Move move)
    {
        return MoveType(move & 0xF000);
    }

    constexpr PieceType PromotedTo(Move move)
    {
        return PieceType(((move >> 12) & 0x3) + kKnight);
    }
}

#endif