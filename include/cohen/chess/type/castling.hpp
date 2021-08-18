#ifndef COHEN_CHESS_TYPE_CASTLING_HPP_INCLUDED
#define COHEN_CHESS_TYPE_CASTLING_HPP_INCLUDED

#include <cassert>
#include <cstdint>

#include <cohen/chess/type/color.hpp>
#include <cohen/chess/type/square.hpp>

namespace cohen::chess::type::castling
{
    using Castling = uint8_t;

    enum CastlingConstant : Castling
    {
        kCastlingNone   = 0x0,
        kCastlingAll    = 0xF,

        kWhiteOO        = 0x1,
        kWhiteOOO       = 0x2,
        kCastlingWhite  = kWhiteOO | kWhiteOOO,

        kBlackOO        = 0x4,
        kBlackOOO       = 0x8,
        kCastlingBlack  = kBlackOO | kBlackOOO,

        kQueenSide      = kWhiteOO  | kBlackOO,
        kKingSide       = kWhiteOOO | kBlackOOO,

        kCastlingNB     = 16,
    };

    constexpr Castling CastlingSide(Color side) noexcept
    {
        assert(side == kWhite || side == kBlack);
        return kCastlingWhite << (side << 1);
    }

    constexpr Castling CastlingQueenSide(Color side) noexcept
    {
        assert(side == kWhite || side == kBlack);
        return kWhiteOO << (side << 1);
    }

    constexpr Castling CastlingKingSide(Color side) noexcept
    {
        assert(side == kWhite || side == kBlack);
        return kWhiteOOO << (side << 1);
    }
}

namespace cohen::chess
{
    using cohen::chess::type::castling::Castling;
    using enum cohen::chess::type::castling::CastlingConstant;

    using cohen::chess::type::castling::CastlingSide;
    using cohen::chess::type::castling::CastlingQueenSide;
    using cohen::chess::type::castling::CastlingKingSide;
}

#endif