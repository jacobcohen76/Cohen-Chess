#ifndef COHEN_CHESS_TYPES_KEY_HPP_INCLUDED
#define COHEN_CHESS_TYPES_KEY_HPP_INCLUDED

#include <cstdint>

namespace cohen_chess
{
    typedef uint64_t Key;

    enum : Key
    {
        kKeyZero    = 0x0000000000000000,
        kKeyAll     = 0xFFFFFFFFFFFFFFFF,
    };
}

#endif