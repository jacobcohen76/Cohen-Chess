#ifndef COHEN_CHESS_TYPE_KEY_HPP_INCLUDED
#define COHEN_CHESS_TYPE_KEY_HPP_INCLUDED

#include <cstdint>

namespace cohen_chess::type::key
{
    using Key = uint64_t;

    enum KeyConstant : Key
    {
        kKeyNone    = 0x0000000000000000,
        kKeyAll     = 0xFFFFFFFFFFFFFFFF,
    };
}

namespace cohen_chess
{
    using type::key::Key;
    
    using type::key::kKeyNone;
    using type::key::kKeyAll;
}

#endif
