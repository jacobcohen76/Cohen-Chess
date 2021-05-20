#ifndef COHEN_CHESS_IO_PARSE_HPP_INCLUDED
#define COHEN_CHESS_IO_PARSE_HPP_INCLUDED

#include <iostream>
#include <string_view>

namespace cohen_chess
{
    template <typename CharT>
    struct Token
    {
        using Type = size_t;
        std::basic_string<CharT> str;
        Type type;
    };


}

#endif