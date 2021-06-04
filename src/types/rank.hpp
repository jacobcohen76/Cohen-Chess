#ifndef COHEN_CHESS_TYPES_RANK_HPP_INCLUDED
#define COHEN_CHESS_TYPES_RANK_HPP_INCLUDED

#include <cstdint>

#include <types/color.hpp>

namespace cohen_chess
{
    namespace rank
    {
        using Rank = int8_t;

        enum RankConstant : Rank
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

        constexpr Rank MirrorRank(Rank rank) noexcept
        {
            return rank ^ kRank8;
        }

        constexpr Rank RelativeRank(Rank rank, Color side) noexcept
        {
            return rank ^ (side * kRank8);
        }
    }

    using namespace rank;
}

#endif