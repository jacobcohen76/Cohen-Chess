#ifndef COHEN_CHESS_TYPES_BITBOARD_H_INCLUDED
#define COHEN_CHESS_TYPES_BITBOARD_H_INCLUDED

#include "../util/bit_util.h"

#include "anti.h"
#include "diag.h"
#include "direction.h"
#include "file.h"
#include "rank.h"
#include "square.h"

#include <cstdint>

namespace cohen_chess
{
    typedef uint64_t Bitboard;

    constexpr const Bitboard kEmptyBB        = 0x0000000000000000;
    constexpr const Bitboard kUniverseBB     = 0xFFFFFFFFFFFFFFFF;
    constexpr const Bitboard kDarkSquaresBB  = 0xAA55AA55AA55AA55;
    constexpr const Bitboard kLightSquaresBB = 0x55AA55AA55AA55AA;
    constexpr const Bitboard kRankEdgesBB    = 0x8181818181818181;
    constexpr const Bitboard kFileEdgesBB    = 0xFF000000000000FF;
    constexpr const Bitboard kEdgesBB        = 0xFF818181818181FF;

    constexpr Bitboard MirrorRank(Bitboard bb)
    {
        return Bitboard(__builtin_bswap64(bb));
    }

    constexpr Bitboard MirrorFile(Bitboard bb)
    {
        constexpr const Bitboard k1 = 0x5555555555555555;
        constexpr const Bitboard k2 = 0x3333333333333333;
        constexpr const Bitboard k4 = 0x0F0F0F0F0F0F0F0F;
        bb = ((bb >> 1) & k1) | ((bb & k1) << 1);
        bb = ((bb >> 2) & k2) | ((bb & k2) << 2);
        bb = ((bb >> 4) & k4) | ((bb & k4) << 4);
        return bb;
    }

    constexpr Bitboard MirrorDiag(Bitboard bb)
    {
        constexpr const Bitboard k1 = 0x5500550055005500;
        constexpr const Bitboard k2 = 0x3333000033330000;
        constexpr const Bitboard k4 = 0x0F0F0F0F00000000;
        Bitboard tr = kEmptyBB;
        tr = ((bb << 28) ^ bb) & k4;
        bb = ((tr >> 28) ^ tr) ^ bb;
        tr = ((bb << 14) ^ bb) & k2;
        bb = ((tr >> 14) ^ tr) ^ bb;
        tr = ((bb <<  7) ^ bb) & k1;
        bb = ((tr >>  7) ^ tr) ^ bb;
        return bb;
    }

    constexpr Bitboard MirrorAnti(Bitboard bb)
    {
        constexpr const Bitboard k1 = 0xAA00AA00AA00AA00;
        constexpr const Bitboard k2 = 0xCCCC0000CCCC0000;
        constexpr const Bitboard k4 = 0xF0F0F0F00F0F0F0F;
        Bitboard tr = kEmptyBB;
        tr =   (bb << 36) ^ bb;
        bb = (((bb >> 36) ^ tr) & k4) ^ bb;
        tr =  ((bb << 18) ^ bb) & k2;
        bb =  ((tr >> 18) ^ tr) ^ bb;
        tr =  ((bb <<  9) ^ bb) & k1;
        bb =  ((tr >>  9) ^ tr) ^ bb;
        return bb;
    }

    constexpr Bitboard SquareBB(Square sq)
    {
        return Bitboard(0x0000000000000001) << sq;
    }

    constexpr Bitboard RankBB(Rank rank)
    {
        return Bitboard(0x00000000000000FF) << (rank << 3);
    }

    constexpr Bitboard FileBB(File file)
    {
        return Bitboard(0x0101010101010101) << file;
    }

    inline Bitboard DiagBB(Diag diag)
    {
        static const Bitboard kDiagBitboards[kDiagNB]
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

    inline Bitboard AntiBB(Anti anti)
    {
        static const Bitboard kAntiBitboards[kAntiNB]
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

    namespace bitboard
    {
        extern Bitboard kLineBitboards[kSquareNB][kSquareNB];
        extern Bitboard kBetweenBitboards[kSquareNB][kSquareNB];
        
        void InitLineBitboards(Bitboard[kSquareNB][kSquareNB]);
        void InitBetweenBitboards(Bitboard[kSquareNB][kSquareNB]);
        void Init();
    };

    inline Bitboard LineBB(Square sq1, Square sq2)
    {
        return bitboard::kLineBitboards[sq1][sq2];
    }

    inline Bitboard BetweenBB(Square sq1, Square sq2)
    {
        return bitboard::kBetweenBitboards[sq1][sq2];
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
        while((shift = ShiftBB<dir>(bb) | bb) != bb && !(shift & occ))
        {
            bb = shift;
        }
        return bb;
    }
}

#endif