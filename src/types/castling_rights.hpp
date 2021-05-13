#ifndef COHEN_CHESS_TYPES_CASTLING_RIGHTS_HPP_INCLUDED
#define COHEN_CHESS_TYPES_CASTLING_RIGHTS_HPP_INCLUDED

#include <types/color.hpp>
#include <types/square.hpp>

#include <cstdint>

namespace cohen_chess
{
    typedef uint8_t CastlingRights;

    enum : CastlingRights
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

    constexpr CastlingRights CastlingRightsSide(Color side)
    {
        return kCastlingWhite << (side << 1);
    }

    constexpr CastlingRights CastlingRightsQueenSide(Color side)
    {
        return kWhiteOO << (side << 1);
    }

    constexpr CastlingRights CastlingRightsKingSide(Color side)
    {
        return kWhiteOOO << (side << 1);
    }
}

#endif
