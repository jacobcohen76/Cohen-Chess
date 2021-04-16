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

    constexpr Bitboard BishopMask(Square sq)
    {
        return (DiagBB(DiagOf(sq)) | AntiBB(AntiOf(sq)) & ~SquareBB(sq)) & ~kEdgesBB;
    }

    constexpr Bitboard RookMask(Square sq)
    {
        return ((RankBB(RankOf(sq)) & ~kRankEdgesBB) | (FileBB(FileOf(sq)) & ~kFileEdgesBB)) & ~SquareBB(sq);
    }

    constexpr Bitboard SetwisePawnAttacks(Color side, Bitboard pawn_set)
    {
        if(side == kWhite)
        {
            return ShiftBB<kNorthEast>(pawn_set) | ShiftBB<kNorthWest>(pawn_set);
        }
        else
        {
            return ShiftBB<kSouthEast>(pawn_set) | ShiftBB<kSouthWest>(pawn_set);
        }
    }

    constexpr Bitboard SetwiseKnightAttacks(Bitboard knight_set)
    {
        return ShiftBB<kNorthNorthEast>(knight_set) | ShiftBB<kEastEastNorth>(knight_set) |
               ShiftBB<kNorthNorthWest>(knight_set) | ShiftBB<kEastEastSouth>(knight_set) |
               ShiftBB<kSouthSouthEast>(knight_set) | ShiftBB<kWestWestNorth>(knight_set) |
               ShiftBB<kSouthSouthWest>(knight_set) | ShiftBB<kWestWestSouth>(knight_set);
    }

    constexpr Bitboard SetwiseKingAttacks(Bitboard king_set)
    {
        Bitboard attacks = ShiftBB<kEast>(king_set) | ShiftBB<kWest>(king_set);
        king_set |= attacks;
        attacks  |= ShiftBB<kNorth>(king_set) | ShiftBB<kSouth>(king_set);
        return attacks;
    }

    inline Bitboard IterativeBishopAttacks(Bitboard occ, Square sq)
    {
        Bitboard sq_bb = SquareBB(sq);
        return  SetwiseRayBB<kNorthEast>(occ, sq_bb) |
                SetwiseRayBB<kNorthWest>(occ, sq_bb) |
                SetwiseRayBB<kSouthEast>(occ, sq_bb) |
                SetwiseRayBB<kSouthWest>(occ, sq_bb);
    }

    inline Bitboard IterativeRookAttacks(Bitboard occ, Square sq)
    {
        Bitboard sq_bb = SquareBB(sq);
        return  SetwiseRayBB<kNorth>(occ, sq_bb) |
                SetwiseRayBB<kEast> (occ, sq_bb) |
                SetwiseRayBB<kSouth>(occ, sq_bb) |
                SetwiseRayBB<kWest> (occ, sq_bb);
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
}

#endif