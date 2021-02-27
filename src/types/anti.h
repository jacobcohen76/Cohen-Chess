#ifndef COHEN_CHESS_TYPES_ANTI_H_INCLUDED
#define COHEN_CHESS_TYPES_ANTI_H_INCLUDED

#include <cstdint>

namespace cohen_chess
{
    enum Anti : int8_t
    {
        kAnti1  =  0,
        kAnti2  =  1,
        kAnti3  =  2,
        kAnti4  =  3,
        kAnti5  =  4,
        kAnti6  =  5,
        kAnti7  =  6,
        kAnti8  =  7,
        kAnti9  =  8,
        kAntiA  =  9,
        kAntiB  = 10,
        kAntiC  = 11,
        kAntiD  = 12,
        kAntiE  = 13,
        kAntiF  = 14,
        kAntiNB = 15,
    };

    constexpr Anti MirroAnti(Anti a)
    {
        return Anti(kAntiF - a);
    }

    inline Anti& operator++(Anti& op)
    {
        return op = Anti(int8_t(op) + 1);
    }

    inline Anti& operator--(Anti& op)
    {
        return op = Anti(int8_t(op) - 1);
    }

    constexpr Anti operator+(Anti op)
    {
        return Anti(+int8_t(op));
    }

    constexpr Anti operator-(Anti op)
    {
        return Anti(-int8_t(op));
    }

    constexpr Anti operator~(Anti op)
    {
        return Anti(~int8_t(op));
    }

    template<typename Integral>
    constexpr Anti operator<<(Anti op1, Integral op2)
    {
        return Anti(int8_t(op1) << op2);
    }

    template<typename Integral>
    constexpr Anti operator>>(Anti op1, Integral op2)
    {
        return Anti(int8_t(op1) >> op2);
    }

    constexpr Anti operator&(Anti op1, Anti op2)
    {
        return Anti(int8_t(op1) & int8_t(op2));
    }

    constexpr Anti operator^(Anti op1, Anti op2)
    {
        return Anti(int8_t(op1) ^ int8_t(op2));
    }

    constexpr Anti operator|(Anti op1, Anti op2)
    {
        return Anti(int8_t(op1) ^ int8_t(op2));
    }

    template<typename Integral>
    inline Anti& operator+=(Anti& lhs, Integral rhs)
    {
        return lhs = Anti(int8_t(lhs) + rhs);
    }

    template<typename Integral>
    inline Anti& operator-=(Anti& lhs, Integral rhs)
    {
        return lhs = Anti(int8_t(lhs) - rhs);
    }

    template<typename Integral>
    inline Anti& operator*=(Anti& lhs, Integral rhs)
    {
        return lhs = Anti(int8_t(lhs) * rhs);
    }

    template<typename Integral>
    inline Anti& operator/=(Anti& lhs, Integral rhs)
    {
        return lhs = Anti(int8_t(lhs) / rhs);
    }

    template<typename Integral>
    inline Anti& operator%=(Anti& lhs, Integral rhs)
    {
        return lhs = Anti(int8_t(lhs) % rhs);
    }

    template<typename Integral>
    inline Anti& operator<<=(Anti& lhs, Integral rhs)
    {
        return lhs = Anti(int8_t(lhs) << rhs);
    }

    template<typename Integral>
    inline Anti& operator>>=(Anti& lhs, Integral rhs)
    {
        return lhs = Anti(int8_t(lhs) >> rhs);
    }

    template<typename Integral>
    inline Anti& operator&=(Anti& lhs, Integral rhs)
    {
        return lhs = Anti(int8_t(lhs) & rhs);
    }

    template<typename Integral>
    inline Anti& operator^=(Anti& lhs, Integral rhs)
    {
        return lhs = Anti(int8_t(lhs) ^ rhs);
    }

    template<typename Integral>
    inline Anti& operator|=(Anti& lhs, Integral rhs)
    {
        return lhs = Anti(int8_t(lhs) | rhs);
    }
};

#endif