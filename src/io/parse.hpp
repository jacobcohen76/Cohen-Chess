#ifndef COHEN_CHESS_IO_PARSE_HPP_INCLUDED
#define COHEN_CHESS_IO_PARSE_HPP_INCLUDED

#include <stdexcept>
#include <iostream>
#include <string>

namespace cohen_chess
{
    class ParseError : public std::runtime_error
    {
    public:
        using std::runtime_error::runtime_error;
    };

    template <typename CharT>
    struct Token
    {
        using Type = size_t;
        std::basic_string<CharT> str;
        Type type;
    };


}

#endif