#ifndef COHEN_CHESS_TYPE_DIAG_HPP_INCLUDED
#define COHEN_CHESS_TYPE_DIAG_HPP_INCLUDED

#include <cstdint>

#include <type/color.hpp>

namespace cohen_chess::type::diag
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
        return kDiagF - diag;
    }

    constexpr Diag RelativeDiag(Diag diag, Color side) noexcept
    {
        return side ? diag : MirrorDiag(diag);
    }
}

namespace cohen_chess
{
    using type::diag::Diag;

    using type::diag::kDiag1;
    using type::diag::kDiag2;
    using type::diag::kDiag3;
    using type::diag::kDiag4;
    using type::diag::kDiag5;
    using type::diag::kDiag6;
    using type::diag::kDiag7;
    using type::diag::kDiag8;
    using type::diag::kDiag9;
    using type::diag::kDiagA;
    using type::diag::kDiagB;
    using type::diag::kDiagC;
    using type::diag::kDiagD;
    using type::diag::kDiagE;
    using type::diag::kDiagF;
    using type::diag::kDiagNB;

    using type::diag::MirrorDiag;
    using type::diag::RelativeDiag;
}

#endif
