#ifndef COHEN_CHESS_TYPES_DIAG_HPP_INCLUDED
#define COHEN_CHESS_TYPES_DIAG_HPP_INCLUDED

#include <cstdint>

#include <types/color.hpp>

namespace cohen_chess
{
    namespace diag
    {
        using Diag = uint8_t;

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

    using namespace diag;
}

#endif
