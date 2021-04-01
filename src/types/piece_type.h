#ifndef COHEN_CHESS_TYPES_PIECE_TYPE_H_INCLUDED
#define COHEN_CHESS_TYPES_PIECE_TYPE_H_INCLUDED

#include <cstdint>

namespace cohen_chess
{
    enum PieceType : uint8_t
    {
        kPieceTypeNone  = 0,
        kPawn           = 1,
        kKnight         = 2,
        kBishop         = 3,
        kRook           = 4,
        kQueen          = 5,
        kKing           = 6,
        kPieceTypeAll   = 7,
        kPieceTypeNB    = 8,
    };

    constexpr PieceType& operator++(PieceType& op)
    {
        return op = PieceType(uint8_t(op) + 1);
    }

    constexpr PieceType& operator--(PieceType& op)
    {
        return op = PieceType(uint8_t(op) - 1);
    }

    constexpr PieceType operator+(PieceType op)
    {
        return PieceType(+uint8_t(op));
    }

    constexpr PieceType operator-(PieceType op)
    {
        return PieceType(-uint8_t(op));
    }

    constexpr PieceType operator~(PieceType op)
    {
        return PieceType(~uint8_t(op));
    }

    template<typename Integral>
    constexpr PieceType operator<<(PieceType op1, Integral op2)
    {
        return PieceType(uint8_t(op1) << op2);
    }

    template<typename Integral>
    constexpr PieceType operator>>(PieceType op1, Integral op2)
    {
        return PieceType(uint8_t(op1) >> op2);
    }

    constexpr PieceType operator&(PieceType op1, PieceType op2)
    {
        return PieceType(uint8_t(op1) & uint8_t(op2));
    }

    constexpr PieceType operator^(PieceType op1, PieceType op2)
    {
        return PieceType(uint8_t(op1) ^ uint8_t(op2));
    }

    constexpr PieceType operator|(PieceType op1, PieceType op2)
    {
        return PieceType(uint8_t(op1) ^ uint8_t(op2));
    }

    template<typename Integral>
    constexpr PieceType& operator+=(PieceType& lhs, Integral rhs)
    {
        return lhs = PieceType(uint8_t(lhs) + rhs);
    }

    template<typename Integral>
    constexpr PieceType& operator-=(PieceType& lhs, Integral rhs)
    {
        return lhs = PieceType(uint8_t(lhs) - rhs);
    }

    template<typename Integral>
    constexpr PieceType& operator*=(PieceType& lhs, Integral rhs)
    {
        return lhs = PieceType(uint8_t(lhs) * rhs);
    }

    template<typename Integral>
    constexpr PieceType& operator/=(PieceType& lhs, Integral rhs)
    {
        return lhs = PieceType(uint8_t(lhs) / rhs);
    }

    template<typename Integral>
    constexpr PieceType& operator%=(PieceType& lhs, Integral rhs)
    {
        return lhs = PieceType(uint8_t(lhs) % rhs);
    }

    template<typename Integral>
    constexpr PieceType& operator<<=(PieceType& lhs, Integral rhs)
    {
        return lhs = PieceType(uint8_t(lhs) << rhs);
    }

    template<typename Integral>
    constexpr PieceType& operator>>=(PieceType& lhs, Integral rhs)
    {
        return lhs = PieceType(uint8_t(lhs) >> rhs);
    }

    template<typename Integral>
    constexpr PieceType& operator&=(PieceType& lhs, Integral rhs)
    {
        return lhs = PieceType(uint8_t(lhs) & rhs);
    }

    template<typename Integral>
    constexpr PieceType& operator^=(PieceType& lhs, Integral rhs)
    {
        return lhs = PieceType(uint8_t(lhs) ^ rhs);
    }

    template<typename Integral>
    constexpr PieceType& operator|=(PieceType& lhs, Integral rhs)
    {
        return lhs = PieceType(uint8_t(lhs) | rhs);
    }
}

#endif