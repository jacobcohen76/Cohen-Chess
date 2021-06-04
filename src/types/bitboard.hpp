#ifndef COHEN_CHESS_TYPES_BITBOARD_HPP_INCLUDED
#define COHEN_CHESS_TYPES_BITBOARD_HPP_INCLUDED

#include <array>
#include <cassert>
#include <cstdint>

#include <types/anti.hpp>
#include <types/diag.hpp>
#include <types/direction.hpp>
#include <types/file.hpp>
#include <types/rank.hpp>
#include <types/square.hpp>
#include <util/bits.hpp>

namespace cohen_chess
{
    namespace bitboard
    {
        using Bitboard = uint64_t;

        constexpr Bitboard kEmptyBB        = 0x0000000000000000;
        constexpr Bitboard kUniverseBB     = 0xFFFFFFFFFFFFFFFF;
        constexpr Bitboard kDarkSquaresBB  = 0xAA55AA55AA55AA55;
        constexpr Bitboard kLightSquaresBB = 0x55AA55AA55AA55AA;
        constexpr Bitboard kRankEdgesBB    = 0x8181818181818181;
        constexpr Bitboard kFileEdgesBB    = 0xFF000000000000FF;
        constexpr Bitboard kEdgesBB        = 0xFF818181818181FF;

        constexpr Bitboard SquareBB(Square sq) noexcept
        {
            assert(kA1 <= sq && sq < kSquareNB);
            constexpr Bitboard kBitboardA1 = 0x0000000000000001;
            return kBitboardA1 << sq;
        }

        constexpr Bitboard RankBB(Rank rank) noexcept
        {
            assert(kRank1 <= rank && rank < kRankNB);
            constexpr Bitboard kBitboardRank1 = 0x00000000000000FF;
            return kBitboardRank1 << (rank << 3);
        }

        constexpr Bitboard FileBB(File file) noexcept
        {
            assert(kFileA <= file && file < kFileNB);
            constexpr Bitboard kBitboardFileA = 0x0101010101010101;
            return kBitboardFileA << file;
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

        constexpr Bitboard DiagBB(Diag diag) noexcept
        {
            return kDiagTable[diag];
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

        constexpr Bitboard AntiBB(Anti anti) noexcept
        {
            return kAntiTable[anti];
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
            if (dir > 0)
            {
                Bitboard ray_bb = RayBB(sq, dir);
                int blocker = BitScanForward((occ & ray_bb) | 0x8000000000000000);
                return ray_bb ^ RayBB(blocker, dir);
            }
            else
            {
                Bitboard ray_bb = RayBB(sq, dir);
                int blocker = BitScanReverse((occ & ray_bb) | 0x0000000000000001);
                return ray_bb ^ RayBB(blocker, dir);
            }
        }

        constexpr std::array<std::array<Bitboard, kSquareNB>, kSquareNB> kBetweenTable = []()
        {
            std::array<std::array<Bitboard, kSquareNB>, kSquareNB> between_table = {};
            for (Square sq1 = kA1; sq1 < kSquareNB; ++sq1)
            {
                for (Square sq2 = kA1; sq2 < kSquareNB; ++sq2)
                {
                    between_table[sq1][sq2] = RayBB(sq1, RayBetween(sq1, sq2)) &
                                              RayBB(sq2, RayBetween(sq2, sq1));
                }
            }
            return between_table;
        }();

        constexpr Bitboard BetweenBB(Square sq1, Square sq2) noexcept
        {
            return kBetweenTable[sq1][sq2];
        }

        template <Direction shift_dir>
        constexpr Bitboard kShiftMask = [](Direction dir)
        {
            Bitboard mask = kEmptyBB;
            for (Square sq = kA1; sq < kSquareNB; ++sq)
            {
                mask |= CanStep(sq, dir) * SquareBB(sq);
            }
            return mask;
        }(shift_dir);

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

    using bitboard::Bitboard;

    using bitboard::kEmptyBB;
    using bitboard::kUniverseBB;
    using bitboard::kDarkSquaresBB;
    using bitboard::kLightSquaresBB;
    using bitboard::kRankEdgesBB;
    using bitboard::kFileEdgesBB;
    using bitboard::kEdgesBB;

    using bitboard::SquareBB;
    using bitboard::RankBB;
    using bitboard::FileBB;
    using bitboard::DiagBB;
    using bitboard::AntiBB;
    using bitboard::RayBB;
    using bitboard::BetweenBB;
    using bitboard::ShiftBB;
    using bitboard::MirrorBitboardRank;
    using bitboard::MirrorBitboardFile;
    using bitboard::MirrorBitboardDiag;
    using bitboard::MirrorBitboardAnti;
}

#endif