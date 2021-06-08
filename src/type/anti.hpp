#ifndef COHEN_CHESS_TYPE_ANTI_HPP_INCLUDED
#define COHEN_CHESS_TYPE_ANTI_HPP_INCLUDED

#include <cassert>
#include <cstdint>

#include <type/color.hpp>

namespace cohen_chess::type::anti
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

namespace cohen_chess
{
    using type::anti::Anti;

    using type::anti::kAnti1;
    using type::anti::kAnti2;
    using type::anti::kAnti3;
    using type::anti::kAnti4;
    using type::anti::kAnti5;
    using type::anti::kAnti6;
    using type::anti::kAnti7;
    using type::anti::kAnti8;
    using type::anti::kAnti9;
    using type::anti::kAntiA;
    using type::anti::kAntiB;
    using type::anti::kAntiC;
    using type::anti::kAntiD;
    using type::anti::kAntiE;
    using type::anti::kAntiF;
    using type::anti::kAntiNB;

    using type::anti::MirrorAnti;
    using type::anti::RelativeAnti;
}

#endif