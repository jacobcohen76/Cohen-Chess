#ifndef COHEN_CHESS_TYPES_MOVE_HPP_INCLUDED
#define COHEN_CHESS_TYPES_MOVE_HPP_INCLUDED

#include <cstdint>

#include <types/piece.hpp>
#include <types/square.hpp>

namespace cohen_chess
{
    namespace move
    {
        using MoveType = uint16_t;

        enum MoveTypeConstant : MoveType
        {
            kQuietMove = 0x0000,
            kPromotion = 0x4000,
            kEnPassant = 0x8000,
            kCastling  = 0xC000,
        };

        using Move = uint16_t;

        enum MoveConstant : Move
        {
            kMoveNone = 0x0000,
            kMoveNull = 0xFFFF,
        };

        constexpr Move MakeMove(Square from, Square to) noexcept
        {
            return (to << 6) | from;
        }

        constexpr Move MakeMove(Square from, Square to, MoveType type) noexcept
        {
            return MakeMove(from, to) | type;
        }

        constexpr Square FromSquare(Move move) noexcept
        {
            return move & 0x3F;
        }

        constexpr Square ToSquare(Move move) noexcept
        {
            return (move >> 6) & 0x3F;
        }

        constexpr MoveType MoveTypeOf(Move move) noexcept
        {
            return move & 0xC000;
        }

        constexpr PieceType PromotedTo(Move move) noexcept
        {
            return ((move >> 12) & 0x3) + kKnight;
        }

        constexpr MoveType PromotionMoveType(PieceType promoted_to) noexcept
        {
            return ((promoted_to - kKnight) << 12) | kPromotion;
        }
    }

    using namespace move;
}

#endif