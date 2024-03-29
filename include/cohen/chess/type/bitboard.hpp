#ifndef COHEN_CHESS_TYPE_BITBOARD_HPP_INCLUDED
#define COHEN_CHESS_TYPE_BITBOARD_HPP_INCLUDED

#include <assert.h>
#include <stdint.h>

#include <algorithm>
#include <array>
#include <ranges>

#include <cohen/chess/type/anti.hpp>
#include <cohen/chess/type/diag.hpp>
#include <cohen/chess/type/direction.hpp>
#include <cohen/chess/type/file.hpp>
#include <cohen/chess/type/rank.hpp>
#include <cohen/chess/type/square.hpp>

#include <cohen/util/bits.hpp>

namespace cohen::chess::type::bitboard
{
    using Bitboard = uint64_t;

    enum BitboardConstant : Bitboard
    {
        kEmptyBB        = 0x0000000000000000,
        kUniverseBB     = 0xFFFFFFFFFFFFFFFF,
        kDarkSquaresBB  = 0xAA55AA55AA55AA55,
        kLightSquaresBB = 0x55AA55AA55AA55AA,
        kRankEdgesBB    = 0x8181818181818181,
        kFileEdgesBB    = 0xFF000000000000FF,
        kMainDiagBB     = 0x8040201008040201,
        kMainAntiBB     = 0x0102040810204080,
        kEdgesBB        = 0xFF818181818181FF,
    };

    constexpr Bitboard RuntimeSquareBB(Square sq) noexcept
    {
        constexpr Bitboard kBitboardA1 = 0x0000000000000001;
        assert(kA1 <= sq && sq < kSquareNB);
        return kBitboardA1 << sq;
    }

