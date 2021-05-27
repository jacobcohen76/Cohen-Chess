#ifndef COHEN_CHESS_TYPES_MOVE_HPP_INCLUDED
#define COHEN_CHESS_TYPES_MOVE_HPP_INCLUDED

#include <types/piece.hpp>
#include <types/square.hpp>

#include <cstdint>

namespace cohen_chess
{
    typedef uint16_t MoveType, Move;

    enum : MoveType
    {
        kQuietMove = 0x0000,
        kPromotion = 0x4000,
        kEnPassant = 0x8000,
        kCastling  = 0xC000,
    };

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