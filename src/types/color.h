#ifndef COHEN_CHESS_TYPES_COLOR_H_INCLUDED
#define COHEN_CHESS_TYPES_COLOR_H_INCLUDED

#include <cstdint>

namespace cohen_chess
{
    enum Color : uint8_t
    {
        kWhite   = 0,
        kBlack   = 1,
        kColorNB = 2,
    };

    constexpr Color FlipColor(Color c)
    {
        return Color(!uint8_t(c));
    }

    constexpr Color operator!(Color op)
    {
        return FlipColor(op);
    }
}

#endif
