#ifndef COHEN_CHESS_TYPES_DIRECTION_H_INCLUDED
#define COHEN_CHESS_TYPES_DIRECTION_H_INCLUDED

#include "square.h"

#include <cstdint>

namespace cohen_chess
{
    typedef int8_t Direction;

    enum : Direction
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

    namespace direction
    {
        extern Direction kRayBetween[kSquareNB][kSquareNB];

        void InitRayBetween(Direction[kSquareNB][kSquareNB]);
        void Init();
    };

    inline Direction RayBetween(Square sq1, Square sq2)
    {
        return direction::kRayBetween[sq1][sq2];
    }

    constexpr int8_t Magnitude(Direction dir)
    {
        return SquareDistance(kE4, kE4 + dir);
    }

    constexpr bool CanStep(Square sq, Direction step)
    {
        return IsNormal(sq) && IsNormal(sq + step) && SquareDistance(sq, sq + step) == Magnitude(step);
    }
};

#endif
