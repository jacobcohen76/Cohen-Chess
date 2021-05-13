#ifndef COHEN_CHESS_TYPES_SQUARE_HPP_INCLUDED
#define COHEN_CHESS_TYPES_SQUARE_HPP_INCLUDED

#include <types/anti.hpp>
#include <types/diag.hpp>
#include <types/file.hpp>
#include <types/rank.hpp>

#include <algorithm>
#include <cstdint>

namespace cohen_chess
{
    typedef int8_t Square;

    enum : Square
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

    constexpr Square MakeSquare(Rank rank, File file)
    {
        return (rank << 3) | file;
    }

    constexpr Rank RankOf(Square sq)
    {
        return sq >> 3;
    }

    constexpr File FileOf(Square sq)
    {
        return sq & kH1;
    }

    constexpr Diag DiagOf(Square sq)
    {
        return RankOf(sq) - FileOf(sq) + kDiag8;
    }

    constexpr Anti AntiOf(Square sq)
    {
        return RankOf(sq) + FileOf(sq);
    }

    constexpr Square MirrorSquareRank(Square sq)
    {
        return sq ^ kA8;
    }

    constexpr Square MirrorSquareFile(Square sq)
    {
        return sq ^ kH1;
    }

    constexpr Square MirrorSquareDiag(Square sq)
    {
        return ((sq << 3) | (sq >> 3)) & kH8;
    }

    constexpr Square MirrorSquareAnti(Square sq)
    {
        return MirrorSquareDiag(sq) ^ kH8;
    }

    constexpr Square MirrorSquareRankFile(Square sq)
    {
        return sq ^ kH8;
    }

    constexpr Square RelativeSquare(Square sq, Color side)
    {
        return sq ^ (side * kH8);
    }

    constexpr Square RelativeSquareRank(Square sq, Color side)
    {
        return sq ^ (side * kA8);
    }

    constexpr Square RelativeSquareFile(Square sq, Color side)
    {
        return sq ^ (side * kH1);
    }

    constexpr int SquareRankDistance(Square sq1, Square sq2)
    {
        auto dist = RankOf(sq1) - RankOf(sq2);
        return (dist < 0) ? -dist : +dist;
    }

    constexpr int SquareFileDistance(Square sq1, Square sq2)
    {
        auto dist = FileOf(sq1) - FileOf(sq2);
        return (dist < 0) ? -dist : +dist;
    }

    constexpr int SquareManhattanDistance(Square sq1, Square sq2)
    {
        return SquareRankDistance(sq1, sq2) + SquareFileDistance(sq1, sq2);
    }

    constexpr bool IsNormalSquare(Square sq)
    {
        return 0 <= sq && sq < kSquareNB;
    }
}

#endif