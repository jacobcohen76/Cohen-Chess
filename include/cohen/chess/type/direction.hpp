#ifndef COHEN_CHESS_TYPE_DIRECTION_HPP_INCLUDED
#define COHEN_CHESS_TYPE_DIRECTION_HPP_INCLUDED

#include <array>
#include <cassert>
#include <cstdint>

#include <cohen/chess/type/square.hpp>

namespace cohen::chess::type::direction
{
    using Direction = int;

    enum DirectionConstant : Direction
    {
        kDirNone    =  0,

        kNorth      =  1,
        kEast       =  2,
        kSouth      =  3,
        kWest       =  4,

        kNorthEast  =  5,
        kSouthEast  =  6,
        kSouthWest  =  7,
        kNorthWest  =  8,

        kNorthNorth =  9,
        kEastEast   = 10,
        kSouthSouth = 11,
        kWestWest   = 12,

        kDirNB      = 13,
    };

    inline constexpr std::array<std::array<Direction, kSquareNB>, kSquareNB> kRayBetweenTable = []()
    {
        std::array<std::array<Direction, kSquareNB>, kSquareNB> ray_table = {};
        for (Square from = kA1; from < kSquareNB; ++from)
        for (Square   to = kA1; to   < kSquareNB; ++to)
        {
            if (from != to)
            {
                if (OnSameRank(from, to))
                    ray_table[from][to] = from < to ? kEast : kWest;
                if (OnSameFile(from, to))
                    ray_table[from][to] = from < to ? kNorth : kSouth;
                if (OnSameDiag(from, to))
                    ray_table[from][to] = from < to ? kNorthEast : kSouthWest;
                if (OnSameAnti(from, to))
                    ray_table[from][to] = from < to ? kNorthWest : kSouthEast;
            }
        }
        return ray_table;
    }();

    constexpr Direction RayBetween(Square from, Square to) noexcept
    {
        assert(kA1 <= from && from < kSquareNB);
        assert(kA1 <= to   && to   < kSquareNB);
        return kRayBetweenTable[from][to];
    }

    inline constexpr std::array<Square, kDirNB> kSquareVectorTable = []()
    {
        std::array<Square, kDirNB> vec_table = {};
        vec_table[kDirNone]    =  0;
        vec_table[kNorth]      = +8;
        vec_table[kEast]       = +1;
        vec_table[kSouth]      = -vec_table[kNorth];
        vec_table[kWest]       = -vec_table[kEast];
        vec_table[kNorthEast]  =  vec_table[kNorth] + vec_table[kEast];
        vec_table[kSouthEast]  =  vec_table[kSouth] + vec_table[kEast];
        vec_table[kSouthWest]  =  vec_table[kSouth] + vec_table[kWest];
        vec_table[kNorthWest]  =  vec_table[kNorth] + vec_table[kWest];
        vec_table[kNorthNorth] =  vec_table[kNorth] + vec_table[kNorth];
        vec_table[kEastEast]   =  vec_table[kEast]  + vec_table[kEast];
        vec_table[kSouthSouth] =  vec_table[kSouth] + vec_table[kSouth];
        vec_table[kWestWest]   =  vec_table[kWest]  + vec_table[kWest];
        return vec_table;
    }();

    constexpr Square SquareVector(Direction dir) noexcept
    {
        assert(kDirNone <= dir && dir < kDirNB);
        return kSquareVectorTable[dir];
    }

    inline constexpr std::array<Square, kDirNB> kMagnitudeTable = []()
    {
        std::array<Square, kDirNB> mag_table = {};
        mag_table[kDirNone]    = 0;
        mag_table[kNorth]      = 1;
        mag_table[kEast]       = 1;
        mag_table[kSouth]      = 1;
        mag_table[kWest]       = 1;
        mag_table[kNorthEast]  = 2;
        mag_table[kSouthEast]  = 2;
        mag_table[kSouthWest]  = 2;
        mag_table[kNorthWest]  = 2;
        mag_table[kNorthNorth] = 2;
        mag_table[kEastEast]   = 2;
        mag_table[kSouthSouth] = 2;
        mag_table[kWestWest]   = 2;
        return mag_table;
    }();

    constexpr Square Magnitude(Direction dir) noexcept
    {
        assert(kDirNone <= dir && dir < kDirNB);
        return kMagnitudeTable[dir];
    }

    constexpr bool CanStep(Square from, Direction step) noexcept
    {
        assert(kA1 <= from && from < kSquareNB);
        assert(kDirNone <= step && step < kDirNB);
        Square vec = SquareVector(step);
        Square to  = from + vec;
        return step != kDirNone
            && IsNormalSquare(to)
            && SquareDistance(from, to) == Magnitude(step);
    }
}

namespace cohen::chess
{
    using cohen::chess::type::direction::Direction;
    using enum cohen::chess::type::direction::DirectionConstant;

    using cohen::chess::type::direction::RayBetween;
    using cohen::chess::type::direction::SquareVector;
    using cohen::chess::type::direction::Magnitude;
    using cohen::chess::type::direction::CanStep;
}

#endif