#ifndef COHEN_CHESS_TYPES_FILE_HPP_INCLUDED
#define COHEN_CHESS_TYPES_FILE_HPP_INCLUDED

#include <cstdint>

#include <types/color.hpp>

namespace cohen_chess
{
    namespace file
    {
        using File = int8_t;

        enum FileConstant : File
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

        constexpr File MirrorFile(File file) noexcept
        {
            return file ^ kFileH;
        }

        constexpr File RelativeFile(File file, Color side) noexcept
        {
            return file ^ (side * kFileH);
        }
    }

    using namespace file;
}

#endif