#ifndef COHEN_CHESS_TYPE_RANK_HPP_INCLUDED
#define COHEN_CHESS_TYPE_RANK_HPP_INCLUDED

#include <cassert>
#include <cstdint>

#include <type/color.hpp>

namespace cohen_chess::type::rank
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
        assert(kRank1 <= rank && rank < kRankNB);
        return rank ^ 0b111;
    }

    constexpr Rank RelativeRank(Rank rank, Color side) noexcept
    {
        assert(kRank1 <= rank && rank < kRankNB);
        assert(side == kWhite || side == kBlack);
        return rank ^ (side * 0b111);
    }
}

namespace cohen_chess
{
    using type::rank::Rank;

    using type::rank::kRank1;
    using type::rank::kRank2;
    using type::rank::kRank3;
    using type::rank::kRank4;
    using type::rank::kRank5;
    using type::rank::kRank6;
    using type::rank::kRank7;
    using type::rank::kRank8;
    using type::rank::kRankNB;

    using type::rank::MirrorRank;
    using type::rank::RelativeRank;
}

#endif