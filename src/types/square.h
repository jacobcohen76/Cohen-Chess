#ifndef COHEN_CHESS_TYPES_SQUARE_H_INCLUDED
#define COHEN_CHESS_TYPES_SQUARE_H_INCLUDED

#include "anti.h"
#include "diag.h"
#include "file.h"
#include "rank.h"

#include <algorithm>
#include <cstdint>

namespace cohen_chess
{
    enum Square : int8_t
    {
        kA1, kB1, kC1, kD1, kE1, kF1, kG1, kH1,
        kA2, kB2, kC2, kD2, kE2, kF2, kG2, kH2,
        kA3, kB3, kC3, kD3, kE3, kF3, kG3, kH3,
        kA4, kB4, kC4, kD4, kE4, kF4, kG4, kH4,
        kA5, kB5, kC5, kD5, kE5, kF5, kG5, kH5,
        kA6, kB6, kC6, kD6, kE6, kF6, kG6, kH6,
        kA7, kB7, kC7, kD7, kE7, kF7, kG7, kH7,
        kA8, kB8, kC8, kD8, kE8, kF8, kG8, kH8,
        kSquareNone = 64,
        kSquareNB   = 64,
    };

    constexpr Square MakeSquare(Rank r, File f)
    {
        return Square((r << 3) | f);
    }

    constexpr Square MakeSquare(File f, Rank r)
    {
        return MakeSquare(r, f);
    }

    constexpr Rank RankOf(Square sq)
    {
        return Rank(sq >> 3);
    }

    constexpr File FileOf(Square sq)
    {
        return File(sq & kH1);
    }

    constexpr Diag DiagOf(Square sq)
    {
        return Diag(RankOf(sq) - FileOf(sq) + kDiag8);
    }

    constexpr Anti AntiOf(Square sq)
    {
        return Anti(RankOf(sq) + FileOf(sq));
    }

    constexpr Square MirrorRank(Square sq)
    {
        return Square(sq ^ kA8);
    }

    constexpr Square MirrorFile(Square sq)
    {
        return Square(sq ^ kH1);
    }

    constexpr Square MirrorDiag(Square sq)
    {
        return Square(((sq << 3) | (sq >> 3)) & kH8);
    }

    constexpr Square MirrorAnti(Square sq)
    {
        return Square(MirrorDiag(sq) ^ kH8);
    }

    constexpr Square MirrorRankFile(Square sq)
    {
        return Square(sq ^ kH8);
    }

    constexpr Square RelativeSquare(Color side, Square sq)
    {
        return Square(sq ^ (side * kH8));
    }

    constexpr Square RelativeRank(Color side, Square sq)
    {
        return Square(sq ^ (side * kA8));
    }

    constexpr Square RelativeFile(Color side, Square sq)
    {
        return Square(sq ^ (side * kH1));
    }

    constexpr bool IsNormal(Square sq)
    {
        return kA1 <= sq && sq < kSquareNB;
    }

    constexpr int8_t RankDistance(Square sq1, Square sq2)
    {
        return std::abs(RankOf(sq1) - RankOf(sq2));
    }

    constexpr int8_t FileDistance(Square sq1, Square sq2)
    {
        return std::abs(FileOf(sq1) - FileOf(sq2));
    }

    constexpr int8_t SquareDistance(Square sq1, Square sq2)
    {
        return RankDistance(sq1, sq2) + FileDistance(sq1, sq2);
    }

    constexpr Square& operator++(Square& op)
    {
        return op = Square(int8_t(op) + 1);
    }

    constexpr Square& operator--(Square& op)
    {
        return op = Square(int8_t(op) - 1);
    }

    constexpr Square operator+(Square op)
    {
        return Square(+int8_t(op));
    }

    constexpr Square operator-(Square op)
    {
        return Square(-int8_t(op));
    }

    constexpr Square operator~(Square op)
    {
        return Square(~int8_t(op));
    }

    template<typename Integral>
    constexpr Square operator<<(Square op1, Integral op2)
    {
        return Square(int8_t(op1) << op2);
    }

    template<typename Integral>
    constexpr Square operator>>(Square op1, Integral op2)
    {
        return Square(int8_t(op1) >> op2);
    }

    constexpr Square operator&(Square op1, Square op2)
    {
        return Square(int8_t(op1) & int8_t(op2));
    }

    constexpr Square operator^(Square op1, Square op2)
    {
        return Square(int8_t(op1) ^ int8_t(op2));
    }

    constexpr Square operator|(Square op1, Square op2)
    {
        return Square(int8_t(op1) ^ int8_t(op2));
    }

    template<typename Integral>
    constexpr Square& operator+=(Square& lhs, Integral rhs)
    {
        return lhs = Square(int8_t(lhs) + rhs);
    }

    template<typename Integral>
    constexpr Square& operator-=(Square& lhs, Integral rhs)
    {
        return lhs = Square(int8_t(lhs) - rhs);
    }

    template<typename Integral>
    constexpr Square& operator*=(Square& lhs, Integral rhs)
    {
        return lhs = Square(int8_t(lhs) * rhs);
    }

    template<typename Integral>
    constexpr Square& operator/=(Square& lhs, Integral rhs)
    {
        return lhs = Square(int8_t(lhs) / rhs);
    }

    template<typename Integral>
    constexpr Square& operator%=(Square& lhs, Integral rhs)
    {
        return lhs = Square(int8_t(lhs) % rhs);
    }

    template<typename Integral>
    constexpr Square& operator<<=(Square& lhs, Integral rhs)
    {
        return lhs = Square(int8_t(lhs) << rhs);
    }

    template<typename Integral>
    constexpr Square& operator>>=(Square& lhs, Integral rhs)
    {
        return lhs = Square(int8_t(lhs) >> rhs);
    }

    template<typename Integral>
    constexpr Square& operator&=(Square& lhs, Integral rhs)
    {
        return lhs = Square(int8_t(lhs) & rhs);
    }

    template<typename Integral>
    constexpr Square& operator^=(Square& lhs, Integral rhs)
    {
        return lhs = Square(int8_t(lhs) ^ rhs);
    }

    template<typename Integral>
    constexpr Square& operator|=(Square& lhs, Integral rhs)
    {
        return lhs = Square(int8_t(lhs) | rhs);
    }
}

#endif