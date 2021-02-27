#ifndef COHEN_CHESS_TYPES_MOVE_H_INCLUDED
#define COHEN_CHESS_TYPES_MOVE_H_INCLUDED

#include "move_type.h"
#include "piece_type.h"

#include <cstdint>

namespace cohen_chess
{
    enum Move : uint16_t
    {
        kMoveNone = 0x0000,
        kMoveNull = 0xFFFF,
    };

    constexpr Move MakeMove(Square from, Square to)
    {
        return Move(uint16_t(from) | (uint16_t(to) << 6));
    }

    constexpr Move MakeMove(MoveType type, Square from, Square to)
    {
        return Move(uint16_t(type << 12) | uint16_t(MakeMove(from, to)));
    }

    constexpr Square FromSquare(Move move)
    {
        return Square(uint16_t(move) & 0x3F);
    }

    constexpr Square ToSquare(Move move)
    {
        return Square((uint16_t(move) >> 6) & 0x3F);
    }

    constexpr MoveType TypeOf(Move move)
    {
        return MoveType(uint16_t(move) & 0xF000);
    }

    constexpr PieceType PromotedTo(Move move)
    {
        return PieceType(((uint16_t(move) >> 12) & 0x3) + kKnight);
    }

    inline Move& operator++(Move& op)
    {
        return op = Move(uint8_t(op) + 1);
    }

    inline Move& operator--(Move& op)
    {
        return op = Move(uint8_t(op) - 1);
    }

    constexpr Move operator+(Move op)
    {
        return Move(+uint8_t(op));
    }

    constexpr Move operator-(Move op)
    {
        return Move(-uint8_t(op));
    }

    constexpr Move operator~(Move op)
    {
        return Move(~uint8_t(op));
    }

    template<typename Integral>
    constexpr Move operator<<(Move op1, Integral op2)
    {
        return Move(uint8_t(op1) << op2);
    }

    template<typename Integral>
    constexpr Move operator>>(Move op1, Integral op2)
    {
        return Move(uint8_t(op1) >> op2);
    }

    constexpr Move operator&(Move op1, Move op2)
    {
        return Move(uint8_t(op1) & uint8_t(op2));
    }

    constexpr Move operator^(Move op1, Move op2)
    {
        return Move(uint8_t(op1) ^ uint8_t(op2));
    }

    constexpr Move operator|(Move op1, Move op2)
    {
        return Move(uint8_t(op1) ^ uint8_t(op2));
    }

    template<typename Integral>
    inline Move& operator+=(Move& lhs, Integral rhs)
    {
        return lhs = Move(uint8_t(lhs) + rhs);
    }

    template<typename Integral>
    inline Move& operator-=(Move& lhs, Integral rhs)
    {
        return lhs = Move(uint8_t(lhs) - rhs);
    }

    template<typename Integral>
    inline Move& operator*=(Move& lhs, Integral rhs)
    {
        return lhs = Move(uint8_t(lhs) * rhs);
    }

    template<typename Integral>
    inline Move& operator/=(Move& lhs, Integral rhs)
    {
        return lhs = Move(uint8_t(lhs) / rhs);
    }

    template<typename Integral>
    inline Move& operator%=(Move& lhs, Integral rhs)
    {
        return lhs = Move(uint8_t(lhs) % rhs);
    }

    template<typename Integral>
    inline Move& operator<<=(Move& lhs, Integral rhs)
    {
        return lhs = Move(uint8_t(lhs) << rhs);
    }

    template<typename Integral>
    inline Move& operator>>=(Move& lhs, Integral rhs)
    {
        return lhs = Move(uint8_t(lhs) >> rhs);
    }

    template<typename Integral>
    inline Move& operator&=(Move& lhs, Integral rhs)
    {
        return lhs = Move(uint8_t(lhs) & rhs);
    }

    template<typename Integral>
    inline Move& operator^=(Move& lhs, Integral rhs)
    {
        return lhs = Move(uint8_t(lhs) ^ rhs);
    }

    template<typename Integral>
    inline Move& operator|=(Move& lhs, Integral rhs)
    {
        return lhs = Move(uint8_t(lhs) | rhs);
    }
};

#endif