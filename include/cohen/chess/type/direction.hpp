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
        kNorth         = +8,
        kEast          = +1,
        kSouth         = -kNorth,
        kWest          = -kEast,

        kNorthEast     =  kNorth + kEast,
        kSouthEast     =  kSouth + kEast,
        kSouthWest     =  kSouth + kWest,
        kNorthWest     =  kNorth + kWest,

        kNorthNorth    =  kNorth + kNorth,
        kEastEast      =  kEast  + kEast,
        kSouthSouth    =  kSouth + kSouth,
        kWestWest      =  kWest  + kWest,

        kDirectionNone = 0,
    };

    constexpr int Magnitude(Direction dir) noexcept
    {
        switch (dir)
        {
            case kNorth:         return 1;
            case kEast:          return 1;
            case kSouth:         return 1;
            case kWest:          return 1;

            case kNorthEast:     return 2;
            case kSouthEast:     return 2;
            case kSouthWest:     return 2;
            case kNorthWest:     return 2;

            case kNorthNorth:    return 2;
            case kEastEast:      return 2;
            case kSouthSouth:    return 2;
            case kWestWest:      return 2;

            default:             return 0;
        }
    }

    constexpr bool CanStep(Square sq, Direction step) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return IsNormalSquare(sq + step)
            && SquareDistance(sq, sq + step) == Magnitude(step);
    }

    constexpr std::array<std::array<int8_t, kSquareNB>, kSquareNB> kRayBetweenTable = []()
    {
        std::array<std::array<int8_t, kSquareNB>, kSquareNB> ray_between_table = {};
        for (Square from = kA1; from < kSquareNB; ++from)
        for (Square   to = kA1;   to < kSquareNB; ++to)
        {
            if (from != to)
            {
                if (OnSameRank(from, to)) ray_between_table[from][to] = from < to ? kEast      : kWest;
                if (OnSameFile(from, to)) ray_between_table[from][to] = from < to ? kNorth     : kSouth;
                if (OnSameDiag(from, to)) ray_between_table[from][to] = from < to ? kNorthEast : kSouthWest;
                if (OnSameAnti(from, to)) ray_between_table[from][to] = from < to ? kNorthWest : kSouthEast;
            }
        }
        return ray_between_table;
    }();

    constexpr Direction RayBetween(Square from, Square to) noexcept
    {
        assert(kA1 <= from && from < kSquareNB);
        assert(kA1 <= to   &&   to < kSquareNB);
        return kRayBetweenTable[from][to];
    }
}

namespace cohen::chess
{
    using cohen::chess::type::direction::Direction;
    using enum cohen::chess::type::direction::DirectionConstant;

    using cohen::chess::type::direction::RayBetween;
    using cohen::chess::type::direction::Magnitude;
    using cohen::chess::type::direction::CanStep;
}

#endif
