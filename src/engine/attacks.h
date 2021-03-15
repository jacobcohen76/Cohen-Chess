#ifndef COHEN_CHESS_ENGINE_ATTACKS_H_INCLUDED
#define COHEN_CHESS_ENGINE_ATTACKS_H_INCLUDED

#include "../types/bitboard.h"
#include "../types/direction.h"
#include "../types/piece_type.h"
#include "../types/square.h"

namespace cohen_chess
{
    namespace attacks
    {
        /**
         * https://www.chessprogramming.org/Magic_Bitboards#Fancy
         */
        struct FancyMagic
        {
            Bitboard    mask;
            Bitboard    magic;
            Bitboard*   attacks;
            uint32_t    shift;

            size_t      index(Bitboard) const;
            Bitboard    attackable(Bitboard) const;
        };

        extern Bitboard     kPawnAttackTable[kColorNB][kSquareNB];
        extern Bitboard     kKnightAttackTable[kSquareNB];
        extern Bitboard     kKingAttackTable[kSquareNB];
        // extern Bitboard     kMagicBishopAttackTable[kSquareNB];
        // extern Bitboard     kMagicRookAttackTable[kSquareNB];
        extern FancyMagic   kBishopMagicTable[kSquareNB];
        extern FancyMagic   kRookMagicTable[kSquareNB];

        void InitPawnAttackTable(Bitboard[kColorNB][kSquareNB]);
        void InitKnightAttackTable(Bitboard[kSquareNB]);
        void InitKingAttackTable(Bitboard[kSquareNB]);
        void InitBishopMagicTable(FancyMagic[kSquareNB], Bitboard[kSquareNB], Bitboard*);
        void InitRookMagicTable(FancyMagic[kSquareNB], Bitboard[kSquareNB], Bitboard*);

        inline size_t FancyMagic::index(Bitboard occ) const
        {
            return (occ & mask) * magic >> shift;
        }

        inline Bitboard FancyMagic::attackable(Bitboard occ) const
        {
            return attacks[index(occ)];
        }
    }

    constexpr Bitboard RelevantOccBishop(Square sq)
    {
        return (DiagBB(DiagOf(sq)) | AntiBB(AntiOf(sq)) & ~SquareBB(sq)) & ~kEdgesBB;
    }

    constexpr Bitboard RelevantOccRook(Square sq)
    {
        return ((RankBB(RankOf(sq)) & ~kRankEdgesBB) | (FileBB(FileOf(sq)) & ~kFileEdgesBB)) & ~SquareBB(sq);
    }

    constexpr Bitboard ComputePawnAttacks(Color c, Square sq)
    {
        if(c == kWhite)
        {

        }
        else
        {

        }
    }

    constexpr Bitboard ComputeKnightAttacks(Square sq)
    {
        return  ((SquareBB(sq) & ~RankBB(kRank8) & ~RankBB(kRank7) & ~FileBB(kFileH)) << +(kNorth + kNorth + kEast)) |
                ((SquareBB(sq) & ~RankBB(kRank8) & ~RankBB(kRank7) & ~FileBB(kFileA)) << +(kNorth + kNorth + kWest)) |
                ((SquareBB(sq) & ~RankBB(kRank8) & ~FileBB(kFileH) & ~FileBB(kFileG)) << +(kNorth + kEast  + kEast)) |
                ((SquareBB(sq) & ~RankBB(kRank8) & ~FileBB(kFileA) & ~FileBB(kFileB)) << +(kNorth + kWest  + kWest)) |
                ((SquareBB(sq) & ~RankBB(kRank1) & ~RankBB(kRank2) & ~FileBB(kFileH)) >> -(kSouth + kSouth + kEast)) |
                ((SquareBB(sq) & ~RankBB(kRank1) & ~RankBB(kRank2) & ~FileBB(kFileA)) >> -(kSouth + kSouth + kWest)) |
                ((SquareBB(sq) & ~RankBB(kRank1) & ~FileBB(kFileH) & ~FileBB(kFileG)) >> -(kSouth + kEast  + kEast)) |
                ((SquareBB(sq) & ~RankBB(kRank1) & ~FileBB(kFileA) & ~FileBB(kFileB)) >> -(kSouth + kWest  + kWest));
    }

    constexpr Bitboard ComputeKingAttacks(Square sq)
    {
        return  ((SquareBB(sq) & ~RankBB(kRank8))                   << +(kNorth))         |
                ((SquareBB(sq) & ~FileBB(kFileH))                   << +(kEast))          |
                ((SquareBB(sq) & ~RankBB(kRank1))                   >> -(kSouth))         |
                ((SquareBB(sq) & ~FileBB(kFileA))                   >> -(kWest))          |
                ((SquareBB(sq) & ~RankBB(kRank8) & ~FileBB(kFileH)) << +(kNorth + kEast)) |
                ((SquareBB(sq) & ~RankBB(kRank8) & ~FileBB(kFileA)) << +(kNorth + kWest)) |
                ((SquareBB(sq) & ~RankBB(kRank1) & ~FileBB(kFileH)) >> -(kSouth + kEast)) |
                ((SquareBB(sq) & ~RankBB(kRank1) & ~FileBB(kFileA)) >> -(kSouth + kWest));
    }

    inline Bitboard IterativeBishopAttacks(Bitboard occ, Square sq)
    {
        return  RayBB(occ, sq, kNorthEast) |
                RayBB(occ, sq, kSouthWest) |
                RayBB(occ, sq, kSouthEast) |
                RayBB(occ, sq, kNorthWest);
    }

    inline Bitboard IterativeRookAttacks(Bitboard occ, Square sq)
    {
        return  RayBB(occ, sq, kNorth) |
                RayBB(occ, sq, kEast)  |
                RayBB(occ, sq, kSouth) |
                RayBB(occ, sq, kWest);
    }

    inline Bitboard IterativeQueenAttacks(Bitboard occ, Square sq)
    {
        return IterativeBishopAttacks(occ, sq) | IterativeRookAttacks(occ, sq);
    }

    inline Bitboard LookupPawnAttacks(Color c, Square sq)
    {
        return attacks::kPawnAttackTable[c][sq];
    }

    inline Bitboard LookupKnightAttacks(Square sq)
    {
        return attacks::kKnightAttackTable[sq];
    }

    inline Bitboard LookupKingAttacks(Square sq)
    {
        return attacks::kKingAttackTable[sq];
    }

    inline Bitboard MagicBishopAttacks(Bitboard occ, Square sq)
    {
        return attacks::kBishopMagicTable[sq].attackable(occ);
    }

    inline Bitboard MagicRookAttacks(Bitboard occ, Square sq)
    {
        return attacks::kRookMagicTable[sq].attackable(occ);
    }

    inline Bitboard MagicQueenAttacks(Bitboard occ, Square sq)
    {
        return MagicBishopAttacks(occ, sq) | MagicRookAttacks(occ, sq);    
    }

    constexpr auto PawnAttacks      = LookupPawnAttacks;
    constexpr auto KnightAttacks    = LookupKnightAttacks;
    constexpr auto BishopAttacks    = MagicBishopAttacks;
    constexpr auto RookAttacks      = MagicRookAttacks;
    constexpr auto QueenAttacks     = MagicQueenAttacks;
    constexpr auto KingAttacks      = LookupKingAttacks;
}

#endif