#ifndef COHEN_CHESS_IO_PARSE_HPP_INCLUDED
#define COHEN_CHESS_IO_PARSE_HPP_INCLUDED

#include <stdexcept>
#include <iostream>
#include <string>

namespace cohen_chess::io::parse
{
    struct ParseError : public std::runtime_error
    {
        using std::runtime_error::runtime_error;
    };
}

namespace cohen_chess
{
    using io::parse::ParseError;
}

#endif