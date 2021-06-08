#ifndef COHEN_CHESS_TYPE_FILE_HPP_INCLUDED
#define COHEN_CHESS_TYPE_FILE_HPP_INCLUDED

#include <cstdint>

#include <type/color.hpp>

namespace cohen_chess::type::file
{
    using File = int;

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

namespace cohen_chess
{
    using type::file::File;

    using type::file::kFileA;
    using type::file::kFileB;
    using type::file::kFileC;
    using type::file::kFileD;
    using type::file::kFileE;
    using type::file::kFileF;
    using type::file::kFileG;
    using type::file::kFileH;
    using type::file::kFileNB;

    using type::file::MirrorFile;
    using type::file::RelativeFile;
}

#endif