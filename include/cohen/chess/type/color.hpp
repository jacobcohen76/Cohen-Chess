#ifndef COHEN_CHESS_TYPE_COLOR_HPP_INCLUDED
#define COHEN_CHESS_TYPE_COLOR_HPP_INCLUDED

#include <cstdint>

namespace cohen::chess::type::color
{
    using Color = uint8_t;

    enum ColorConstant : Color
    {
        kWhite   = 0,
        kBlack   = 1,
        kColorNB = 2,
    };
}

namespace cohen::chess
{
    using cohen::chess::type::color::Color;

    using cohen::chess::type::color::kWhite;
    using cohen::chess::type::color::kBlack;
    using cohen::chess::type::color::kColorNB;
}

#endif
