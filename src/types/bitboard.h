#ifndef COHEN_CHESS_TYPES_BITBOARD_H_INCLUDED
#define COHEN_CHESS_TYPES_BITBOARD_H_INCLUDED

#include "../util/bit_util.h"

#include "anti.h"
#include "diag.h"
#include "direction.h"
#include "file.h"
#include "rank.h"
#include "square.h"

#include <array>
#include <cstdint>

namespace cohen_chess
{
    typedef uint64_t Bitboard;

    enum : Bitboard
    {
        kEmptyBB        = 0x0000000000000000,
        kUniverseBB     = 0xFFFFFFFFFFFFFFFF,
        kDarkSquaresBB  = 0xAA55AA55AA55AA55,
        kLightSquaresBB = 0x55AA55AA55AA55AA,
        kRankEdgesBB    = 0x8181818181818181,
        kFileEdgesBB    = 0xFF000000000000FF,
        kEdgesBB        = 0xFF818181818181FF,
    };

    constexpr Bitboard MirrorBitboardRank(Bitboard bb)
    {
        return __builtin_bswap64(bb);
    }

    constexpr Bitboard MirrorBitboardFile(Bitboard bb)
    {
        constexpr Bitboard k1 = 0x5555555555555555;
        constexpr Bitboard k2 = 0x3333333333333333;
        constexpr Bitboard k4 = 0x0F0F0F0F0F0F0F0F;
        bb = ((bb >> 1) & k1) | ((bb & k1) << 1);
        bb = ((bb >> 2) & k2) | ((bb & k2) << 2);
        bb = ((bb >> 4) & k4) | ((bb & k4) << 4);
        return bb;
    }

    constexpr Bitboard MirrorBitboardDiag(Bitboard bb)
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

    constexpr Bitboard MirrorBitboardAnti(Bitboard bb)
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

    constexpr Bitboard ComputeSquareBB(Square sq)
    {
        constexpr Bitboard kBitboardSquareA1 = 0x0000000000000001;
        return kBitboardSquareA1 << sq;
    }

    constexpr Bitboard LookupSquareBB(Square sq)
    {
        constexpr std::array<Bitboard, kSquareNB> kSquareTable = []
        {
            std::array<Bitboard, kSquareNB> square_table;
            for (Square sq = kA1; sq < kSquareNB; ++sq)
            {
                square_table[sq] = ComputeSquareBB(sq);
            }
            return square_table;
        }();
        return kSquareTable[sq];
    }

    constexpr Bitboard SquareBB(Square sq)
    {
        return ComputeSquareBB(sq);
    }

    constexpr Bitboard ComputeRankBB(Rank rank)
    {
        constexpr Bitboard kBitboardRank1 = 0x00000000000000FF;
        return kBitboardRank1 << rank;
    }

    constexpr Bitboard LookupRankBB(Rank rank)
    {
        constexpr std::array<Bitboard, kRankNB> kRankTable = []
        {
            std::array<Bitboard, kRankNB> rank_table;
            for (Rank rank = kRank1; rank < kRankNB; ++rank)
            {
                rank_table[rank] = ComputeRankBB(rank);
            }
            return rank_table;
        }();
        return kRankTable[rank];
    }

    constexpr Bitboard RankBB(Rank rank)
    {
        return ComputeRankBB(rank);
    }

    constexpr Bitboard ComputeFileBB(File file)
    {
        constexpr Bitboard kBitboardFileA = 0x0101010101010101;
        return kBitboardFileA << file;
    }

    constexpr Bitboard LookupFileBB(File file)
    {
        constexpr std::array<Bitboard, kFileNB> kFileTable = []
        {
            std::array<Bitboard, kFileNB> file_table;
            for (File file = kFileA; file < kFileNB; ++file)
            {
                file_table[file] = ComputeFileBB(file);
            }
            return file_table;
        }();
        return kFileTable[file];
    }

    constexpr Bitboard FileBB(File file)
    {
        return ComputeFileBB(file);
    }

