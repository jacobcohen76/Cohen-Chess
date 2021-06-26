#ifndef COHEN_TYPE_KEY_HPP_INCLUDED
#define COHEN_TYPE_KEY_HPP_INCLUDED

#include <cstdint>

namespace cohen::type::key
{
    using Key = uint64_t;

    enum KeyConstant : Key
    {
        kKeyNone    = 0x0000000000000000,
        kKeyAll     = 0xFFFFFFFFFFFFFFFF,
    };
}

namespace cohen
{
    using type::key::Key;
    
    using type::key::kKeyNone;
    using type::key::kKeyAll;
}

#endif
