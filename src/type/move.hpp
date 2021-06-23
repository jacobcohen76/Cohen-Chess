#ifndef COHEN_CHESS_TYPE_MOVE_HPP_INCLUDED
#define COHEN_CHESS_TYPE_MOVE_HPP_INCLUDED

#include <cassert>
#include <cstdint>

#include <type/piece.hpp>
#include <type/square.hpp>

namespace cohen_chess::type::move
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
        assert(kA1 <= from && from < kSquareNB);
        assert(kA1 <= to   && to   < kSquareNB);
        return (to << 6) | from;
    }

    constexpr Move MakeMove(Square from, Square to, MoveType type) noexcept
    {
        assert(kA1 <= from && from < kSquareNB);
        assert(kA1 <= to   && to   < kSquareNB);
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
        return ((move >> 12) & 0b0011) + kKnight;
    }

    constexpr MoveType PromotionMoveType(PieceType promoted_to) noexcept
    {
        return ((promoted_to - kKnight) << 12) | kPromotion;
    }
}

namespace cohen_chess
{
    using type::move::MoveType;

    using type::move::kQuietMove;
    using type::move::kPromotion;
    using type::move::kEnPassant;
    using type::move::kCastling;

    using type::move::Move;

    using type::move::kMoveNone;
    using type::move::kMoveNull;

    using type::move::MakeMove;
    using type::move::FromSquare;
    using type::move::ToSquare;
    using type::move::MoveTypeOf;
    using type::move::PromotedTo;
    using type::move::PromotionMoveType;
}

#endif
