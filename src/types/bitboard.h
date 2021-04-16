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

    constexpr Bitboard ComputeSquareBB(Square sq)
    {
        constexpr Bitboard kBitboardSquareA1 = 0x0000000000000001;
        return kBitboardSquareA1 << sq;
    }

    constexpr Bitboard LookupSquareBB(Square sq)
    {
        constexpr std::array<Bitboard, kSquareNB> kSquareBitboards = []
        {
            std::array<Bitboard, kSquareNB> square_bitboards;
            for (Square sq = kA1; sq < kSquareNB; ++sq)
            {
                square_bitboards[sq] = ComputeSquareBB(sq);
            }
            return square_bitboards;
        }();
        return kSquareBitboards[sq];
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
        constexpr std::array<Bitboard, kRankNB> kRankBitboards = []
        {
            std::array<Bitboard, kRankNB> rank_bitboards;
            for (Rank rank = kRank1; rank < kRankNB; ++rank)
            {
                rank_bitboards[rank] = ComputeRankBB(rank);
            }
            return rank_bitboards;
        }();
        return kRankBitboards[rank];
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
        constexpr std::array<Bitboard, kFileNB> kFileBitboards = []
        {
            std::array<Bitboard, kFileNB> file_bitboards;
            for (File file = kFileA; file < kFileNB; ++file)
            {
                file_bitboards[file] = ComputeFileBB(file);
            }
            return file_bitboards;
        }();
        return kFileBitboards[file];
    }

    constexpr Bitboard FileBB(File file)
    {
        return ComputeFileBB(file);
    }

    constexpr Bitboard DiagBB(Diag diag)
    {
        constexpr std::array<Bitboard, kDiagNB> kDiagBitboards =
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
        return kDiagBitboards[diag];
    }

    constexpr Bitboard AntiBB(Anti anti)
    {
        constexpr std::array<Bitboard, kAntiNB> kAntiBitboards = 
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
        return kAntiBitboards[anti];
    }

    constexpr Bitboard LineBB(Square sq1, Square sq2)
    {
        constexpr std::array<std::array<Bitboard, kSquareNB>, kSquareNB> kLineBitboards = []
        {
            std::array<std::array<Bitboard, kSquareNB>, kSquareNB> line_bitboards;
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
                    line_bitboards[sq1][sq2] = bb;
                    line_bitboards[sq2][sq1] = bb;
                }
            }
            return line_bitboards;
        }();
        return kLineBitboards[sq1][sq2];
    }

    constexpr Bitboard BetweenBB(Square sq1, Square sq2)
    {
        constexpr std::array<std::array<Bitboard, kSquareNB>, kSquareNB> kBetweenBitboards = []
        {
            std::array<std::array<Bitboard, kSquareNB>, kSquareNB> between_bitboards;
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
                    between_bitboards[sq1][sq2] = bb;
                    between_bitboards[sq2][sq1] = bb;
                }
            }
            return between_bitboards;
        }();
        return kBetweenBitboards[sq1][sq2];
    } 

    template <Direction dir>
    constexpr Bitboard ShiftBB(Bitboard bb)
    {
        if (bb == 0)
        {
            return 0;
        }
        else if constexpr (dir == kNorth)
        {
            return (bb & ~RankBB(kRank8)) << +kNorth;
        }
        else if constexpr (dir == kEast)
        {
            return (bb & ~FileBB(kFileH)) << +kEast;
        }
        else if constexpr (dir == kSouth)
        {
            return (bb & ~RankBB(kRank1)) >> -kSouth;
        }
        else if constexpr (dir == kWest)
        {
            return (bb & ~FileBB(kFileA)) >> -kWest;
        }
        else if constexpr (dir == kNorthEast)
        {
            return (bb & ~RankBB(kRank8) & ~FileBB(kFileH)) << +kNorthEast;
        }
        else if constexpr (dir == kNorthWest)
        {
            return (bb & ~RankBB(kRank8) & ~FileBB(kFileA)) << +kNorthWest;
        }
        else if constexpr (dir == kSouthEast)
        {
            return (bb & ~RankBB(kRank1) & ~FileBB(kFileH)) >> -kSouthEast;
        }
        else if constexpr (dir == kSouthWest)
        {
            return (bb & ~RankBB(kRank1) & ~FileBB(kFileA)) >> -kSouthWest;
        }
        else if constexpr (dir == kNorthNorth)
        {
            return (bb & ~RankBB(kRank8) & ~RankBB(kRank7)) << +kNorthNorth;
        }
        else if constexpr (dir == kEastEast)
        {
            return (bb & ~FileBB(kFileH) & ~FileBB(kFileG)) << +kEastEast;
        }
        else if constexpr (dir == kSouthSouth)
        {
            return (bb & ~RankBB(kRank1) & ~RankBB(kRank2)) >> -kSouthSouth;
        }
        else if constexpr (dir == kWestWest)
        {
            return (bb & ~FileBB(kFileA) & ~FileBB(kFileB)) >> -kWestWest;
        }
        else if constexpr (dir == kNorthNorthEast)
        {
            return (bb & ~RankBB(kRank8) & ~RankBB(kRank7) & ~FileBB(kFileH)) << +kNorthNorthEast;
        }
        else if constexpr (dir == kNorthNorthWest)
        {
            return (bb & ~RankBB(kRank8) & ~RankBB(kRank7) & ~FileBB(kFileA)) << +kNorthNorthWest;
        }
        else if constexpr (dir == kEastEastNorth)
        {
            return (bb & ~FileBB(kFileH) & ~FileBB(kFileG) & ~RankBB(kRank8)) << +kEastEastNorth;
        }
        else if constexpr (dir == kEastEastSouth)
        {
            return (bb & ~FileBB(kFileH) & ~FileBB(kFileG) & ~RankBB(kRank1)) >> -kEastEastSouth;
        }
        else if constexpr (dir == kSouthSouthEast)
        {
            return (bb & ~RankBB(kRank1) & ~RankBB(kRank2) & ~FileBB(kFileH)) >> -kSouthSouthEast;
        }
        else if constexpr (dir == kSouthSouthWest)
        {
            return (bb & ~RankBB(kRank1) & ~RankBB(kRank2) & ~FileBB(kFileA)) >> -kSouthSouthWest;
        }
        else if constexpr (dir == kWestWestNorth)
        {
            return (bb & ~FileBB(kFileA) & ~FileBB(kFileB) & ~RankBB(kRank8)) << +kWestWestNorth;
        }
        else if constexpr (dir == kWestWestSouth)
        {
            return (bb & ~FileBB(kFileA) & ~FileBB(kFileB) & ~RankBB(kRank1)) >> -kWestWestSouth;
        }
        else
        {
            return bb;
        }
    }

    template <Direction dir>
    constexpr Bitboard SetwiseRayBB(Bitboard bb)
    {
        Bitboard shift;
        while((shift = ShiftBB<dir>(bb) | bb) != bb)
        {
            bb = shift;
        }
        return bb;
    }

    template <Direction dir>
    constexpr Bitboard SetwiseRayBB(Bitboard bb, Bitboard occ)
    {
        Bitboard shift;
        occ = ShiftBB<dir>(occ);
        while((shift = ShiftBB<dir>(bb) | bb) != bb && (shift & occ) == 0)
        {
            bb = shift;
        }
        return bb;
    }

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
}

#endif