    constexpr Bitboard DiagBB(Diag diag)
    {
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
        return kDiagTable[diag];
    }

    constexpr Bitboard AntiBB(Anti anti)
    {
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
        return kAntiTable[anti];
    }

    constexpr Bitboard LineBB(Square sq1, Square sq2)
    {
        constexpr std::array<std::array<Bitboard, kSquareNB>, kSquareNB> kLineTable = []
        {
            std::array<std::array<Bitboard, kSquareNB>, kSquareNB> line_table;
            for (Square sq1 = kA1; sq1 < kSquareNB; ++sq1)
            {
                for (Square sq2 = sq1; sq2 < kSquareNB; ++sq2)
                {
                    Bitboard bb = kEmptyBB;
                    Direction dir = RayBetween(sq1, sq2);
                    if (dir)
                    {
                        Square itr = sq1;
                        while (itr != sq2)
                        {
                            bb |= SquareBB(itr);
                            itr += dir;
                        }
                        bb |= SquareBB(sq2);
                    }
                    line_table[sq1][sq2] = bb;
                    line_table[sq2][sq1] = bb;
                }
            }
            return line_table;
        }();
        return kLineTable[sq1][sq2];
    }

    constexpr Bitboard BetweenBB(Square sq1, Square sq2)
    {
        constexpr std::array<std::array<Bitboard, kSquareNB>, kSquareNB> kBetweenTable = []
        {
            std::array<std::array<Bitboard, kSquareNB>, kSquareNB> between_table;
            for (Square sq1 = kA1; sq1 < kSquareNB; ++sq1)
            {
                for (Square sq2 = sq1; sq2 < kSquareNB; ++sq2)
                {
                    Bitboard bb = kEmptyBB;
                    Direction dir = RayBetween(sq1, sq2);
                    if (dir)
                    {
                        Square itr = sq1 + dir;
                        while (itr != sq2)
                        {
                            bb |= SquareBB(itr);
                            itr += dir;
                        }
                    }
                    between_table[sq1][sq2] = bb;
                    between_table[sq2][sq1] = bb;
                }
            }
            return between_table;
        }();
        return kBetweenTable[sq1][sq2];
    }

    template <Direction dir>
    constexpr Bitboard RayBB(Square sq)
    {
        constexpr std::array<Bitboard, kSquareNB> kRayTable = []
        {
            std::array<Bitboard, kSquareNB> ray_table;
            for (Square sq = kA1; sq < kSquareNB; ++sq)
            {
                Bitboard bb = kEmptyBB;
                Square itr = sq;
                while (CanStep(itr, dir))
                {
                    itr += dir;
                    bb |= SquareBB(itr);
                }
                ray_table[sq] = bb;
            }
            return ray_table;
        }();
        return kRayTable[sq];
    }

    template <Direction dir>
    constexpr Bitboard RayBB(Bitboard occ, Square sq)
    {
        Bitboard ray_bb = RayBB<dir>(sq);
        if constexpr (dir > 0)
        {
            int blocker = BitScanForward(occ & ray_bb);
            if (blocker == kSquareNone)
                return ray_bb;
            else
                return ray_bb & LineBB(sq, blocker);
        }
        else
        {
            int blocker = BitScanReverse(occ & ray_bb);
            if (blocker == kSquareNone)
                return ray_bb;
            else
                return ray_bb & LineBB(sq, blocker);
        }
    }

    template <Direction dir>
    constexpr Bitboard ShiftBB(Bitboard bb)
    {
        return bb;
    }

    template <>
    constexpr Bitboard ShiftBB<kNorth>(Bitboard bb)
    {
        return (bb & ~RankBB(kRank8)) << +kNorth;
    }

    template <>
    constexpr Bitboard ShiftBB<kEast>(Bitboard bb)
    {
        return (bb & ~FileBB(kFileH)) << +kEast;
    }

    template <>
    constexpr Bitboard ShiftBB<kSouth>(Bitboard bb)
    {
        return (bb & ~RankBB(kRank1)) >> -kSouth;
    }

