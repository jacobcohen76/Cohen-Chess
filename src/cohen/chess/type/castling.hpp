#ifndef COHEN_TYPE_CASTLING_HPP_INCLUDED
#define COHEN_TYPE_CASTLING_HPP_INCLUDED

#include <cassert>
#include <cstdint>

#include <type/color.hpp>
#include <type/square.hpp>

namespace cohen::type::castling
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

namespace cohen
{
    using type::castling::Castling;

    using type::castling::kCastlingNone;
    using type::castling::kCastlingAll;
    using type::castling::kWhiteOO;
    using type::castling::kWhiteOOO;
    using type::castling::kCastlingWhite;
    using type::castling::kBlackOO;
    using type::castling::kBlackOOO;
    using type::castling::kCastlingBlack;
    using type::castling::kQueenSide;
    using type::castling::kKingSide;
    using type::castling::kCastlingNB;

    using type::castling::CastlingSide;
    using type::castling::CastlingQueenSide;
    using type::castling::CastlingKingSide;
}

#endif
