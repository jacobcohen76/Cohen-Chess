#ifndef COHEN_CHESS_TYPE_FILE_HPP_INCLUDED
#define COHEN_CHESS_TYPE_FILE_HPP_INCLUDED

#include <cassert>
#include <cstdint>

#include <cohen/chess/type/color.hpp>

namespace cohen::chess::type::file
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
        assert(kFileA <= file && file < kFileNB);
        return file ^ 0b111;
    }

    constexpr File RelativeFile(File file, Color side) noexcept
    {
        assert(kFileA <= file && file < kFileNB);
        assert(side == kWhite || side == kBlack);
        return file ^ (side * 0b111);
    }
}

namespace cohen::chess
{
    using cohen::chess::type::file::File;

    using cohen::chess::type::file::kFileA;
    using cohen::chess::type::file::kFileB;
    using cohen::chess::type::file::kFileC;
    using cohen::chess::type::file::kFileD;
    using cohen::chess::type::file::kFileE;
    using cohen::chess::type::file::kFileF;
    using cohen::chess::type::file::kFileG;
    using cohen::chess::type::file::kFileH;
    using cohen::chess::type::file::kFileNB;

    using cohen::chess::type::file::MirrorFile;
    using cohen::chess::type::file::RelativeFile;
}

#endif
