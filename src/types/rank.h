#ifndef COHEN_CHESS_TYPES_RANK_H_INCLUDED
#define COHEN_CHESS_TYPES_RANK_H_INCLUDED

#include "color.h"

#include <cstdint>

namespace cohen_chess
{
    enum Rank : int8_t
    {
        kRank1  = 0,
        kRank2  = 1,
        kRank3  = 2,
        kRank4  = 3,
        kRank5  = 4,
        kRank6  = 5,
        kRank7  = 6,
        kRank8  = 7,
        kRankNB = 8,
    };

    constexpr Rank MirrorRank(Rank r)
    {
        return Rank(r ^ kRank8);
    }

    constexpr Rank RelativeRank(Color side, Rank r)
    {
        return Rank(r ^ (side * kRank8));
    }

    inline Rank& operator++(Rank& op)
    {
        return op = Rank(int8_t(op) + 1);
    }

    inline Rank& operator--(Rank& op)
    {
        return op = Rank(int8_t(op) - 1);
    }

    constexpr Rank operator+(Rank op)
    {
        return Rank(+int8_t(op));
    }

    constexpr Rank operator-(Rank op)
    {
        return Rank(-int8_t(op));
    }

    constexpr Rank operator~(Rank op)
    {
        return Rank(~int8_t(op));
    }

    template<typename Integral>
    constexpr Rank operator<<(Rank op1, Integral op2)
    {
        return Rank(int8_t(op1) << op2);
    }

    template<typename Integral>
    constexpr Rank operator>>(Rank op1, Integral op2)
    {
        return Rank(int8_t(op1) >> op2);
    }

    constexpr Rank operator&(Rank op1, Rank op2)
    {
        return Rank(int8_t(op1) & int8_t(op2));
    }

    constexpr Rank operator^(Rank op1, Rank op2)
    {
        return Rank(int8_t(op1) ^ int8_t(op2));
    }

    constexpr Rank operator|(Rank op1, Rank op2)
    {
        return Rank(int8_t(op1) ^ int8_t(op2));
    }

    template<typename Integral>
    inline Rank& operator+=(Rank& lhs, Integral rhs)
    {
        return lhs = Rank(int8_t(lhs) + rhs);
    }

    template<typename Integral>
    inline Rank& operator-=(Rank& lhs, Integral rhs)
    {
        return lhs = Rank(int8_t(lhs) - rhs);
    }

    template<typename Integral>
    inline Rank& operator*=(Rank& lhs, Integral rhs)
    {
        return lhs = Rank(int8_t(lhs) * rhs);
    }

    template<typename Integral>
    inline Rank& operator/=(Rank& lhs, Integral rhs)
    {
        return lhs = Rank(int8_t(lhs) / rhs);
    }

    template<typename Integral>
    inline Rank& operator%=(Rank& lhs, Integral rhs)
    {
        return lhs = Rank(int8_t(lhs) % rhs);
    }

    template<typename Integral>
    inline Rank& operator<<=(Rank& lhs, Integral rhs)
    {
        return lhs = Rank(int8_t(lhs) << rhs);
    }

    template<typename Integral>
    inline Rank& operator>>=(Rank& lhs, Integral rhs)
    {
        return lhs = Rank(int8_t(lhs) >> rhs);
    }

    template<typename Integral>
    inline Rank& operator&=(Rank& lhs, Integral rhs)
    {
        return lhs = Rank(int8_t(lhs) & rhs);
    }

    template<typename Integral>
    inline Rank& operator^=(Rank& lhs, Integral rhs)
    {
        return lhs = Rank(int8_t(lhs) ^ rhs);
    }

    template<typename Integral>
    inline Rank& operator|=(Rank& lhs, Integral rhs)
    {
        return lhs = Rank(int8_t(lhs) | rhs);
    }
};

#endif