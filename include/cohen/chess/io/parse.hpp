#ifndef COHEN_IO_PARSE_HPP_INCLUDED
#define COHEN_IO_PARSE_HPP_INCLUDED

#include <stdexcept>
#include <iostream>
#include <string>

namespace cohen::chess::io::parse
{
    struct ParseError : public std::runtime_error
    {
        using std::runtime_error::runtime_error;
    };
}

namespace cohen::chess
{
    using cohen::chess::io::parse::ParseError;
}

#endif