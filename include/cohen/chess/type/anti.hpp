#ifndef COHEN_CHESS_TYPE_ANTI_HPP_INCLUDED
#define COHEN_CHESS_TYPE_ANTI_HPP_INCLUDED

#include <cassert>
#include <cstdint>

#include <cohen/chess/type/color.hpp>

namespace cohen::chess::type::anti
{
    using Anti = int;

    enum AntiConstant : Anti
    {
        kAnti1  =  0,
        kAnti2  =  1,
        kAnti3  =  2,
        kAnti4  =  3,
        kAnti5  =  4,
        kAnti6  =  5,
        kAnti7  =  6,
        kAnti8  =  7,
        kAnti9  =  8,
        kAntiA  =  9,
        kAntiB  = 10,
        kAntiC  = 11,
        kAntiD  = 12,
        kAntiE  = 13,
        kAntiF  = 14,
        kAntiNB = 15,
    };

    constexpr Anti MirrorAnti(Anti anti) noexcept
    {
        assert(kAnti1 <= anti && anti < kAntiNB);
        return kAntiF - anti;
    }

    constexpr Anti RelativeAnti(Color side, Anti anti) noexcept
    {
        assert(side == kWhite || side == kBlack);
        assert(kAnti1 <= anti && anti < kAntiNB);
        return side ? anti : MirrorAnti(anti);
    }
}

namespace cohen::chess
{
    using cohen::chess::type::anti::Anti;
    using enum cohen::chess::type::anti::AntiConstant;

    using cohen::chess::type::anti::MirrorAnti;
    using cohen::chess::type::anti::RelativeAnti;
}

#endif