    inline constexpr std::array<Bitboard, kSquareNB> kSquareBitboardTable = []()
    {
        std::array<Bitboard, kSquareNB> square_table = {};
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            square_table[sq] = RuntimeSquareBB(sq);
        }
        return square_table;
    }();

    constexpr Bitboard LookupSquareBB(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return kSquareBitboardTable[sq];
    }

    constexpr Bitboard SquareBB(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return LookupSquareBB(sq);
    }

    constexpr Bitboard RuntimeRankBB(Rank rank) noexcept
    {
        constexpr Bitboard kBitboardRank1 = 0x00000000000000FF;
        assert(kRank1 <= rank && rank < kRankNB);
        return kBitboardRank1 << (rank << 3);
    }

    inline constexpr std::array<Bitboard, kRankNB> kRankBitboardTable = []()
    {
        std::array<Bitboard, kRankNB> rank_table = {};
        for (Rank rank = kRank1; rank < kRankNB; ++rank)
        {
            rank_table[rank] = RuntimeRankBB(rank);
        }
        return rank_table;
    }();

    constexpr Bitboard LookupRankBB(Rank rank) noexcept
    {
        assert(kRank1 <= rank && rank < kRankNB);
        return kRankBitboardTable[rank];
    }

    constexpr Bitboard RankBB(Rank rank) noexcept
    {
        assert(kRank1 <= rank && rank < kRankNB);
        return LookupRankBB(rank);
    }

    constexpr Bitboard RuntimeFileBB(File file) noexcept
    {
        constexpr Bitboard kBitboardFileA = 0x0101010101010101;
        assert(kFileA <= file && file < kFileNB);
        return kBitboardFileA << file;
    }

    inline constexpr std::array<Bitboard, kFileNB> kFileBitboardTable = []()
    {
        std::array<Bitboard, kFileNB> file_table = {};
        for (File file = kFileA; file < kFileNB; ++file)
        {
            file_table[file] = RuntimeFileBB(file);
        }
        return file_table;
    }();

    constexpr Bitboard LookupFileBB(File file) noexcept
    {
        assert(kFileA <= file && file < kFileNB);
        return kFileBitboardTable[file];
    }

    constexpr Bitboard FileBB(File file) noexcept
    {
        assert(kFileA <= file && file < kFileNB);
        return LookupFileBB(file);
    }

    inline constexpr std::array<Bitboard, kDiagNB> kDiagBitboardTable =
    {
        0x0000000000000080,
        0x0000000000008040,
        0x0000000000804020,
        0x0000000080402010,
        0x0000008040201008,
        0x0000804020100804,
        0x0080402010080402,
        0x8040201008040201,
        0x4020100804020100,
        0x2010080402010000,
        0x1008040201000000,
        0x0804020100000000,
        0x0402010000000000,
        0x0201000000000000,
        0x0100000000000000,
    };

    constexpr Bitboard LookupDiagBB(Diag diag) noexcept
    {
        assert(kDiag1 <= diag && diag < kDiagNB);
        return kDiagBitboardTable[diag];
    }

    constexpr Bitboard DiagBB(Diag diag) noexcept
    {
        assert(kDiag1 <= diag && diag < kDiagNB);
        return LookupDiagBB(diag);
    }

    inline constexpr std::array<Bitboard, kAntiNB> kAntiBitboardTable = 
    {
        0x0000000000000001,
        0x0000000000000102,
        0x0000000000010204,
        0x0000000001020408,
        0x0000000102040810,
        0x0000010204081020,
        0x0001020408102040,
        0x0102040810204080,
        0x0204081020408000,
        0x0408102040800000,
        0x0810204080000000,
        0x1020408000000000,
        0x2040800000000000,
        0x4080000000000000,
        0x8000000000000000,
    };

    constexpr Bitboard LookupAntiBB(Anti anti) noexcept
    {
        assert(kAnti1 <= anti && anti < kAntiNB);
        return kAntiBitboardTable[anti];
    }

    constexpr Bitboard AntiBB(Anti anti) noexcept
    {
        assert(kAnti1 <= anti && anti < kAntiNB);
        return LookupAntiBB(anti);
    }

    inline constexpr std::array<std::array<Bitboard, kSquareNB>, kDirNB> kRayBitboardTable = []()
    {
        std::array<std::array<Bitboard, kSquareNB>, kDirNB> ray_table = {};
        for (Direction dir = kDirNone; dir < kDirNB; ++dir)
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            Bitboard ray_bb = kEmptyBB;
            Square itr = sq;
            Square vec = SquareVector(dir);
            while (CanStep(itr, dir))
            {
                ray_bb |= SquareBB(itr += vec);
            }
            ray_table[dir][sq] = ray_bb;
        }
        return ray_table;
    }();

    constexpr Bitboard RayBB(Direction dir, Square sq) noexcept
    {
        assert(kDirNone <= dir && dir < kDirNB);
        assert(kA1 <= sq && sq < kSquareNB);
        return kRayBitboardTable[dir][sq];
    }

    constexpr Bitboard RayBB(Direction dir, Square sq, Bitboard occ) noexcept
    {
        assert(kDirNone <= dir && dir < kDirNB);
        assert(kA1 <= sq && sq < kSquareNB);
        Square vec = SquareVector(dir);
        Bitboard ray_bb = RayBB(dir, sq);
        int blocker = vec > 0 ? BitScanForward((occ & ray_bb) | SquareBB(kH8))
                              : BitScanReverse((occ & ray_bb) | SquareBB(kA1));
        return ray_bb ^ RayBB(dir, blocker);
    }

    template <Direction dir>
    constexpr Bitboard RayBB(Square sq) noexcept
    {
        static_assert(kDirNone <= dir && dir < kDirNB);
        assert(kA1 <= sq && sq < kSquareNB);
        return kRayBitboardTable[dir][sq];
    }

    template <Direction dir>
    constexpr Bitboard RayBB(Square sq, Bitboard occ) noexcept
    {
        static_assert(kDirNone <= dir && dir < kDirNB);
        assert(kA1 <= sq && sq < kSquareNB);
        if constexpr (SquareVector(dir) > 0)
        {
            Bitboard ray_bb = RayBB<dir>(sq);
            int blocker = BitScanForward((occ & ray_bb) | SquareBB(kH8));
            return ray_bb ^ RayBB<dir>(blocker);
        }
        else
        {
            Bitboard ray_bb = RayBB<dir>(sq);
            int blocker = BitScanReverse((occ & ray_bb) | SquareBB(kA1));
            return ray_bb ^ RayBB<dir>(blocker);
        }
    }

    constexpr Bitboard RuntimeBetweenBB(Square from, Square to) noexcept
    {
        assert(kA1 <= from && from < kSquareNB);
        assert(kA1 <= to   && to   < kSquareNB);
        return RayBB(RayBetween(from, to), from)
             & RayBB(RayBetween(to, from), to);
    }

    inline constexpr std::array<std::array<Bitboard, kSquareNB>, kSquareNB> kBetweenBitboardTable = []()
    {
        std::array<std::array<Bitboard, kSquareNB>, kSquareNB> between_table = {};
        for (Square from = kA1; from < kSquareNB; ++from)
        for (Square to   = kA2; to   < kSquareNB; ++to)
        {
            between_table[from][to] = RuntimeBetweenBB(from, to);
        }
        return between_table;
    }();

    constexpr Bitboard LookupBetweenBB(Square from, Square to) noexcept
    {
        assert(kA1 <= from && from < kSquareNB);
        assert(kA1 <= to   && to   < kSquareNB);
        return kBetweenBitboardTable[from][to];
    }

    constexpr Bitboard BetweenBB(Square from, Square to) noexcept
    {
        assert(kA1 <= from && from < kSquareNB);
        assert(kA1 <= to   && to   < kSquareNB);
        return LookupBetweenBB(from, to);
    }

    inline constexpr std::array<Bitboard, kDirNB> kShiftMaskTable = []()
    {
        std::array<Bitboard, kDirNB> mask_table = {};
        std::ranges::fill(mask_table, kUniverseBB);

        mask_table[kEast]      = ~FileBB(kFileH);
        mask_table[kNorthEast] = ~FileBB(kFileH);
        mask_table[kSouthEast] = ~FileBB(kFileH);
        mask_table[kEastEast]  = ~FileBB(kFileH) & ~FileBB(kFileG);

        mask_table[kWest]      = ~FileBB(kFileA);
        mask_table[kNorthWest] = ~FileBB(kFileA);
        mask_table[kSouthWest] = ~FileBB(kFileA);
        mask_table[kWestWest]  = ~FileBB(kFileA) & ~FileBB(kFileH);

        return mask_table;
    }();

    constexpr Bitboard ShiftMask(Direction dir) noexcept
    {
        assert(kDirNone <= dir && dir < kDirNB);
        return kShiftMaskTable[dir];
    }

    constexpr Bitboard ShfitBB(Direction dir, Bitboard bb) noexcept
    {
        assert(kDirNone <= dir && dir < kDirNB);
        const Square   kVec  = SquareVector(dir);
        const Bitboard kMask = ShiftMask(dir);
        if (kVec > 0)
            return (bb & kMask) << +kVec;
        else
            return (bb & kMask) >> -kVec;
    }

    template <Direction dir>
    constexpr Bitboard ShiftBB(Bitboard bb) noexcept
    {
        static_assert(kDirNone <= dir && dir < kDirNB);
        constexpr Square   kVec  = SquareVector(dir);
        constexpr Bitboard kMask = ShiftMask(dir);
        if constexpr (kVec > 0)
            return (bb & kMask) << +kVec;
        else
            return (bb & kMask) >> -kVec;
    }

    constexpr Bitboard MirrorBitboardRank(Bitboard bb) noexcept
    {
        return __builtin_bswap64(bb);
    }

    constexpr Bitboard MirrorBitboardFile(Bitboard bb) noexcept
    {
        constexpr Bitboard k1 = 0x5555555555555555;
        constexpr Bitboard k2 = 0x3333333333333333;
        constexpr Bitboard k4 = 0x0F0F0F0F0F0F0F0F;
        bb = ((bb >> 1) & k1) | ((bb & k1) << 1);
        bb = ((bb >> 2) & k2) | ((bb & k2) << 2);
        bb = ((bb >> 4) & k4) | ((bb & k4) << 4);
        return bb;
    }

    constexpr Bitboard MirrorBitboardDiag(Bitboard bb) noexcept
    {
        constexpr Bitboard k1 = 0x5500550055005500;
        constexpr Bitboard k2 = 0x3333000033330000;
        constexpr Bitboard k4 = 0x0F0F0F0F00000000;
        Bitboard tr = kEmptyBB;
        tr = ((bb << 28) ^ bb) & k4;
        bb = ((tr >> 28) ^ tr) ^ bb;
        tr = ((bb << 14) ^ bb) & k2;
        bb = ((tr >> 14) ^ tr) ^ bb;
        tr = ((bb <<  7) ^ bb) & k1;
        bb = ((tr >>  7) ^ tr) ^ bb;
        return bb;
    }

    constexpr Bitboard MirrorBitboardAnti(Bitboard bb) noexcept
    {
        constexpr Bitboard k1 = 0xAA00AA00AA00AA00;
        constexpr Bitboard k2 = 0xCCCC0000CCCC0000;
        constexpr Bitboard k4 = 0xF0F0F0F00F0F0F0F;
        Bitboard tr = kEmptyBB;
        tr =   (bb << 36) ^ bb;
        bb = (((bb >> 36) ^ tr) & k4) ^ bb;
        tr =  ((bb << 18) ^ bb) & k2;
        bb =  ((tr >> 18) ^ tr) ^ bb;
        tr =  ((bb <<  9) ^ bb) & k1;
        bb =  ((tr >>  9) ^ tr) ^ bb;
        return bb;
    }
}

namespace cohen::chess
{
    using cohen::chess::type::bitboard::Bitboard;
    using enum cohen::chess::type::bitboard::BitboardConstant;

    using cohen::chess::type::bitboard::SquareBB;
    using cohen::chess::type::bitboard::RankBB;
    using cohen::chess::type::bitboard::FileBB;
    using cohen::chess::type::bitboard::DiagBB;
    using cohen::chess::type::bitboard::AntiBB;
    using cohen::chess::type::bitboard::RayBB;
    using cohen::chess::type::bitboard::BetweenBB;
    using cohen::chess::type::bitboard::ShiftMask;
    using cohen::chess::type::bitboard::ShiftBB;
    using cohen::chess::type::bitboard::MirrorBitboardRank;
    using cohen::chess::type::bitboard::MirrorBitboardFile;
    using cohen::chess::type::bitboard::MirrorBitboardDiag;
    using cohen::chess::type::bitboard::MirrorBitboardAnti;
}

#endif