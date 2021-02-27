#ifndef COHEN_CHESS_TYPES_DIRECTION_H_INCLUDED
#define COHEN_CHESS_TYPES_DIRECTION_H_INCLUDED

#include "square.h"

#include <cstdint>

namespace cohen_chess
{
    enum Direction : int8_t
    {
        kNorth          = +8,
        kEast           = +1,
        kSouth          = -kNorth,
        kWest           = -kEast,
        kNorthEast      = kNorth + kEast,
        kNorthWest      = kNorth + kWest,
        kSouthEast      = kSouth + kEast,
        kSouthWest      = kSouth + kWest,
        kDirectionNone  = 0,
    };

    namespace direction
    {
        extern Direction kRayBetween[kSquareNB][kSquareNB];
        
        void InitRayBetween();
    };

    inline Direction RayBetween(Square sq1, Square sq2)
    {
        return direction::kRayBetween[sq1][sq2];
    }

    inline Direction& operator++(Direction& op)
    {
        return op = Direction(int8_t(op) + 1);
    }

    inline Direction& operator--(Direction& op)
    {
        return op = Direction(int8_t(op) - 1);
    }

    constexpr Direction operator+(Direction op)
    {
        return Direction(+int8_t(op));
    }

    constexpr Direction operator-(Direction op)
    {
        return Direction(-int8_t(op));
    }

    constexpr Direction operator~(Direction op)
    {
        return Direction(~int8_t(op));
    }

    constexpr Direction operator-(Square sq1, Square sq2)
    {
        return Direction(int8_t(sq1) - int8_t(sq2));
    }

    constexpr Square operator+(Square sq, Direction dir)
    {
        return Square(int8_t(sq) + int8_t(dir));
    }

    constexpr Square operator-(Square sq, Direction dir)
    {
        return Square(int8_t(sq) - int8_t(dir));
    }

    template<typename Integral>
    constexpr Direction operator<<(Direction op1, Integral op2)
    {
        return Direction(int8_t(op1) << op2);
    }

    template<typename Integral>
    constexpr Direction operator>>(Direction op1, Integral op2)
    {
        return Direction(int8_t(op1) >> op2);
    }

    constexpr Direction operator&(Direction op1, Direction op2)
    {
        return Direction(int8_t(op1) & int8_t(op2));
    }

    constexpr Direction operator^(Direction op1, Direction op2)
    {
        return Direction(int8_t(op1) ^ int8_t(op2));
    }

    constexpr Direction operator|(Direction op1, Direction op2)
    {
        return Direction(int8_t(op1) ^ int8_t(op2));
    }

    template<typename Integral>
    inline Direction& operator+=(Direction& lhs, Integral rhs)
    {
        return lhs = Direction(int8_t(lhs) + rhs);
    }

    template<typename Integral>
    inline Direction& operator-=(Direction& lhs, Integral rhs)
    {
        return lhs = Direction(int8_t(lhs) - rhs);
    }

    template<typename Integral>
    inline Direction& operator*=(Direction& lhs, Integral rhs)
    {
        return lhs = Direction(int8_t(lhs) * rhs);
    }

    template<typename Integral>
    inline Direction& operator/=(Direction& lhs, Integral rhs)
    {
        return lhs = Direction(int8_t(lhs) / rhs);
    }

    template<typename Integral>
    inline Direction& operator%=(Direction& lhs, Integral rhs)
    {
        return lhs = Direction(int8_t(lhs) % rhs);
    }

    template<typename Integral>
    inline Direction& operator<<=(Direction& lhs, Integral rhs)
    {
        return lhs = Direction(int8_t(lhs) << rhs);
    }

    template<typename Integral>
    inline Direction& operator>>=(Direction& lhs, Integral rhs)
    {
        return lhs = Direction(int8_t(lhs) >> rhs);
    }

    template<typename Integral>
    inline Direction& operator&=(Direction& lhs, Integral rhs)
    {
        return lhs = Direction(int8_t(lhs) & rhs);
    }

    template<typename Integral>
    inline Direction& operator^=(Direction& lhs, Integral rhs)
    {
        return lhs = Direction(int8_t(lhs) ^ rhs);
    }

    template<typename Integral>
    inline Direction& operator|=(Direction& lhs, Integral rhs)
    {
        return lhs = Direction(int8_t(lhs) | rhs);
    }
};

#endif
