#ifndef COHEN_CHESS_TYPES_DIRECTION_HPP_INCLUDED
#define COHEN_CHESS_TYPES_DIRECTION_HPP_INCLUDED

#include <array>
#include <cstdint>

#include <types/square.hpp>

namespace cohen_chess
{
    namespace direction
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

        constexpr std::array<std::array<int, kSquareNB>, kSquareNB> kRayBetweenTable = []
        {
            std::array<std::array<int, kSquareNB>, kSquareNB> ray_between_table = {};
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

    using direction::Direction;
    using enum direction::DirectionConstant;
    using direction::RayBetween;
    using direction::Magnitude;
    using direction::CanStep;
};

#endif
