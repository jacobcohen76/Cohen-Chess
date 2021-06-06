#ifndef COHEN_CHESS_TYPE_ANTI_HPP_INCLUDED
#define COHEN_CHESS_TYPE_ANTI_HPP_INCLUDED

#include <cstdint>

#include <type/color.hpp>

namespace cohen_chess::anti
{
    using Anti = uint8_t;

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
        return kAntiF - anti;
    }

    constexpr Anti RelativeAnti(Anti anti, Color side) noexcept
    {
        return side ? anti : MirrorAnti(anti);
    }
}

namespace cohen_chess
{
    using anti::Anti;

    using anti::kAnti1;
    using anti::kAnti2;
    using anti::kAnti3;
    using anti::kAnti4;
    using anti::kAnti5;
    using anti::kAnti6;
    using anti::kAnti7;
    using anti::kAnti8;
    using anti::kAnti9;
    using anti::kAntiA;
    using anti::kAntiB;
    using anti::kAntiC;
    using anti::kAntiD;
    using anti::kAntiE;
    using anti::kAntiF;
    using anti::kAntiNB;

    using anti::MirrorAnti;
    using anti::RelativeAnti;
}

#endif