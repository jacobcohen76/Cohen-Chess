#ifndef COHEN_CHESS_TYPES_FILE_HPP_INCLUDED
#define COHEN_CHESS_TYPES_FILE_HPP_INCLUDED

#include <types/color.hpp>

#include <cstdint>

namespace cohen_chess
{
    typedef int8_t File;

    enum : File
    {
        kFileA  = 0,
        kFileB  = 1,
        kFileC  = 2,
        kFileD  = 3,
        kFileE  = 4,
        kFileF  = 5,
        kFileG  = 6,
        kFileH  = 7,
        kFileNB = 8,
    };

    constexpr File MirrorFile(File file)
    {
        return file ^ kFileH;
    }

    constexpr File RelativeFile(File file, Color side)
    {
        return file ^ (side * kFileH);
    }
}

#endif