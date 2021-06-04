#ifndef COHEN_CHESS_TYPES_COLOR_HPP_INCLUDED
#define COHEN_CHESS_TYPES_COLOR_HPP_INCLUDED

#include <cstdint>

namespace cohen_chess
{
    namespace color
    {
        using Color = uint8_t;

        enum ColorConstant : Color
        {
            kWhite   = 0,
            kBlack   = 1,
            kColorNB = 2,
        };
    }

    using namespace color;
}

#endif
