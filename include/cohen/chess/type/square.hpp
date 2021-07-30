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

    constexpr Square RelativeSquare(Color side, Square sq) noexcept
    {
        assert(side == kWhite || side == kBlack);
        assert(kA1 <= sq && sq < kSquareNB);
        return sq ^ (side * 0b111111);
    }

    constexpr Square RelativeSquareRank(Color side, Square sq) noexcept
    {
        assert(side == kWhite || side == kBlack);
        assert(kA1 <= sq && sq < kSquareNB);
        return sq ^ (side * 0b111000);
    }

    constexpr Square RelativeSquareFile(Color side, Square sq) noexcept
    {
        assert(side == kWhite || side == kBlack);
        assert(kA1 <= sq && sq < kSquareNB);
        return sq ^ (side * 0b000111);
    }

    constexpr Square EnPassantTarget(Color side, File ep_file) noexcept
    {
        assert(side == kWhite || side == kBlack);
        assert(kFileA <= ep_file && ep_file < kFileNB);
        return MakeSquare(RelativeRank(side, kRank6), ep_file);
    }

    constexpr int RuntimeSquareRankDistance(Square from, Square to) noexcept
    {
        assert(kA1 <= from && from < kSquareNB);
        assert(kA1 <= to   &&   to < kSquareNB);
        const auto diff = RankOf(from) - RankOf(to);
        return diff < 0 ? -diff : +diff;
    }

    inline constexpr std::array<std::array<int8_t, kSquareNB>, kSquareNB> kSquareRankDistanceTable = []()
    {
        std::array<std::array<int8_t, kSquareNB>, kSquareNB> dist_table = {};
        for (Square from = kA1; from < kSquareNB; ++from)
        for (Square   to = kA1;   to < kSquareNB; ++to)
        {
            dist_table[from][to] = RuntimeSquareRankDistance(from, to);
        }
        return dist_table;
    }();

    constexpr int LookupSquareRankDistance(Square from, Square to) noexcept
    {
        assert(kA1 <= from && from < kSquareNB);
        assert(kA1 <= to   &&   to < kSquareNB);
        return kSquareRankDistanceTable[from][to];
    }

    constexpr int SquareRankDistance(Square from, Square to) noexcept
    {
        assert(kA1 <= from && from < kSquareNB);
        assert(kA1 <= to   &&   to < kSquareNB);
        return LookupSquareRankDistance(from, to);
    }

    constexpr int RuntimeSquareFileDistance(Square from, Square to) noexcept
    {
        assert(kA1 <= from && from < kSquareNB);
        assert(kA1 <= to   &&   to < kSquareNB);
        const auto diff = FileOf(from) - FileOf(to);
        return diff < 0 ? -diff : +diff;
    }

    inline constexpr std::array<std::array<int8_t, kSquareNB>, kSquareNB> kSquareFileDistanceTable = []()
    {
        std::array<std::array<int8_t, kSquareNB>, kSquareNB> dist_table = {};
        for (Square from = kA1; from < kSquareNB; ++from)
        for (Square   to = kA1;   to < kSquareNB; ++to)
        {
            dist_table[from][to] = RuntimeSquareFileDistance(from, to);
        }
        return dist_table;
    }();

    constexpr int LookupSquareFileDistance(Square from, Square to) noexcept
    {
        assert(kA1 <= from && from < kSquareNB);
        assert(kA1 <= to   &&   to < kSquareNB);
        return kSquareFileDistanceTable[from][to];
    }

    constexpr int SquareFileDistance(Square from, Square to) noexcept
    {
        assert(kA1 <= from && from < kSquareNB);
        assert(kA1 <= to   &&   to < kSquareNB);
        return LookupSquareFileDistance(from, to);
    }

    constexpr int RuntimeSquareDistance(Square from, Square to) noexcept
    {
        assert(kA1 <= from && from < kSquareNB);
        assert(kA1 <= to   &&   to < kSquareNB);
        return SquareRankDistance(from, to) + SquareFileDistance(from, to);
    }

    inline constexpr std::array<std::array<int8_t, kSquareNB>, kSquareNB> kSquareDistanceTable = []()
    {
        std::array<std::array<int8_t, kSquareNB>, kSquareNB> dist_table = {};
        for (Square from = kA1; from < kSquareNB; ++from)
        for (Square   to = kA1;   to < kSquareNB; ++to)
        {
            dist_table[from][to] = RuntimeSquareDistance(from, to);
        }
        return dist_table;
    }();

    constexpr int LookupSquareDistance(Square from, Square to) noexcept
    {
        assert(kA1 <= from && from < kSquareNB);
        assert(kA1 <= to   &&   to < kSquareNB);
        return kSquareDistanceTable[from][to];
    }

    constexpr int SquareDistance(Square from, Square to) noexcept
    {
        assert(kA1 <= from && from < kSquareNB);
        assert(kA1 <= to   &&   to < kSquareNB);
        return LookupSquareDistance(from, to);
    }

    constexpr bool IsNormalSquare(Square sq) noexcept
    {
        return kA1 <= sq && sq < kSquareNB;
    }

    constexpr bool OnSameRank(Square from, Square to) noexcept
    {
        assert(kA1 <= from && from < kSquareNB);
        assert(kA1 <= to   &&   to < kSquareNB);
        return RankOf(from ^ to) == 0;
    }

    constexpr bool OnSameFile(Square from, Square to) noexcept
    {
        assert(kA1 <= from && from < kSquareNB);
        assert(kA1 <= to   &&   to < kSquareNB);
        return FileOf(from ^ to) == 0;
    }

    constexpr bool OnSameDiag(Square from, Square to) noexcept
    {
        assert(kA1 <= from && from < kSquareNB);
        assert(kA1 <= to   &&   to < kSquareNB);
        return (from - to) % 9 == 0;
    }

    constexpr bool OnSameAnti(Square from, Square to) noexcept
    {
        assert(kA1 <= from && from < kSquareNB);
        assert(kA1 <= to   &&   to < kSquareNB);
        return RankOf(from) + FileOf(to) == RankOf(from) + FileOf(to);
    }
}

namespace cohen::chess
{
    using cohen::chess::type::square::Square;
    using enum cohen::chess::type::square::SquareConstant;

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
