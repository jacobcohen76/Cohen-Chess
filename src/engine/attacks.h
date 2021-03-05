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
        extern Bitboard     kMagicAttackTable[kSquareNB];
        extern FancyMagic   kBishopMagicTable[kSquareNB];
        extern FancyMagic   kRookMagicTable[kSquareNB];

        void InitPawnAttackTable(Bitboard[kColorNB][kSquareNB]);
        void InitKnightAttackTable(Bitboard[kSquareNB]);
        void InitKingAttackTable(Bitboard[kSquareNB]);
        void InitMagicAttackTable();
        void InitBishopMagicTable();
        void InitRookMagicTable();

        inline size_t FancyMagic::index(Bitboard occ) const
        {
            return (occ & mask) * magic >> shift;
        }

        inline Bitboard FancyMagic::attackable(Bitboard occ) const
        {
            return attacks[index(occ)];
        }
    }

    inline Bitboard PawnAttacks(Color c, Square sq)
    {
        return attacks::kPawnAttackTable[c][sq];
    }

    inline Bitboard KnightAttacks(Square sq)
    {
        return attacks::kKnightAttackTable[sq];
    }

    inline Bitboard KingAttacks(Square sq)
    {
        return attacks::kKingAttackTable[sq];
    }

    inline Bitboard BishopAttacks(Bitboard occ, Square sq)
    {
        return attacks::kBishopMagicTable[sq].attackable(occ);
    }

    inline Bitboard RookAttacks(Bitboard occ, Square sq)
    {
        return attacks::kRookMagicTable[sq].attackable(occ);
    }

    inline Bitboard QueenAttacks(Bitboard occ, Square sq)
    {
        return BishopAttacks(occ, sq) | RookAttacks(occ, sq);    
    }
}

#endif