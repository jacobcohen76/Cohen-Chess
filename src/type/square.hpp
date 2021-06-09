#ifndef COHEN_CHESS_TYPE_SQUARE_HPP_INCLUDED
#define COHEN_CHESS_TYPE_SQUARE_HPP_INCLUDED

#include <algorithm>
#include <cassert>
#include <cstdint>

#include <type/anti.hpp>
#include <type/diag.hpp>
#include <type/file.hpp>
#include <type/rank.hpp>

namespace cohen_chess::type::square
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

    constexpr int SquareRankDistance(Square sq1, Square sq2) noexcept
    {
        assert(kA1 <= sq1 && sq1 < kSquareNB);
        assert(kA1 <= sq2 && sq2 < kSquareNB);
        const auto diff = RankOf(sq1) - RankOf(sq2);
        return (diff < 0) ? -diff : +diff;
    }

    constexpr int SquareFileDistance(Square sq1, Square sq2) noexcept
    {
        assert(kA1 <= sq1 && sq1 < kSquareNB);
        assert(kA1 <= sq2 && sq2 < kSquareNB);
        const auto diff = FileOf(sq1) - FileOf(sq2);
        return (diff < 0) ? -diff : +diff;
    }

    constexpr int SquareDistance(Square sq1, Square sq2) noexcept
    {
        assert(kA1 <= sq1 && sq1 < kSquareNB);
        assert(kA1 <= sq2 && sq2 < kSquareNB);
        return SquareRankDistance(sq1, sq2) + SquareFileDistance(sq1, sq2);
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

namespace cohen_chess
{
    using type::square::Square;

    using type::square::kA1, type::square::kB1, type::square::kC1, type::square::kD1,
          type::square::kE1, type::square::kF1, type::square::kG1, type::square::kH1,
          type::square::kA2, type::square::kB2, type::square::kC2, type::square::kD2,
          type::square::kE2, type::square::kF2, type::square::kG2, type::square::kH2,
          type::square::kA3, type::square::kB3, type::square::kC3, type::square::kD3,
          type::square::kE3, type::square::kF3, type::square::kG3, type::square::kH3,
          type::square::kA4, type::square::kB4, type::square::kC4, type::square::kD4,
          type::square::kE4, type::square::kF4, type::square::kG4, type::square::kH4,
          type::square::kA5, type::square::kB5, type::square::kC5, type::square::kD5,
          type::square::kE5, type::square::kF5, type::square::kG5, type::square::kH5,
          type::square::kA6, type::square::kB6, type::square::kC6, type::square::kD6,
          type::square::kE6, type::square::kF6, type::square::kG6, type::square::kH6,
          type::square::kA7, type::square::kB7, type::square::kC7, type::square::kD7,
          type::square::kE7, type::square::kF7, type::square::kG7, type::square::kH7,
          type::square::kA8, type::square::kB8, type::square::kC8, type::square::kD8,
          type::square::kE8, type::square::kF8, type::square::kG8, type::square::kH8,
          type::square::kSquareNone,
          type::square::kSquareNB;

    using type::square::MakeSquare;
    using type::square::RankOf;
    using type::square::FileOf;
    using type::square::DiagOf;
    using type::square::AntiOf;
    using type::square::MirrorSquareRank;
    using type::square::MirrorSquareFile;
    using type::square::MirrorSquareDiag;
    using type::square::MirrorSquareAnti;
    using type::square::MirrorSquare;
    using type::square::RelativeSquare;
    using type::square::RelativeSquareRank;
    using type::square::RelativeSquareFile;
    using type::square::SquareRankDistance;
    using type::square::SquareFileDistance;
    using type::square::SquareDistance;
    using type::square::IsNormalSquare;
    using type::square::OnSameRank;
    using type::square::OnSameFile;
    using type::square::OnSameDiag;
    using type::square::OnSameAnti;
}

#endif