#ifndef COHEN_CHESS_TYPE_FILE_HPP_INCLUDED
#define COHEN_CHESS_TYPE_FILE_HPP_INCLUDED

#include <cassert>
#include <cstdint>

#include <cohen/chess/type/color.hpp>

namespace cohen::chess::type::file
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
        assert(kFileA <= file && file < kFileNB);
        return file ^ 0b111;
    }

    constexpr File RelativeFile(Color side, File file) noexcept
    {
        assert(side == kWhite || side == kBlack);
        assert(kFileA <= file && file < kFileNB);
        return file ^ (side * 0b111);
    }
}

namespace cohen::chess
{
    using cohen::chess::type::file::File;
    using enum cohen::chess::type::file::FileConstant;

    using cohen::chess::type::file::MirrorFile;
    using cohen::chess::type::file::RelativeFile;
}

#endif
