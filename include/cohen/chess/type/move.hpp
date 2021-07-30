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
        kQuietMove = 0b0000000000000000,
        kPromotion = 0b0100000000000000,
        kEnPassant = 0b1000000000000000,
        kCastling  = 0b1100000000000000,
    };

    using Move = uint16_t;

    enum MoveConstant : Move
    {
        kMoveNone = 0b0000000000000000,
        kMoveNull = 0b1111111111111111,
    };

    constexpr Move MakeMove(Square from, Square to, MoveType type = kQuietMove) noexcept
    {
        assert(kA1 <= from && from < kSquareNB);
        assert(kA1 <= to   &&   to < kSquareNB);
        return type | from | (to << 6);
    }

    constexpr Square FromSquare(Move move) noexcept
    {
        return move & 0b0000000000111111;
    }

    constexpr Square ToSquare(Move move) noexcept
    {
        return (move >> 6) & 0b0000000000111111;
    }

    constexpr MoveType MoveTypeOf(Move move) noexcept
    {
        return move & 0b1100000000000000;
    }

    constexpr PieceType PromotedTo(Move move) noexcept
    {
        return ((move >> 12) & 0b0011) + kKnight;
    }

    constexpr MoveType PromoMoveType(PieceType promoted_to) noexcept
    {
        return ((promoted_to - kKnight) << 12) | kPromotion;
    }
}

namespace cohen::chess
{
    using cohen::chess::type::move::MoveType;
    using enum cohen::chess::type::move::MoveTypeConstant;

    using cohen::chess::type::move::Move;
    using enum cohen::chess::type::move::MoveConstant;

    using cohen::chess::type::move::MakeMove;
    using cohen::chess::type::move::FromSquare;
    using cohen::chess::type::move::ToSquare;
    using cohen::chess::type::move::MoveTypeOf;
    using cohen::chess::type::move::PromotedTo;
    using cohen::chess::type::move::PromoMoveType;
}

#endif
