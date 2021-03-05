#ifndef COHEN_CHESS_TYPES_KEY_H_INCLUDED
#define COHEN_CHESS_TYPES_KEY_H_INCLUDED

#include <cstdint>

namespace cohen_chess
{
    enum Key : uint64_t
    {
        kKeyZero    = 0x0000000000000000,
        kKeyAll     = 0xFFFFFFFFFFFFFFFF,
    };

    inline Key& operator++(Key& op)
    {
        return op = Key(uint64_t(op) + 1ull);
    }

    inline Key& operator--(Key& op)
    {
        return op = Key(uint64_t(op) - 1ull);
    }

    constexpr Key operator+(Key op)
    {
        return Key(+uint64_t(op));
    }

    constexpr Key operator-(Key op)
    {
        return Key(-uint64_t(op));
    }

    constexpr Key operator~(Key op)
    {
        return Key(~uint64_t(op));
    }

    template<typename Integral>
    constexpr Key operator<<(Key op1, Integral op2)
    {
        return Key(uint64_t(op1) << op2);
    }

    template<typename Integral>
    constexpr Key operator>>(Key op1, Integral op2)
    {
        return Key(uint64_t(op1) >> op2);
    }

    constexpr Key operator&(Key op1, Key op2)
    {
        return Key(uint64_t(op1) & uint64_t(op2));
    }

    constexpr Key operator^(Key op1, Key op2)
    {
        return Key(uint64_t(op1) ^ uint64_t(op2));
    }

    constexpr Key operator|(Key op1, Key op2)
    {
        return Key(uint64_t(op1) ^ uint64_t(op2));
    }

    template<typename Integral>
    inline Key& operator+=(Key& lhs, Integral rhs)
    {
        return lhs = Key(uint64_t(lhs) + rhs);
    }

    template<typename Integral>
    inline Key& operator-=(Key& lhs, Integral rhs)
    {
        return lhs = Key(uint64_t(lhs) - rhs);
    }

    template<typename Integral>
    inline Key& operator*=(Key& lhs, Integral rhs)
    {
        return lhs = Key(uint64_t(lhs) * rhs);
    }

    template<typename Integral>
    inline Key& operator/=(Key& lhs, Integral rhs)
    {
        return lhs = Key(uint64_t(lhs) / rhs);
    }

    template<typename Integral>
    inline Key& operator%=(Key& lhs, Integral rhs)
    {
        return lhs = Key(uint64_t(lhs) % rhs);
    }

    template<typename Integral>
    inline Key& operator<<=(Key& lhs, Integral rhs)
    {
        return lhs = Key(uint64_t(lhs) << rhs);
    }

    template<typename Integral>
    inline Key& operator>>=(Key& lhs, Integral rhs)
    {
        return lhs = Key(uint64_t(lhs) >> rhs);
    }

    template<typename Integral>
    inline Key& operator&=(Key& lhs, Integral rhs)
    {
        return lhs = Key(uint64_t(lhs) & rhs);
    }

    template<typename Integral>
    inline Key& operator^=(Key& lhs, Integral rhs)
    {
        return lhs = Key(uint64_t(lhs) ^ rhs);
    }

    template<typename Integral>
    inline Key& operator|=(Key& lhs, Integral rhs)
    {
        return lhs = Key(uint64_t(lhs) | rhs);
    }
}

#endif