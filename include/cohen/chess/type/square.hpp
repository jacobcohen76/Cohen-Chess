#ifndef COHEN_CHESS_TYPE_SQUARE_HPP_INCLUDED
#define COHEN_CHESS_TYPE_SQUARE_HPP_INCLUDED

#include <algorithm>
#include <cassert>
#include <cstdint>

#include <cohen/chess/type/anti.hpp>
#include <cohen/chess/type/diag.hpp>
#include <cohen/chess/type/file.hpp>
#include <cohen/chess/type/rank.hpp>

namespace cohen::chess::type::square
{
    using Square = int;

    enum SquareConstant : Square
    {
        kA1, kB1, kC1, kD1, kE1, kF1, kG1, kH1,
        kA2, kB2, kC2, kD2, kE2, kF2, kG2, kH2,
        kA3, kB3, kC3, kD3, kE3, kF3, kG3, kH3,
        kA4, kB4, kC4, kD4, kE4, kF4, kG4, kH4,
        kA5, kB5, kC5, kD5, kE5, kF5, kG5, kH5,
        kA6, kB6, kC6, kD6, kE6, kF6, kG6, kH6,
        kA7, kB7, kC7, kD7, kE7, kF7, kG7, kH7,
        kA8, kB8, kC8, kD8, kE8, kF8, kG8, kH8,
        kSquareNone = 64,
        kSquareNB   = 64,
    };

    constexpr Square MakeSquare(Rank rank, File file) noexcept
    {
        assert(kRank1 <= rank && rank < kRankNB);
        assert(kFileA <= file && file < kFileNB);
        return (rank << 3) | file;
    }

    constexpr Rank RankOf(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return sq >> 3;
    }

    constexpr File FileOf(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return sq & 0b000111;
    }

    constexpr Diag DiagOf(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return RankOf(sq) - FileOf(sq) + kDiag8;
    }

    constexpr Anti AntiOf(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return RankOf(sq) + FileOf(sq);
    }

    constexpr Square MirrorSquareRank(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return sq ^ 0b111000;
    }

    constexpr Square MirrorSquareFile(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return sq ^ 0b000111;
    }

    constexpr Square MirrorSquareDiag(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return ((sq << 3) | (sq >> 3)) & 0b111111;
    }

    constexpr Square MirrorSquareAnti(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return MirrorSquareDiag(sq) ^ 0b111111;
    }

    constexpr Square MirrorSquare(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return sq ^ 0b111111;
    }

