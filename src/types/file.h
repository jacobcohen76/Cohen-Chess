#ifndef COHEN_CHESS_TYPES_FILE_H_INCLUDED
#define COHEN_CHESS_TYPES_FILE_H_INCLUDED

#include "color.h"

#include <cstdint>

namespace cohen_chess
{
    enum File : int8_t
    {
        kFileA  = 0,
        kFileB  = 1,
        kFileC  = 2,
        kFileD  = 3,
        kFileE  = 4,
        kFileF  = 5,
        kFileG  = 6,
        kFileH  = 7,
        kFileNB = 8,
    };

    constexpr File MirrorFile(File f)
    {
        return File(f ^ kFileH);
    }

    constexpr File RelativeFile(Color side, File f)
    {
        return File(f ^ (side * kFileH));
    }

    inline File& operator++(File& op)
    {
        return op = File(int8_t(op) + 1);
    }

    inline File& operator--(File& op)
    {
        return op = File(int8_t(op) - 1);
    }

    constexpr File operator+(File op)
    {
        return File(+int8_t(op));
    }

    constexpr File operator-(File op)
    {
        return File(-int8_t(op));
    }

    constexpr File operator~(File op)
    {
        return File(~int8_t(op));
    }

    template<typename Integral>
    constexpr File operator<<(File op1, Integral op2)
    {
        return File(int8_t(op1) << op2);
    }

    template<typename Integral>
    constexpr File operator>>(File op1, Integral op2)
    {
        return File(int8_t(op1) >> op2);
    }

    constexpr File operator&(File op1, File op2)
    {
        return File(int8_t(op1) & int8_t(op2));
    }

    constexpr File operator^(File op1, File op2)
    {
        return File(int8_t(op1) ^ int8_t(op2));
    }

    constexpr File operator|(File op1, File op2)
    {
        return File(int8_t(op1) ^ int8_t(op2));
    }

    template<typename Integral>
    inline File& operator+=(File& lhs, Integral rhs)
    {
        return lhs = File(int8_t(lhs) + rhs);
    }

    template<typename Integral>
    inline File& operator-=(File& lhs, Integral rhs)
    {
        return lhs = File(int8_t(lhs) - rhs);
    }

    template<typename Integral>
    inline File& operator*=(File& lhs, Integral rhs)
    {
        return lhs = File(int8_t(lhs) * rhs);
    }

    template<typename Integral>
    inline File& operator/=(File& lhs, Integral rhs)
    {
        return lhs = File(int8_t(lhs) / rhs);
    }

    template<typename Integral>
    inline File& operator%=(File& lhs, Integral rhs)
    {
        return lhs = File(int8_t(lhs) % rhs);
    }

    template<typename Integral>
    inline File& operator<<=(File& lhs, Integral rhs)
    {
        return lhs = File(int8_t(lhs) << rhs);
    }

    template<typename Integral>
    inline File& operator>>=(File& lhs, Integral rhs)
    {
        return lhs = File(int8_t(lhs) >> rhs);
    }

    template<typename Integral>
    inline File& operator&=(File& lhs, Integral rhs)
    {
        return lhs = File(int8_t(lhs) & rhs);
    }

    template<typename Integral>
    inline File& operator^=(File& lhs, Integral rhs)
    {
        return lhs = File(int8_t(lhs) ^ rhs);
    }

    template<typename Integral>
    inline File& operator|=(File& lhs, Integral rhs)
    {
        return lhs = File(int8_t(lhs) | rhs);
    }
};

#endif