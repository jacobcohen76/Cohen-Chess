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

    constexpr Rank RelativeRank(Rank rank, Color side) noexcept
    {
        assert(kRank1 <= rank && rank < kRankNB);
        assert(side == kWhite || side == kBlack);
        return rank ^ (side * 0b111);
    }
}

namespace cohen
{
    using cohen::chess::type::rank::Rank;

    using cohen::chess::type::rank::kRank1;
    using cohen::chess::type::rank::kRank2;
    using cohen::chess::type::rank::kRank3;
    using cohen::chess::type::rank::kRank4;
    using cohen::chess::type::rank::kRank5;
    using cohen::chess::type::rank::kRank6;
    using cohen::chess::type::rank::kRank7;
    using cohen::chess::type::rank::kRank8;
    using cohen::chess::type::rank::kRankNB;

    using cohen::chess::type::rank::MirrorRank;
    using cohen::chess::type::rank::RelativeRank;
}

#endif
