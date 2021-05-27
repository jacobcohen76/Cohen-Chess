#ifndef COHEN_CHESS_TYPES_BITBOARD_HPP_INCLUDED
#define COHEN_CHESS_TYPES_BITBOARD_HPP_INCLUDED

#include <types/anti.hpp>
#include <types/diag.hpp>
#include <types/direction.hpp>
#include <types/file.hpp>
#include <types/rank.hpp>
#include <types/square.hpp>
#include <util/bit_util.hpp>

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

    namespace bitboard
    {
        constexpr Bitboard kBitboardSquareA1 = 0x0000000000000001;
        constexpr Bitboard kBitboardRank1    = 0x00000000000000FF;
        constexpr Bitboard kBitboardFileA    = 0x0101010101010101;

        constexpr std::array<Bitboard, kSquareNB> kSquareTable = []()
        {
            std::array<Bitboard, kSquareNB> square_table = {};
            for (Square sq = kA1; sq < kSquareNB; ++sq)
            {
                square_table[sq] = kBitboardSquareA1 << sq;
            }
            return square_table;
        }();

        constexpr std::array<Bitboard, kRankNB> kRankTable = []()
        {
            std::array<Bitboard, kRankNB> rank_table = {};
            for (Rank rank = kRank1; rank < kRankNB; ++rank)
            {
                rank_table[rank] = kBitboardRank1 << (rank << 3);
            }
            return rank_table;
        }();

        constexpr std::array<Bitboard, kFileNB> kFileTable = []()
        {
            std::array<Bitboard, kFileNB> file_table = {};
            for (File file = kFileA; file < kFileNB; ++file)
            {
                file_table[file] = kBitboardFileA << file;
            }
            return file_table;
        }();
        
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

        constexpr std::array<std::array<Bitboard, kSquareNB>, kSquareNB> kLineTable = []()
        {
            std::array<std::array<Bitboard, kSquareNB>, kSquareNB> line_table = {};
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
                            bb |= kBitboardSquareA1 << itr;
                            itr += dir;
                        }
                        bb |= kBitboardSquareA1 << itr;
                    }
                    line_table[sq1][sq2] = bb;
                    line_table[sq2][sq1] = bb;
                }
            }
            return line_table;
        }();
        
        constexpr std::array<std::array<Bitboard, kSquareNB>, kSquareNB> kBetweenTable = []()
        {
            std::array<std::array<Bitboard, kSquareNB>, kSquareNB> between_table = {};
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
                            bb |= kBitboardSquareA1 << itr;
                            itr += dir;
                        }
                    }
                    between_table[sq1][sq2] = bb;
                    between_table[sq2][sq1] = bb;
                }
            }
            return between_table;
        }();

        consteval std::array<Bitboard, kSquareNB> MakeRayTable(Direction dir)
        {
            std::array<Bitboard, kSquareNB> ray_table = {};
            for (Square sq = kA1; sq < kSquareNB; ++sq)
            {
                Bitboard bb = kEmptyBB;
                Square itr = sq;
                while (CanStep(itr, dir))
                {
                    itr += dir;
                    bb |= kBitboardSquareA1 << itr;
                }
                ray_table[sq] = bb;
            }
            return ray_table;
        }

        constexpr std::array<Bitboard, kSquareNB> kRayNorthTable          = MakeRayTable(kNorth);
        constexpr std::array<Bitboard, kSquareNB> kRaySouthTable          = MakeRayTable(kSouth);
        constexpr std::array<Bitboard, kSquareNB> kRayEastTable           = MakeRayTable(kEast);
        constexpr std::array<Bitboard, kSquareNB> kRayWestTable           = MakeRayTable(kWest);
        constexpr std::array<Bitboard, kSquareNB> kRayNorthEastTable      = MakeRayTable(kNorthEast);
        constexpr std::array<Bitboard, kSquareNB> kRayNorthWestTable      = MakeRayTable(kNorthWest);
        constexpr std::array<Bitboard, kSquareNB> kRaySouthEastTable      = MakeRayTable(kSouthEast);
        constexpr std::array<Bitboard, kSquareNB> kRaySouthWestTable      = MakeRayTable(kSouthWest);
        constexpr std::array<Bitboard, kSquareNB> kRayNorthNorthTable     = MakeRayTable(kNorthNorth);
        constexpr std::array<Bitboard, kSquareNB> kRaySouthSouthTable     = MakeRayTable(kSouthSouth);
        constexpr std::array<Bitboard, kSquareNB> kRayEastEastTable       = MakeRayTable(kEastEast);
        constexpr std::array<Bitboard, kSquareNB> kRayWestWestTable       = MakeRayTable(kWestWest);
        constexpr std::array<Bitboard, kSquareNB> kRayNorthNorthEastTable = MakeRayTable(kNorthNorthEast);
        constexpr std::array<Bitboard, kSquareNB> kRayNorthNorthWestTable = MakeRayTable(kNorthNorthWest);
        constexpr std::array<Bitboard, kSquareNB> kRaySouthSouthEastTable = MakeRayTable(kSouthSouthEast);
        constexpr std::array<Bitboard, kSquareNB> kRaySouthSouthWestTable = MakeRayTable(kSouthSouthWest);
        constexpr std::array<Bitboard, kSquareNB> kRayEastEastNorthTable  = MakeRayTable(kEastEastNorth);
        constexpr std::array<Bitboard, kSquareNB> kRayEastEastSouthTable  = MakeRayTable(kEastEastSouth);
        constexpr std::array<Bitboard, kSquareNB> kRayWestWestNorthTable  = MakeRayTable(kWestWestNorth);
        constexpr std::array<Bitboard, kSquareNB> kRayWestWestSouthTable  = MakeRayTable(kWestWestSouth);
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

    constexpr Bitboard SquareBB(Square sq)
    {
        return bitboard::kSquareTable[sq];
    }

    constexpr Bitboard RankBB(Rank rank)
    {
        return bitboard::kRankTable[rank];
    }

    constexpr Bitboard FileBB(File file)
    {
        return bitboard::kFileTable[file];
    }

    constexpr Bitboard DiagBB(Diag diag)
    {
        return bitboard::kDiagTable[diag];
    }

    constexpr Bitboard AntiBB(Anti anti)
    {
        return bitboard::kAntiTable[anti];
    }

    constexpr Bitboard LineBB(Square sq1, Square sq2)
    {
        return bitboard::kLineTable[sq1][sq2];
    }

    constexpr Bitboard BetweenBB(Square sq1, Square sq2)
    {
        return bitboard::kBetweenTable[sq1][sq2];
    }

    template <Direction dir>
    constexpr Bitboard RayBB(Square sq)
    {
        return kEmptyBB;
    }

    template <>
    constexpr Bitboard RayBB<kNorth>(Square sq)
    {
        return bitboard::kRayNorthTable[sq];
    }

    template <>
    constexpr Bitboard RayBB<kSouth>(Square sq)
    {
        return bitboard::kRaySouthTable[sq];
    }

    template <>
    constexpr Bitboard RayBB<kEast>(Square sq)
    {
        return bitboard::kRayEastTable[sq];
    }

    template <>
    constexpr Bitboard RayBB<kWest>(Square sq)
    {
        return bitboard::kRayWestTable[sq];
    }

    template <>
    constexpr Bitboard RayBB<kNorthEast>(Square sq)
    {
        return bitboard::kRayNorthEastTable[sq];
    }

    template <>
    constexpr Bitboard RayBB<kNorthWest>(Square sq)
    {
        return bitboard::kRayNorthWestTable[sq];
    }

    template <>
    constexpr Bitboard RayBB<kSouthEast>(Square sq)
    {
        return bitboard::kRaySouthEastTable[sq];
    }

    template <>
    constexpr Bitboard RayBB<kSouthWest>(Square sq)
    {
        return bitboard::kRaySouthWestTable[sq];
    }

    template <>
    constexpr Bitboard RayBB<kNorthNorth>(Square sq)
    {
        return bitboard::kRayNorthNorthTable[sq];
    }

    template <>
    constexpr Bitboard RayBB<kSouthSouth>(Square sq)
    {
        return bitboard::kRaySouthSouthTable[sq];
    }

    template <>
    constexpr Bitboard RayBB<kEastEast>(Square sq)
    {
        return bitboard::kRayEastEastTable[sq];
    }

    template <>
    constexpr Bitboard RayBB<kWestWest>(Square sq)
    {
        return bitboard::kRayWestWestTable[sq];
    }

    template <>
    constexpr Bitboard RayBB<kNorthNorthEast>(Square sq)
    {
        return bitboard::kRayNorthNorthEastTable[sq];
    }

    template <>
    constexpr Bitboard RayBB<kNorthNorthWest>(Square sq)
    {
        return bitboard::kRayNorthNorthWestTable[sq];
    }

    template <>
    constexpr Bitboard RayBB<kSouthSouthEast>(Square sq)
    {
        return bitboard::kRaySouthSouthEastTable[sq];
    }

    template <>
    constexpr Bitboard RayBB<kSouthSouthWest>(Square sq)
    {
        return bitboard::kRaySouthSouthWestTable[sq];
    }

    template <>
    constexpr Bitboard RayBB<kEastEastNorth>(Square sq)
    {
        return bitboard::kRayEastEastNorthTable[sq];
    }

    template <>
    constexpr Bitboard RayBB<kEastEastSouth>(Square sq)
    {
        return bitboard::kRayEastEastSouthTable[sq];
    }

    template <>
    constexpr Bitboard RayBB<kWestWestNorth>(Square sq)
    {
        return bitboard::kRayWestWestNorthTable[sq];
    }

    template <>
    constexpr Bitboard RayBB<kWestWestSouth>(Square sq)
    {
        return bitboard::kRayWestWestSouthTable[sq];
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