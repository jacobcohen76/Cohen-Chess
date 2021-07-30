#ifndef COHEN_CHESS_TYPE_KEY_HPP_INCLUDED
#define COHEN_CHESS_TYPE_KEY_HPP_INCLUDED

#include <cstdint>

namespace cohen::chess::type::key
{
    using Key = uint64_t;

    enum KeyConstant : Key
    {
        kKeyNone = 0x0000000000000000,
        kKeyAll  = 0xFFFFFFFFFFFFFFFF,
    };
}

namespace cohen::chess
{
    using cohen::chess::type::key::Key;
    using enum cohen::chess::type::key::KeyConstant;
}

#endif
