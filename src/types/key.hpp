#ifndef COHEN_CHESS_TYPES_KEY_HPP_INCLUDED
#define COHEN_CHESS_TYPES_KEY_HPP_INCLUDED

#include <cstdint>

namespace cohen_chess
{
    namespace key
    {
        using Key = uint64_t;

        enum KeyConstant : Key
        {
            kKeyZero    = 0x0000000000000000,
            kKeyAll     = 0xFFFFFFFFFFFFFFFF,
        };
    }

    using namespace key;
}

#endif