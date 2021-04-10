#ifndef COHEN_CHESS_TYPES_COLOR_H_INCLUDED
#define COHEN_CHESS_TYPES_COLOR_H_INCLUDED

#include <cstdint>

namespace cohen_chess
{
    typedef uint8_t Color;

    enum : Color
    {
        kWhite   = 0,
        kBlack   = 1,
        kColorNB = 2,
    };

    constexpr Color FlipColor(Color c)
    {
        return !c;
    }
}

#endif