    constexpr Square RelativeSquare(Square sq, Color side) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        assert(side == kWhite || side == kBlack);
        return sq ^ (side * 0b111111);
    }

    constexpr Square RelativeSquareRank(Square sq, Color side) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        assert(side == kWhite || side == kBlack);
        return sq ^ (side * 0b111000);
    }

    constexpr Square RelativeSquareFile(Square sq, Color side) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        assert(side == kWhite || side == kBlack);
        return sq ^ (side * 0b000111);
    }

    constexpr Square EnPassantTarget(File ep_file, Color side) noexcept
    {
        assert(kFileA <= ep_file && ep_file < kFileNB);
        assert(side == kWhite || kBlack);
        return MakeSquare(RelativeRank(kRank6, side), ep_file);
    }

    constexpr int RuntimeSquareRankDistance(Square sq1, Square sq2) noexcept
    {
        assert(kA1 <= sq1 && sq1 < kSquareNB);
        assert(kA1 <= sq2 && sq2 < kSquareNB);
        const auto diff = RankOf(sq1) - RankOf(sq2);
        return diff < 0 ? -diff : +diff;
    }

    inline constexpr std::array<std::array<int8_t, kSquareNB>, kSquareNB> kSquareRankDistanceTable = []()
    {
        std::array<std::array<int8_t, kSquareNB>, kSquareNB> dist_table = {};
        std::generate(begin(dist_table), end(dist_table),
        [sq1 = Square{kA1}]() mutable -> std::array<int8_t, kSquareNB>
        {
            std::array<int8_t, kSquareNB> sub_table = {};
            std::generate(begin(sub_table), end(sub_table),
            [sq1, sq2 = Square{kA1}]() mutable -> int8_t
            {
                return RuntimeSquareRankDistance(sq1, sq2++);
            });
            return ++sq1, sub_table;
        });
        return dist_table;
    }();

    constexpr int LookupSquareRankDistance(Square sq1, Square sq2) noexcept
    {
        assert(kA1 <= sq1 && sq1 < kSquareNB);
        assert(kA1 <= sq2 && sq2 < kSquareNB);
        return kSquareRankDistanceTable[sq1][sq2];
    }

    constexpr int SquareRankDistance(Square sq1, Square sq2) noexcept
    {
        assert(kA1 <= sq1 && sq1 < kSquareNB);
        assert(kA1 <= sq2 && sq2 < kSquareNB);
        return LookupSquareRankDistance(sq1, sq2);
    }

    constexpr int RuntimeSquareFileDistance(Square sq1, Square sq2) noexcept
    {
        assert(kA1 <= sq1 && sq1 < kSquareNB);
        assert(kA1 <= sq2 && sq2 < kSquareNB);
        const auto diff = FileOf(sq1) - FileOf(sq2);
        return diff < 0 ? -diff : +diff;
    }

    inline constexpr std::array<std::array<int8_t, kSquareNB>, kSquareNB> kSquareFileDistanceTable = []()
    {
        std::array<std::array<int8_t, kSquareNB>, kSquareNB> dist_table = {};
        std::generate(begin(dist_table), end(dist_table),
        [sq1 = Square{kA1}]() mutable -> std::array<int8_t, kSquareNB>
        {
            std::array<int8_t, kSquareNB> sub_table = {};
            std::generate(begin(sub_table), end(sub_table),
            [sq1, sq2 = Square{kA1}]() mutable -> int8_t
            {
                return RuntimeSquareFileDistance(sq1, sq2++);
            });
            return ++sq1, sub_table;
        });
        return dist_table;
    }();

    constexpr int LookupSquareFileDistance(Square sq1, Square sq2) noexcept
    {
        assert(kA1 <= sq1 && sq1 < kSquareNB);
        assert(kA1 <= sq2 && sq2 < kSquareNB);
        return kSquareFileDistanceTable[sq1][sq2];
    }

    constexpr int SquareFileDistance(Square sq1, Square sq2) noexcept
    {
        assert(kA1 <= sq1 && sq1 < kSquareNB);
        assert(kA1 <= sq2 && sq2 < kSquareNB);
        return LookupSquareFileDistance(sq1, sq2);
    }

    constexpr int RuntimeSquareDistance(Square sq1, Square sq2) noexcept
    {
        assert(kA1 <= sq1 && sq1 < kSquareNB);
        assert(kA1 <= sq2 && sq2 < kSquareNB);
        return SquareRankDistance(sq1, sq2) + SquareFileDistance(sq1, sq2);
    }

    inline constexpr std::array<std::array<int8_t, kSquareNB>, kSquareNB> kSquareDistanceTable = []()
    {
        std::array<std::array<int8_t, kSquareNB>, kSquareNB> dist_table = {};
        std::generate(begin(dist_table), end(dist_table),
        [sq1 = Square{kA1}]() mutable -> std::array<int8_t, kSquareNB>
        {
            std::array<int8_t, kSquareNB> sub_table = {};
            std::generate(begin(sub_table), end(sub_table),
            [sq1, sq2 = Square{kA1}]() mutable -> int8_t
            {
                return RuntimeSquareDistance(sq1, sq2++);
            });
            return ++sq1, sub_table;
        });
        return dist_table;
    }();

    constexpr int LookupSquareDistance(Square sq1, Square sq2) noexcept
    {
        assert(kA1 <= sq1 && sq1 < kSquareNB);
        assert(kA1 <= sq2 && sq2 < kSquareNB);
        return kSquareDistanceTable[sq1][sq2];
    }

    constexpr int SquareDistance(Square sq1, Square sq2) noexcept
    {
        assert(kA1 <= sq1 && sq1 < kSquareNB);
        assert(kA1 <= sq2 && sq2 < kSquareNB);
        return LookupSquareDistance(sq1, sq2);
    }

    constexpr bool IsNormalSquare(Square sq) noexcept
    {
        return kA1 <= sq && sq < kSquareNB;
    }

    constexpr bool OnSameRank(Square sq1, Square sq2) noexcept
    {
        assert(kA1 <= sq1 && sq1 < kSquareNB);
        assert(kA1 <= sq2 && sq2 < kSquareNB);
        return RankOf(sq1 ^ sq2) == 0;
    }

    constexpr bool OnSameFile(Square sq1, Square sq2) noexcept
    {
        assert(kA1 <= sq1 && sq1 < kSquareNB);
        assert(kA1 <= sq2 && sq2 < kSquareNB);
        return FileOf(sq1 ^ sq2) == 0;
    }

    constexpr bool OnSameDiag(Square sq1, Square sq2) noexcept
    {
        assert(kA1 <= sq1 && sq1 < kSquareNB);
        assert(kA1 <= sq2 && sq2 < kSquareNB);
        return (sq2 - sq1) % 9 == 0;
    }

    constexpr bool OnSameAnti(Square sq1, Square sq2) noexcept
    {
        assert(kA1 <= sq1 && sq1 < kSquareNB);
        assert(kA1 <= sq2 && sq2 < kSquareNB);
        return RankOf(sq1) + FileOf(sq1) == RankOf(sq2) + FileOf(sq2);
    }
}

