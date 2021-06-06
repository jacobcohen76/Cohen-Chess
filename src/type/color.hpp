#ifndef COHEN_CHESS_TYPE_COLOR_HPP_INCLUDED
#define COHEN_CHESS_TYPE_COLOR_HPP_INCLUDED

#include <cstdint>

namespace cohen_chess::type::color
{
    using Color = uint8_t;

    enum ColorConstant : Color
    {
        kWhite   = 0,
        kBlack   = 1,
        kColorNB = 2,
    };
}

namespace cohen_chess
{
    using type::color::Color;

    using type::color::kWhite;
    using type::color::kBlack;
    using type::color::kColorNB;
}

#endif