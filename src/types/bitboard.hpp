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

        template <Direction dir>
        constexpr std::array<Bitboard, kSquareNB> kRayTable = []()
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
        }();

        template <>
        constexpr std::array<Bitboard, kSquareNB> kRayTable<kDirectionNone> = {};

        template <Direction shift_dir>
        constexpr Bitboard kShiftMask = [](Direction dir)
        {
            Bitboard mask = kEmptyBB;
            for (Square sq = kA1; sq < kSquareNB; ++sq)
            {
                mask |= CanStep(sq, dir) * (kBitboardSquareA1 << sq);
            }
            return mask;
        }(shift_dir);
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

    constexpr Bitboard SquareBB(Square sq) noexcept
    {
        return bitboard::kSquareTable[sq];
    }

    constexpr Bitboard RankBB(Rank rank) noexcept
    {
        return bitboard::kRankTable[rank];
    }

    constexpr Bitboard FileBB(File file) noexcept
    {
        return bitboard::kFileTable[file];
    }

    constexpr Bitboard DiagBB(Diag diag) noexcept
    {
        return bitboard::kDiagTable[diag];
    }

    constexpr Bitboard AntiBB(Anti anti) noexcept
    {
        return bitboard::kAntiTable[anti];
    }

    constexpr Bitboard LineBB(Square sq1, Square sq2) noexcept
    {
        return bitboard::kLineTable[sq1][sq2];
    }

    constexpr Bitboard BetweenBB(Square sq1, Square sq2) noexcept
    {
        return bitboard::kBetweenTable[sq1][sq2];
    }

    template <Direction dir>
    constexpr Bitboard RayBB(Square sq) noexcept
    {
        return bitboard::kRayTable<dir>[sq];
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

    template <Direction dir>
    constexpr Bitboard ShiftBB(Bitboard bb) noexcept
    {
        if constexpr (dir == 0)
        {
            return bb;
        }
        else if constexpr (dir > 0)
        {
            return (bb & bitboard::kShiftMask<dir>) << +dir;
        }
        else
        {
            return (bb & bitboard::kShiftMask<dir>) >> -dir;
        }
    }
}

#endif