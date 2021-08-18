#ifndef COHEN_CHESS_TYPE_RANK_HPP_INCLUDED
#define COHEN_CHESS_TYPE_RANK_HPP_INCLUDED

#include <cassert>
#include <cstdint>

#include <cohen/chess/type/color.hpp>

namespace cohen::chess::type::rank
{
    using Rank = int;

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

    constexpr Rank RelativeRank(Color side, Rank rank) noexcept
    {
        assert(side == kWhite || side == kBlack);
        assert(kRank1 <= rank && rank < kRankNB);
        return rank ^ (side * 0b111);
    }
}

namespace cohen
{
    using cohen::chess::type::rank::Rank;
    using enum cohen::chess::type::rank::RankConstant;

    using cohen::chess::type::rank::MirrorRank;
    using cohen::chess::type::rank::RelativeRank;
}

#endif