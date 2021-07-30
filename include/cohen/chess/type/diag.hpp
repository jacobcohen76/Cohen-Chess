#ifndef COHEN_CHESS_TYPE_DIAG_HPP_INCLUDED
#define COHEN_CHESS_TYPE_DIAG_HPP_INCLUDED

#include <cassert>
#include <cstdint>

#include <cohen/chess/type/color.hpp>

namespace cohen::chess::type::diag
{
    using Diag = int;

    enum DiagConstant : Diag
    {
        kDiag1  =  0,
        kDiag2  =  1,
        kDiag3  =  2,
        kDiag4  =  3,
        kDiag5  =  4,
        kDiag6  =  5,
        kDiag7  =  6,
        kDiag8  =  7,
        kDiag9  =  8,
        kDiagA  =  9,
        kDiagB  = 10,
        kDiagC  = 11,
        kDiagD  = 12,
        kDiagE  = 13,
        kDiagF  = 14,
        kDiagNB = 15,
    };

    constexpr Diag MirrorDiag(Diag diag) noexcept
    {
        assert(kDiag1 <= diag && diag < kDiagNB);
        return kDiagF - diag;
    }

    constexpr Diag RelativeDiag(Color side, Diag diag) noexcept
    {
        assert(side == kWhite || side == kBlack);
        assert(kDiag1 <= diag && diag < kDiagNB);
        return side ? diag : MirrorDiag(diag);
    }
}

namespace cohen::chess
{
    using cohen::chess::type::diag::Diag;
    using enum cohen::chess::type::diag::DiagConstant;

    using cohen::chess::type::diag::MirrorDiag;
    using cohen::chess::type::diag::RelativeDiag;
}

#endif
