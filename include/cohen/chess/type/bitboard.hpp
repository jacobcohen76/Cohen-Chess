#ifndef COHEN_CHESS_TYPE_BITBOARD_HPP_INCLUDED
#define COHEN_CHESS_TYPE_BITBOARD_HPP_INCLUDED

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>

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
        std::generate(std::begin(square_table), std::end(square_table),
        [sq = Square(kA1)]() mutable -> Bitboard
        {
            return RuntimeSquareBB(sq++);
        });
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
        std::generate(std::begin(rank_table), std::end(rank_table),
        [rank = Rank(kRank1)]() mutable -> Bitboard
        {
            return RuntimeRankBB(rank++);
        });
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
        std::generate(std::begin(file_table), std::end(file_table),
        [file = File(kFileA)]() mutable -> Bitboard
        {
            return RuntimeFileBB(file++);
        });
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

    template <Direction dir>
    inline constexpr std::array<Bitboard, kSquareNB> kRayBitboardTable = []()
    {
        static_assert(dir != kDirectionNone);
        std::array<Bitboard, kSquareNB> ray_table = {};
        std::generate(std::begin(ray_table), std::end(ray_table),
        [sq = Square(kA1)]() mutable -> Bitboard
        {
            Bitboard ray_bb = kEmptyBB;
            Square itr = sq++;
            while (CanStep(itr, dir))
            {
                ray_bb |= SquareBB(itr += dir);
            }
            return ray_bb;
        });
        return ray_table;
    }();

    template <Direction dir>
    constexpr Bitboard RayBB(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return kRayBitboardTable<dir>[sq];
    }

    template <>
    constexpr Bitboard RayBB<kDirectionNone>(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return kEmptyBB;
    }

    template <Direction dir>
    constexpr Bitboard RayBB(Bitboard occ, Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        if constexpr (dir > 0)
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

    constexpr Bitboard RayBB(Square sq, Direction dir) noexcept
    {
        switch (dir)
        {
            case kNorth:          return RayBB<kNorth>          (sq);
            case kEast:           return RayBB<kEast>           (sq);
            case kSouth:          return RayBB<kSouth>          (sq);
            case kWest:           return RayBB<kWest>           (sq);
            case kNorthEast:      return RayBB<kNorthEast>      (sq);
            case kSouthEast:      return RayBB<kSouthEast>      (sq);
            case kSouthWest:      return RayBB<kSouthWest>      (sq);
            case kNorthWest:      return RayBB<kNorthWest>      (sq);
            case kNorthNorth:     return RayBB<kNorthNorth>     (sq);
            case kEastEast:       return RayBB<kEastEast>       (sq);
            case kSouthSouth:     return RayBB<kSouthSouth>     (sq);
            case kWestWest:       return RayBB<kWestWest>       (sq);
            case kNorthNorthEast: return RayBB<kNorthNorthEast> (sq);
            case kNorthNorthWest: return RayBB<kNorthNorthWest> (sq);
            case kEastEastNorth:  return RayBB<kEastEastNorth>  (sq);
            case kEastEastSouth:  return RayBB<kEastEastSouth>  (sq);
            case kSouthSouthEast: return RayBB<kSouthSouthEast> (sq);
            case kSouthSouthWest: return RayBB<kSouthSouthWest> (sq);
            case kWestWestNorth:  return RayBB<kWestWestNorth>  (sq);
            case kWestWestSouth:  return RayBB<kWestWestSouth>  (sq);
            default:              return RayBB<kDirectionNone>  (sq);
        }
    }

    constexpr Bitboard RayBB(Bitboard occ, Square sq, Direction dir) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        Bitboard ray_bb = RayBB(sq, dir);
        int blocker = (dir > 0) ? BitScanForward((occ & ray_bb) | 0x8000000000000000)
                                : BitScanReverse((occ & ray_bb) | 0x0000000000000001);
        return ray_bb ^ RayBB(blocker, dir);
    }

    constexpr Bitboard RuntimeBetweenBB(Square sq1, Square sq2) noexcept
    {
        assert(kA1 <= sq1 && sq1 < kSquareNB);
        assert(kA1 <= sq2 && sq2 < kSquareNB);
        return RayBB(sq1, RayBetween(sq1, sq2)) &
               RayBB(sq2, RayBetween(sq2, sq1));
    }

    inline constexpr std::array<std::array<Bitboard, kSquareNB>, kSquareNB> kBetweenBitboardTable = []()
    {
        std::array<std::array<Bitboard, kSquareNB>, kSquareNB> between_table = {};
        std::generate(std::begin(between_table), std::end(between_table),
        [sq1 = Square(kA1)]() mutable -> std::array<Bitboard, kSquareNB>
        {
            std::array<Bitboard, kSquareNB> sub_table = {};
            std::generate(std::begin(sub_table), std::end(sub_table),
            [sq1, sq2 = Square(kA1)]() mutable -> Bitboard
            {
                return RuntimeBetweenBB(sq1, sq2++);
            });
            return ++sq1, sub_table;
        });
        return between_table;
    }();

    constexpr Bitboard LookupBetweenBB(Square sq1, Square sq2) noexcept
    {
        assert(kA1 <= sq1 && sq1 < kSquareNB);
        assert(kA1 <= sq2 && sq2 < kSquareNB);
        return kBetweenBitboardTable[sq1][sq2];
    }

    constexpr Bitboard BetweenBB(Square sq1, Square sq2) noexcept
    {
        assert(kA1 <= sq1 && sq1 < kSquareNB);
        assert(kA1 <= sq2 && sq2 < kSquareNB);
        return LookupBetweenBB(sq1, sq2);
    }

    template <Direction dir>
    inline constexpr Bitboard kShiftMask = kUniverseBB;

    template <> inline constexpr Bitboard kShiftMask<kEast>           = ~FileBB(kFileH);
    template <> inline constexpr Bitboard kShiftMask<kNorthEast>      =  kShiftMask<kEast>;
    template <> inline constexpr Bitboard kShiftMask<kSouthEast>      =  kShiftMask<kEast>;
    template <> inline constexpr Bitboard kShiftMask<kNorthNorthEast> =  kShiftMask<kEast>;
    template <> inline constexpr Bitboard kShiftMask<kSouthSouthEast> =  kShiftMask<kEast>;

    template <> inline constexpr Bitboard kShiftMask<kEastEast>       = ~FileBB(kFileH) & ~FileBB(kFileG);
    template <> inline constexpr Bitboard kShiftMask<kEastEastNorth>  =  kShiftMask<kEastEast>;
    template <> inline constexpr Bitboard kShiftMask<kEastEastSouth>  =  kShiftMask<kEastEast>;

    template <> inline constexpr Bitboard kShiftMask<kWest>           = ~FileBB(kFileA);
    template <> inline constexpr Bitboard kShiftMask<kNorthWest>      =  kShiftMask<kWest>;
    template <> inline constexpr Bitboard kShiftMask<kSouthWest>      =  kShiftMask<kWest>;
    template <> inline constexpr Bitboard kShiftMask<kNorthNorthWest> =  kShiftMask<kWest>;
    template <> inline constexpr Bitboard kShiftMask<kSouthSouthWest> =  kShiftMask<kWest>;

    template <> inline constexpr Bitboard kShiftMask<kWestWest>       = ~FileBB(kFileA) & ~FileBB(kFileB);
    template <> inline constexpr Bitboard kShiftMask<kWestWestNorth>  =  kShiftMask<kWestWest>;
    template <> inline constexpr Bitboard kShiftMask<kWestWestSouth>  =  kShiftMask<kWestWest>;

    template <Direction dir>
    constexpr Bitboard ShiftBB(Bitboard bb) noexcept
    {
        if constexpr (dir > 0)
        {
            return (bb & kShiftMask<dir>) << +dir;
        }
        else
        {
            return (bb & kShiftMask<dir>) >> -dir;
        }
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

    using cohen::chess::type::bitboard::kEmptyBB;
    using cohen::chess::type::bitboard::kUniverseBB;
    using cohen::chess::type::bitboard::kDarkSquaresBB;
    using cohen::chess::type::bitboard::kLightSquaresBB;
    using cohen::chess::type::bitboard::kRankEdgesBB;
    using cohen::chess::type::bitboard::kFileEdgesBB;
    using cohen::chess::type::bitboard::kMainDiagBB;
    using cohen::chess::type::bitboard::kMainAntiBB;
    using cohen::chess::type::bitboard::kEdgesBB;

    using cohen::chess::type::bitboard::SquareBB;
    using cohen::chess::type::bitboard::RankBB;
    using cohen::chess::type::bitboard::FileBB;
    using cohen::chess::type::bitboard::DiagBB;
    using cohen::chess::type::bitboard::AntiBB;
    using cohen::chess::type::bitboard::RayBB;
    using cohen::chess::type::bitboard::BetweenBB;
    using cohen::chess::type::bitboard::ShiftBB;
    using cohen::chess::type::bitboard::MirrorBitboardRank;
    using cohen::chess::type::bitboard::MirrorBitboardFile;
    using cohen::chess::type::bitboard::MirrorBitboardDiag;
    using cohen::chess::type::bitboard::MirrorBitboardAnti;
}

#endif