    template <>
    constexpr Bitboard ShiftBB<kWest>(Bitboard bb)
    {
        return (bb & ~FileBB(kFileA)) >> -kWest;
    }

    template <>
    constexpr Bitboard ShiftBB<kNorthEast>(Bitboard bb)
    {
        return (bb & ~RankBB(kRank8) & ~FileBB(kFileH)) << +kNorthEast;
    }

    template <>
    constexpr Bitboard ShiftBB<kNorthWest>(Bitboard bb)
    {
        return (bb & ~RankBB(kRank8) & ~FileBB(kFileA)) << +kNorthWest;
    }

    template <>
    constexpr Bitboard ShiftBB<kSouthEast>(Bitboard bb)
    {
        return (bb & ~RankBB(kRank1) & ~FileBB(kFileH)) >> -kSouthEast;
    }

    template <>
    constexpr Bitboard ShiftBB<kSouthWest>(Bitboard bb)
    {
        return (bb & ~RankBB(kRank1) & ~FileBB(kFileA)) >> -kSouthWest;
    }

    template <>
    constexpr Bitboard ShiftBB<kNorthNorth>(Bitboard bb)
    {
        return (bb & ~RankBB(kRank8) & ~RankBB(kRank7)) << +kNorthNorth;
    }

    template <>
    constexpr Bitboard ShiftBB<kEastEast>(Bitboard bb)
    {
        return (bb & ~FileBB(kFileH) & ~FileBB(kFileG)) << +kEastEast;
    }

    template <>
    constexpr Bitboard ShiftBB<kSouthSouth>(Bitboard bb)
    {
        return (bb & ~RankBB(kRank1) & ~RankBB(kRank2)) >> -kSouthSouth;
    }

    template <>
    constexpr Bitboard ShiftBB<kWestWest>(Bitboard bb)
    {
        return (bb & ~FileBB(kFileA) & ~FileBB(kFileB)) >> -kWestWest;
    }

    template <>
    constexpr Bitboard ShiftBB<kNorthNorthEast>(Bitboard bb)
    {
        return (bb & ~RankBB(kRank8) & ~RankBB(kRank7) & ~FileBB(kFileH)) << +kNorthNorthEast;
    }

    template <>
    constexpr Bitboard ShiftBB<kNorthNorthWest>(Bitboard bb)
    {
        return (bb & ~RankBB(kRank8) & ~RankBB(kRank7) & ~FileBB(kFileA)) << +kNorthNorthWest;
    }

    template <>
    constexpr Bitboard ShiftBB<kEastEastNorth>(Bitboard bb)
    {
        return (bb & ~FileBB(kFileH) & ~FileBB(kFileG) & ~RankBB(kRank8)) << +kEastEastNorth;
    }

    template <>
    constexpr Bitboard ShiftBB<kEastEastSouth>(Bitboard bb)
    {
        return (bb & ~FileBB(kFileH) & ~FileBB(kFileG) & ~RankBB(kRank1)) >> -kEastEastSouth;
    }

    template <>
    constexpr Bitboard ShiftBB<kSouthSouthEast>(Bitboard bb)
    {
        return (bb & ~RankBB(kRank1) & ~RankBB(kRank2) & ~FileBB(kFileH)) >> -kSouthSouthEast;
    }

    template <>
    constexpr Bitboard ShiftBB<kSouthSouthWest>(Bitboard bb)
    {
        return (bb & ~RankBB(kRank1) & ~RankBB(kRank2) & ~FileBB(kFileA)) >> -kSouthSouthWest;
    }

    template <>
    constexpr Bitboard ShiftBB<kWestWestNorth>(Bitboard bb)
    {
        return (bb & ~FileBB(kFileA) & ~FileBB(kFileB) & ~RankBB(kRank8)) << +kWestWestNorth;
    }

    template <>
    constexpr Bitboard ShiftBB<kWestWestSouth>(Bitboard bb)
    {
        return (bb & ~FileBB(kFileA) & ~FileBB(kFileB) & ~RankBB(kRank1)) >> -kWestWestSouth;
    }
}

#endif