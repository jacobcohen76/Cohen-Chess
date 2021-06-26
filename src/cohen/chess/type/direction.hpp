#ifndef COHEN_TYPE_DIRECTION_HPP_INCLUDED
#define COHEN_TYPE_DIRECTION_HPP_INCLUDED

#include <array>
#include <cassert>
#include <cstdint>

#include <type/square.hpp>

namespace cohen::type::direction
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

namespace cohen
{
    using type::direction::Direction;

    using type::direction::kNorth;
    using type::direction::kEast;
    using type::direction::kSouth;
    using type::direction::kWest;
    using type::direction::kNorthEast;
    using type::direction::kSouthEast;
    using type::direction::kSouthWest;
    using type::direction::kNorthWest;
    using type::direction::kNorthNorth;
    using type::direction::kEastEast;
    using type::direction::kSouthSouth;
    using type::direction::kWestWest;
    using type::direction::kNorthNorthEast;
    using type::direction::kNorthNorthWest;
    using type::direction::kEastEastNorth;
    using type::direction::kEastEastSouth;
    using type::direction::kSouthSouthEast;
    using type::direction::kSouthSouthWest;
    using type::direction::kWestWestNorth;
    using type::direction::kWestWestSouth;
    using type::direction::kDirectionNone;

    using type::direction::RayBetween;
    using type::direction::Magnitude;
    using type::direction::CanStep;
};

#endif