namespace cohen::chess
{
    using cohen::chess::type::square::Square;

    using cohen::chess::type::square::kA1;
    using cohen::chess::type::square::kB1;
    using cohen::chess::type::square::kC1;
    using cohen::chess::type::square::kD1;
    using cohen::chess::type::square::kE1;
    using cohen::chess::type::square::kF1;
    using cohen::chess::type::square::kG1;
    using cohen::chess::type::square::kH1;
    using cohen::chess::type::square::kA2;
    using cohen::chess::type::square::kB2;
    using cohen::chess::type::square::kC2;
    using cohen::chess::type::square::kD2;
    using cohen::chess::type::square::kE2;
    using cohen::chess::type::square::kF2;
    using cohen::chess::type::square::kG2;
    using cohen::chess::type::square::kH2;
    using cohen::chess::type::square::kA3;
    using cohen::chess::type::square::kB3;
    using cohen::chess::type::square::kC3;
    using cohen::chess::type::square::kD3;
    using cohen::chess::type::square::kE3;
    using cohen::chess::type::square::kF3;
    using cohen::chess::type::square::kG3;
    using cohen::chess::type::square::kH3;
    using cohen::chess::type::square::kA4;
    using cohen::chess::type::square::kB4;
    using cohen::chess::type::square::kC4;
    using cohen::chess::type::square::kD4;
    using cohen::chess::type::square::kE4;
    using cohen::chess::type::square::kF4;
    using cohen::chess::type::square::kG4;
    using cohen::chess::type::square::kH4;
    using cohen::chess::type::square::kA5;
    using cohen::chess::type::square::kB5;
    using cohen::chess::type::square::kC5;
    using cohen::chess::type::square::kD5;
    using cohen::chess::type::square::kE5;
    using cohen::chess::type::square::kF5;
    using cohen::chess::type::square::kG5;
    using cohen::chess::type::square::kH5;
    using cohen::chess::type::square::kA6;
    using cohen::chess::type::square::kB6;
    using cohen::chess::type::square::kC6;
    using cohen::chess::type::square::kD6;
    using cohen::chess::type::square::kE6;
    using cohen::chess::type::square::kF6;
    using cohen::chess::type::square::kG6;
    using cohen::chess::type::square::kH6;
    using cohen::chess::type::square::kA7;
    using cohen::chess::type::square::kB7;
    using cohen::chess::type::square::kC7;
    using cohen::chess::type::square::kD7;
    using cohen::chess::type::square::kE7;
    using cohen::chess::type::square::kF7;
    using cohen::chess::type::square::kG7;
    using cohen::chess::type::square::kH7;
    using cohen::chess::type::square::kA8;
    using cohen::chess::type::square::kB8;
    using cohen::chess::type::square::kC8;
    using cohen::chess::type::square::kD8;
    using cohen::chess::type::square::kE8;
    using cohen::chess::type::square::kF8;
    using cohen::chess::type::square::kG8;
    using cohen::chess::type::square::kH8;
    using cohen::chess::type::square::kSquareNone;
    using cohen::chess::type::square::kSquareNB;

    using cohen::chess::type::square::MakeSquare;
    using cohen::chess::type::square::RankOf;
    using cohen::chess::type::square::FileOf;
    using cohen::chess::type::square::DiagOf;
    using cohen::chess::type::square::AntiOf;
    using cohen::chess::type::square::MirrorSquareRank;
    using cohen::chess::type::square::MirrorSquareFile;
    using cohen::chess::type::square::MirrorSquareDiag;
    using cohen::chess::type::square::MirrorSquareAnti;
    using cohen::chess::type::square::MirrorSquare;
    using cohen::chess::type::square::RelativeSquare;
    using cohen::chess::type::square::RelativeSquareRank;
    using cohen::chess::type::square::RelativeSquareFile;
    using cohen::chess::type::square::EnPassantTarget;
    using cohen::chess::type::square::SquareRankDistance;
    using cohen::chess::type::square::SquareFileDistance;
    using cohen::chess::type::square::SquareDistance;
    using cohen::chess::type::square::IsNormalSquare;
    using cohen::chess::type::square::OnSameRank;
    using cohen::chess::type::square::OnSameFile;
    using cohen::chess::type::square::OnSameDiag;
    using cohen::chess::type::square::OnSameAnti;
}

#endif
