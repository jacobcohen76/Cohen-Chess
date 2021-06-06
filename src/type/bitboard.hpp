#ifndef COHEN_CHESS_TYPE_BITBOARD_HPP_INCLUDED
#define COHEN_CHESS_TYPE_BITBOARD_HPP_INCLUDED

#include <array>
#include <cassert>
#include <cstdint>

#include <type/anti.hpp>
#include <type/diag.hpp>
#include <type/direction.hpp>
#include <type/file.hpp>
#include <type/rank.hpp>
#include <type/square.hpp>
#include <util/bits.hpp>

namespace cohen_chess::type::bitboard
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

    constexpr std::array<Bitboard, kSquareNB> kSquareTable = []()
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
        return kSquareTable[sq];
    }

    constexpr Bitboard SquareBB(Square sq) noexcept
    {
        return LookupSquareBB(sq);
    }

    constexpr Bitboard RuntimeRankBB(Rank rank) noexcept
    {
        constexpr Bitboard kBitboardRank1 = 0x00000000000000FF;
        assert(kRank1 <= rank && rank < kRankNB);
        return kBitboardRank1 << (rank << 3);
    }

    constexpr std::array<Bitboard, kRankNB> kRankTable = []()
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
        return kRankTable[rank];
    }

    constexpr Bitboard RankBB(Rank rank) noexcept
    {
        return LookupRankBB(rank);
    }

    constexpr Bitboard RuntimeFileBB(File file) noexcept
    {
        constexpr Bitboard kBitboardFileA = 0x0101010101010101;
        assert(kFileA <= file && file < kFileNB);
        return kBitboardFileA << file;
    }

    constexpr std::array<Bitboard, kFileNB> kFileTable = []()
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
        return kFileTable[file];
    }

    constexpr Bitboard FileBB(File file) noexcept
    {
        return LookupFileBB(file);
    }

    constexpr std::array<Bitboard, kDiagNB> kDiagTable =
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
        return kDiagTable[diag];
    }

    constexpr Bitboard DiagBB(Diag diag) noexcept
    {
        return LookupDiagBB(diag);
    }

    constexpr std::array<Bitboard, kAntiNB> kAntiTable = 
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
        return kAntiTable[anti];
    }

    constexpr Bitboard AntiBB(Anti anti) noexcept
    {
        return LookupAntiBB(anti);
    }

    template <Direction dir>
    constexpr std::array<Bitboard, kSquareNB> kRayTable = []()
    {
        static_assert(dir != kDirectionNone);
        std::array<Bitboard, kSquareNB> ray_table = {};
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            Bitboard bb = kEmptyBB;
            Square  itr = sq;
            while (CanStep(itr, dir))
            {
                bb |= SquareBB(itr += dir);
            }
            ray_table[sq] = bb;
        }
        return ray_table;
    }();

    template <Direction dir>
    constexpr Bitboard RayBB(Square sq) noexcept
    {
        return kRayTable<dir>[sq];
    }

    template <>
    constexpr Bitboard RayBB<kDirectionNone>(Square sq) noexcept
    {
        return kEmptyBB;
    }

    template <Direction dir>
    constexpr Bitboard RayBB(Bitboard occ, Square sq) noexcept
    {
        if constexpr (dir > 0)
        {
            Bitboard ray_bb = RayBB<dir>(sq);
            int blocker = BitScanForward((occ & ray_bb) | 0x8000000000000000);
            return ray_bb ^ RayBB<dir>(blocker);
        }
        else
        {
            Bitboard ray_bb = RayBB<dir>(sq);
            int blocker = BitScanReverse((occ & ray_bb) | 0x0000000000000001);
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
        Bitboard ray_bb = RayBB(sq, dir);
        int blocker = (dir > 0) ? BitScanForward((occ & ray_bb) | 0x8000000000000000) :
                                  BitScanReverse((occ & ray_bb) | 0x0000000000000001);
        return ray_bb ^ RayBB(blocker, dir);
    }

    constexpr Bitboard RuntimeBetweenBB(Square sq1, Square sq2) noexcept
    {
        assert(kA1 <= sq1 && sq1 < kSquareNB);
        assert(kA1 <= sq2 && sq2 < kSquareNB);
        return RayBB(sq1, RayBetween(sq1, sq2)) &
               RayBB(sq2, RayBetween(sq2, sq1));
    }

    constexpr std::array<std::array<Bitboard, kSquareNB>, kSquareNB> kBetweenTable = []()
    {
        std::array<std::array<Bitboard, kSquareNB>, kSquareNB> between_table = {};
        for (Square sq1 = kA1; sq1 < kSquareNB; ++sq1)
        {
            for (Square sq2 = kA1; sq2 < kSquareNB; ++sq2)
            {
                between_table[sq1][sq2] = RuntimeBetweenBB(sq1, sq2);
            }
        }
        return between_table;
    }();

    constexpr Bitboard LookupBetweenBB(Square sq1, Square sq2) noexcept
    {
        assert(kA1 <= sq1 && sq1 < kSquareNB);
        assert(kA1 <= sq2 && sq2 < kSquareNB);
        return kBetweenTable[sq1][sq2];
    }

    constexpr Bitboard BetweenBB(Square sq1, Square sq2) noexcept
    {
        return LookupBetweenBB(sq1, sq2);
    }

    template <Direction dir>
    constexpr Bitboard kShiftMask = []()
    {
        Bitboard mask = kEmptyBB;
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            mask |= CanStep(sq, dir) * SquareBB(sq);
        }
        return mask;
    }();

    template <Direction dir>
    constexpr Bitboard ShiftBB(Bitboard bb) noexcept
    {
        if constexpr (dir == 0)
        {
            return bb;
        }
        else if constexpr (dir > 0)
        {
            return (bb & kShiftMask<dir>) << +dir;
        }
        else
        {
            return (bb & kShiftMask<dir>) >> -dir;
        }
    }

    constexpr Bitboard ShiftBB(Bitboard bb, Direction dir) noexcept
    {
        switch (dir)
        {
            case kNorth:          return ShiftBB<kNorth>          (bb);
            case kEast:           return ShiftBB<kEast>           (bb);
            case kSouth:          return ShiftBB<kSouth>          (bb);
            case kWest:           return ShiftBB<kWest>           (bb);
            case kNorthEast:      return ShiftBB<kNorthEast>      (bb);
            case kSouthEast:      return ShiftBB<kSouthEast>      (bb);
            case kSouthWest:      return ShiftBB<kSouthWest>      (bb);
            case kNorthWest:      return ShiftBB<kNorthWest>      (bb);
            case kNorthNorth:     return ShiftBB<kNorthNorth>     (bb);
            case kEastEast:       return ShiftBB<kEastEast>       (bb);
            case kSouthSouth:     return ShiftBB<kSouthSouth>     (bb);
            case kWestWest:       return ShiftBB<kWestWest>       (bb);
            case kNorthNorthEast: return ShiftBB<kNorthNorthEast> (bb);
            case kNorthNorthWest: return ShiftBB<kNorthNorthWest> (bb);
            case kEastEastNorth:  return ShiftBB<kEastEastNorth>  (bb);
            case kEastEastSouth:  return ShiftBB<kEastEastSouth>  (bb);
            case kSouthSouthEast: return ShiftBB<kSouthSouthEast> (bb);
            case kSouthSouthWest: return ShiftBB<kSouthSouthWest> (bb);
            case kWestWestNorth:  return ShiftBB<kWestWestNorth>  (bb);
            case kWestWestSouth:  return ShiftBB<kWestWestSouth>  (bb);
            default:              return ShiftBB<kDirectionNone>  (bb);
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

namespace cohen_chess
{
    using type::bitboard::Bitboard;

    using type::bitboard::kEmptyBB;
    using type::bitboard::kUniverseBB;
    using type::bitboard::kDarkSquaresBB;
    using type::bitboard::kLightSquaresBB;
    using type::bitboard::kRankEdgesBB;
    using type::bitboard::kFileEdgesBB;
    using type::bitboard::kMainDiagBB;
    using type::bitboard::kMainAntiBB;
    using type::bitboard::kEdgesBB;

    using type::bitboard::SquareBB;
    using type::bitboard::RankBB;
    using type::bitboard::FileBB;
    using type::bitboard::DiagBB;
    using type::bitboard::AntiBB;
    using type::bitboard::RayBB;
    using type::bitboard::BetweenBB;
    using type::bitboard::ShiftBB;
    using type::bitboard::MirrorBitboardRank;
    using type::bitboard::MirrorBitboardFile;
    using type::bitboard::MirrorBitboardDiag;
    using type::bitboard::MirrorBitboardAnti;
}

#endif