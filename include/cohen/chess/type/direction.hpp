#ifndef COHEN_CHESS_TYPE_DIRECTION_HPP_INCLUDED
#define COHEN_CHESS_TYPE_DIRECTION_HPP_INCLUDED

#include <array>
#include <cassert>
#include <cstdint>

#include <cohen/chess/type/square.hpp>

namespace cohen::chess::type::direction
{
    using Direction = int8_t;

    enum DirectionConstant : Direction
    {
        kNorth          = +8,
        kEast           = +1,
        kSouth          = -kNorth,
        kWest           = -kEast,

        kNorthEast      = kNorth + kEast,
        kSouthEast      = kSouth + kEast,
        kSouthWest      = kSouth + kWest,
        kNorthWest      = kNorth + kWest,

        kNorthNorth     = kNorth + kNorth,
        kEastEast       = kEast + kEast,
        kSouthSouth     = kSouth + kSouth,
        kWestWest       = kWest + kWest,

        kNorthNorthEast = kNorthNorth + kEast,
        kNorthNorthWest = kNorthNorth + kWest,
        kEastEastNorth  = kEastEast + kNorth,
        kEastEastSouth  = kEastEast + kSouth,
        kSouthSouthEast = kSouthSouth + kEast,
        kSouthSouthWest = kSouthSouth + kWest,
        kWestWestNorth  = kWestWest + kNorth,
        kWestWestSouth  = kWestWest + kSouth,

        kDirectionNone  = 0,
    };

    constexpr std::array<std::array<int8_t, kSquareNB>, kSquareNB> kRayBetweenTable = []()
    {
        std::array<std::array<int8_t, kSquareNB>, kSquareNB> ray_between_table = {};
        for (Square sq1 = kA1; sq1 < kSquareNB; ++sq1)
        {
            for (Square sq2 = kA1; sq2 < kSquareNB; ++sq2)
            {
                if (sq1 == sq2)                ray_between_table[sq1][sq2] = kDirectionNone;
                else if (OnSameRank(sq1, sq2)) ray_between_table[sq1][sq2] = (sq1 < sq2) ? kEast      : kWest;
                else if (OnSameFile(sq1, sq2)) ray_between_table[sq1][sq2] = (sq1 < sq2) ? kNorth     : kSouth;
                else if (OnSameDiag(sq1, sq2)) ray_between_table[sq1][sq2] = (sq1 < sq2) ? kNorthEast : kSouthWest;
                else if (OnSameAnti(sq1, sq2)) ray_between_table[sq1][sq2] = (sq1 < sq2) ? kNorthWest : kSouthEast;
            }
        }
        return ray_between_table;
    }();

    constexpr Direction RayBetween(Square sq1, Square sq2) noexcept
    {
        assert(kA1 <= sq1 && sq1 < kSquareNB);
        assert(kA1 <= sq2 && sq2 < kSquareNB);
        return kRayBetweenTable[sq1][sq2];
    }

    constexpr int Magnitude(Direction dir) noexcept
    {
        return SquareDistance(kE4, kE4 + dir);
    }

    constexpr bool CanStep(Square sq, Direction step) noexcept
    {
        return IsNormalSquare(sq)        &&
               IsNormalSquare(sq + step) &&
               SquareDistance(sq, sq + step) == Magnitude(step);
    }
}

namespace cohen::chess
{
    using cohen::chess::type::direction::Direction;

    using cohen::chess::type::direction::kNorth;
    using cohen::chess::type::direction::kEast;
    using cohen::chess::type::direction::kSouth;
    using cohen::chess::type::direction::kWest;
    using cohen::chess::type::direction::kNorthEast;
    using cohen::chess::type::direction::kSouthEast;
    using cohen::chess::type::direction::kSouthWest;
    using cohen::chess::type::direction::kNorthWest;
    using cohen::chess::type::direction::kNorthNorth;
    using cohen::chess::type::direction::kEastEast;
    using cohen::chess::type::direction::kSouthSouth;
    using cohen::chess::type::direction::kWestWest;
    using cohen::chess::type::direction::kNorthNorthEast;
    using cohen::chess::type::direction::kNorthNorthWest;
    using cohen::chess::type::direction::kEastEastNorth;
    using cohen::chess::type::direction::kEastEastSouth;
    using cohen::chess::type::direction::kSouthSouthEast;
    using cohen::chess::type::direction::kSouthSouthWest;
    using cohen::chess::type::direction::kWestWestNorth;
    using cohen::chess::type::direction::kWestWestSouth;
    using cohen::chess::type::direction::kDirectionNone;

    using cohen::chess::type::direction::RayBetween;
    using cohen::chess::type::direction::Magnitude;
    using cohen::chess::type::direction::CanStep;
};

#endif
