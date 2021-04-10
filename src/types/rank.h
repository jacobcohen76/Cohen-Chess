#ifndef COHEN_CHESS_TYPES_RANK_H_INCLUDED
#define COHEN_CHESS_TYPES_RANK_H_INCLUDED

#include "color.h"

#include <cstdint>

namespace cohen_chess
{
    typedef int8_t Rank;

    enum : Rank
    {
        kRank1  = 0,
        kRank2  = 1,
        kRank3  = 2,
        kRank4  = 3,
        kRank5  = 4,
        kRank6  = 5,
        kRank7  = 6,
        kRank8  = 7,
        kRankNB = 8,
    };

    constexpr Rank MirrorRank(Rank r)
    {
        return Rank(r ^ kRank8);
    }

    constexpr Rank RelativeRank(Color side, Rank r)
    {
        return Rank(r ^ (side * kRank8));
    }
}

#endif