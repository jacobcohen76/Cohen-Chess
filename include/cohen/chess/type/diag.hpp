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

    constexpr Diag RelativeDiag(Diag diag, Color side) noexcept
    {
        assert(kDiag1 <= diag && diag < kDiagNB);
        assert(side == kWhite || side == kBlack);
        return side ? diag : MirrorDiag(diag);
    }
}

namespace cohen::chess
{
    using cohen::chess::type::diag::Diag;

    using cohen::chess::type::diag::kDiag1;
    using cohen::chess::type::diag::kDiag2;
    using cohen::chess::type::diag::kDiag3;
    using cohen::chess::type::diag::kDiag4;
    using cohen::chess::type::diag::kDiag5;
    using cohen::chess::type::diag::kDiag6;
    using cohen::chess::type::diag::kDiag7;
    using cohen::chess::type::diag::kDiag8;
    using cohen::chess::type::diag::kDiag9;
    using cohen::chess::type::diag::kDiagA;
    using cohen::chess::type::diag::kDiagB;
    using cohen::chess::type::diag::kDiagC;
    using cohen::chess::type::diag::kDiagD;
    using cohen::chess::type::diag::kDiagE;
    using cohen::chess::type::diag::kDiagF;
    using cohen::chess::type::diag::kDiagNB;

    using cohen::chess::type::diag::MirrorDiag;
    using cohen::chess::type::diag::RelativeDiag;
}

#endif
