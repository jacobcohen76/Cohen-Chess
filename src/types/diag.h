#ifndef COHEN_CHESS_TYPES_DIAG_H_INCLUDED
#define COHEN_CHESS_TYPES_DIAG_H_INCLUDED

#include <cstdint>

namespace cohen_chess
{
    enum Diag : int8_t
    {
        kDiag1  =  0,
        kDiag2  =  1,
        kDiag3  =  2,
        kDiag4  =  3,
        kDiag5  =  4,
        kDiag6  =  5,
        kDiag7  =  6,
        kDiag8  =  7,
        kDiag9  =  8,
        kDiagA  =  9,
        kDiagB  = 10,
        kDiagC  = 11,
        kDiagD  = 12,
        kDiagE  = 13,
        kDiagF  = 14,
        kDiagNB = 15,
    };

    constexpr Diag MirrorDiag(Diag d)
    {
        return Diag(kDiagF - d);
    }

    constexpr Diag& operator++(Diag& op)
    {
        return op = Diag(int8_t(op) + 1);
    }

    constexpr Diag& operator--(Diag& op)
    {
        return op = Diag(int8_t(op) - 1);
    }

    constexpr Diag operator+(Diag op)
    {
        return Diag(+int8_t(op));
    }

    constexpr Diag operator-(Diag op)
    {
        return Diag(-int8_t(op));
    }

    constexpr Diag operator~(Diag op)
    {
        return Diag(~int8_t(op));
    }

    template<typename Integral>
    constexpr Diag operator<<(Diag op1, Integral op2)
    {
        return Diag(int8_t(op1) << op2);
    }

    template<typename Integral>
    constexpr Diag operator>>(Diag op1, Integral op2)
    {
        return Diag(int8_t(op1) >> op2);
    }

    constexpr Diag operator&(Diag op1, Diag op2)
    {
        return Diag(int8_t(op1) & int8_t(op2));
    }

    constexpr Diag operator^(Diag op1, Diag op2)
    {
        return Diag(int8_t(op1) ^ int8_t(op2));
    }

    constexpr Diag operator|(Diag op1, Diag op2)
    {
        return Diag(int8_t(op1) ^ int8_t(op2));
    }

    template<typename Integral>
    constexpr Diag& operator+=(Diag& lhs, Integral rhs)
    {
        return lhs = Diag(int8_t(lhs) + rhs);
    }

    template<typename Integral>
    constexpr Diag& operator-=(Diag& lhs, Integral rhs)
    {
        return lhs = Diag(int8_t(lhs) - rhs);
    }

    template<typename Integral>
    constexpr Diag& operator*=(Diag& lhs, Integral rhs)
    {
        return lhs = Diag(int8_t(lhs) * rhs);
    }

    template<typename Integral>
    constexpr Diag& operator/=(Diag& lhs, Integral rhs)
    {
        return lhs = Diag(int8_t(lhs) / rhs);
    }

    template<typename Integral>
    constexpr Diag& operator%=(Diag& lhs, Integral rhs)
    {
        return lhs = Diag(int8_t(lhs) % rhs);
    }

    template<typename Integral>
    constexpr Diag& operator<<=(Diag& lhs, Integral rhs)
    {
        return lhs = Diag(int8_t(lhs) << rhs);
    }

    template<typename Integral>
    constexpr Diag& operator>>=(Diag& lhs, Integral rhs)
    {
        return lhs = Diag(int8_t(lhs) >> rhs);
    }

    template<typename Integral>
    constexpr Diag& operator&=(Diag& lhs, Integral rhs)
    {
        return lhs = Diag(int8_t(lhs) & rhs);
    }

    template<typename Integral>
    constexpr Diag& operator^=(Diag& lhs, Integral rhs)
    {
        return lhs = Diag(int8_t(lhs) ^ rhs);
    }

    template<typename Integral>
    constexpr Diag& operator|=(Diag& lhs, Integral rhs)
    {
        return lhs = Diag(int8_t(lhs) | rhs);
    }
}

#endif
