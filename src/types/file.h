#ifndef COHEN_CHESS_TYPES_FILE_H_INCLUDED
#define COHEN_CHESS_TYPES_FILE_H_INCLUDED

#include "color.h"

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

    constexpr File MirrorFile(File f)
    {
        return File(f ^ kFileH);
    }

    constexpr File RelativeFile(Color side, File f)
    {
        return File(f ^ (side * kFileH));
    }
}

#endif