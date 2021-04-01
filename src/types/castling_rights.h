#ifndef COHEN_CHESS_TYPES_CASTLING_RIGHTS_H_INCLUDED
#define COHEN_CHESS_TYPES_CASTLING_RIGHTS_H_INCLUDED

#include "square.h"

#include <cstdint>

namespace cohen_chess
{
    enum CastlingRights : uint8_t
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

    constexpr CastlingRights& operator++(CastlingRights& op)
    {
        return op = CastlingRights(uint8_t(op) + 1);
    }

    constexpr CastlingRights& operator--(CastlingRights& op)
    {
        return op = CastlingRights(uint8_t(op) - 1);
    }

    constexpr CastlingRights operator+(CastlingRights op)
    {
        return CastlingRights(+uint8_t(op));
    }

    constexpr CastlingRights operator-(CastlingRights op)
    {
        return CastlingRights(-uint8_t(op));
    }

    constexpr CastlingRights operator~(CastlingRights op)
    {
        return CastlingRights(~uint8_t(op));
    }

    template<typename Integral>
    constexpr CastlingRights operator<<(CastlingRights op1, Integral op2)
    {
        return CastlingRights(uint8_t(op1) << op2);
    }

    template<typename Integral>
    constexpr CastlingRights operator>>(CastlingRights op1, Integral op2)
    {
        return CastlingRights(uint8_t(op1) >> op2);
    }

    constexpr CastlingRights operator&(CastlingRights op1, CastlingRights op2)
    {
        return CastlingRights(uint8_t(op1) & uint8_t(op2));
    }

    constexpr CastlingRights operator^(CastlingRights op1, CastlingRights op2)
    {
        return CastlingRights(uint8_t(op1) ^ uint8_t(op2));
    }

    constexpr CastlingRights operator|(CastlingRights op1, CastlingRights op2)
    {
        return CastlingRights(uint8_t(op1) ^ uint8_t(op2));
    }

    template<typename Integral>
    constexpr CastlingRights& operator+=(CastlingRights& lhs, Integral rhs)
    {
        return lhs = CastlingRights(uint8_t(lhs) + rhs);
    }

    template<typename Integral>
    constexpr CastlingRights& operator-=(CastlingRights& lhs, Integral rhs)
    {
        return lhs = CastlingRights(uint8_t(lhs) - rhs);
    }

    template<typename Integral>
    constexpr CastlingRights& operator*=(CastlingRights& lhs, Integral rhs)
    {
        return lhs = CastlingRights(uint8_t(lhs) * rhs);
    }

    template<typename Integral>
    constexpr CastlingRights& operator/=(CastlingRights& lhs, Integral rhs)
    {
        return lhs = CastlingRights(uint8_t(lhs) / rhs);
    }

    template<typename Integral>
    constexpr CastlingRights& operator%=(CastlingRights& lhs, Integral rhs)
    {
        return lhs = CastlingRights(uint8_t(lhs) % rhs);
    }

    template<typename Integral>
    constexpr CastlingRights& operator<<=(CastlingRights& lhs, Integral rhs)
    {
        return lhs = CastlingRights(uint8_t(lhs) << rhs);
    }

    template<typename Integral>
    constexpr CastlingRights& operator>>=(CastlingRights& lhs, Integral rhs)
    {
        return lhs = CastlingRights(uint8_t(lhs) >> rhs);
    }

    template<typename Integral>
    constexpr CastlingRights& operator&=(CastlingRights& lhs, Integral rhs)
    {
        return lhs = CastlingRights(uint8_t(lhs) & rhs);
    }

    template<typename Integral>
    constexpr CastlingRights& operator^=(CastlingRights& lhs, Integral rhs)
    {
        return lhs = CastlingRights(uint8_t(lhs) ^ rhs);
    }

    template<typename Integral>
    constexpr CastlingRights& operator|=(CastlingRights& lhs, Integral rhs)
    {
        return lhs = CastlingRights(uint8_t(lhs) | rhs);
    }
}

#endif
