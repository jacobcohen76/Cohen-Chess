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

    constexpr Anti RelativeAnti(Anti anti, Color side) noexcept
    {
        assert(kAnti1 <= anti && anti < kAntiNB);
        assert(side == kWhite || side == kBlack);
        return side ? anti : MirrorAnti(anti);
    }
}

namespace cohen::chess
{
    using cohen::chess::type::anti::Anti;

    using cohen::chess::type::anti::kAnti1;
    using cohen::chess::type::anti::kAnti2;
    using cohen::chess::type::anti::kAnti3;
    using cohen::chess::type::anti::kAnti4;
    using cohen::chess::type::anti::kAnti5;
    using cohen::chess::type::anti::kAnti6;
    using cohen::chess::type::anti::kAnti7;
    using cohen::chess::type::anti::kAnti8;
    using cohen::chess::type::anti::kAnti9;
    using cohen::chess::type::anti::kAntiA;
    using cohen::chess::type::anti::kAntiB;
    using cohen::chess::type::anti::kAntiC;
    using cohen::chess::type::anti::kAntiD;
    using cohen::chess::type::anti::kAntiE;
    using cohen::chess::type::anti::kAntiF;
    using cohen::chess::type::anti::kAntiNB;

    using cohen::chess::type::anti::MirrorAnti;
    using cohen::chess::type::anti::RelativeAnti;
}

#endif
