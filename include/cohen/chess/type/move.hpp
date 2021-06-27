#ifndef COHEN_CHESS_TYPE_MOVE_HPP_INCLUDED
#define COHEN_CHESS_TYPE_MOVE_HPP_INCLUDED

#include <cassert>
#include <cstdint>

#include <cohen/chess/type/piece.hpp>
#include <cohen/chess/type/square.hpp>

namespace cohen::chess::type::move
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

namespace cohen::chess
{
    using cohen::chess::type::move::MoveType;

    using cohen::chess::type::move::kQuietMove;
    using cohen::chess::type::move::kPromotion;
    using cohen::chess::type::move::kEnPassant;
    using cohen::chess::type::move::kCastling;

    using cohen::chess::type::move::Move;

    using cohen::chess::type::move::kMoveNone;
    using cohen::chess::type::move::kMoveNull;

    using cohen::chess::type::move::MakeMove;
    using cohen::chess::type::move::FromSquare;
    using cohen::chess::type::move::ToSquare;
    using cohen::chess::type::move::MoveTypeOf;
    using cohen::chess::type::move::PromotedTo;
    using cohen::chess::type::move::PromotionMoveType;
}

#endif
