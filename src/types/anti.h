#ifndef COHEN_CHESS_TYPES_ANTI_H_INCLUDED
#define COHEN_CHESS_TYPES_ANTI_H_INCLUDED

#include <cstdint>

namespace cohen_chess
{
    typedef uint8_t Anti;

    enum : Anti
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

    constexpr Anti MirroAnti(Anti a)
    {
        return Anti(kAntiF - a);
    }
}

#endif