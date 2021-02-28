#ifndef COHEN_CHESS_ENGINE_ATTACKS_H_INCLUDED
#define COHEN_CHESS_ENGINE_ATTACKS_H_INCLUDED

#include "../types/bitboard.h"
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
            Bitboard*   attack_ptr;
            uint32_t    shift;

            size_t      index(Bitboard) const;
            Bitboard    attackable(Bitboard) const;
        };

        extern Bitboard     kPawnAttacks[kColorNB][kSquareNB];
        extern Bitboard     kKnightAttacks[kSquareNB];
        extern Bitboard     kKingAttacks[kSquareNB];
        extern Bitboard     kMagicAttackTable[kSquareNB];
        extern FancyMagic   kBishopMagics[kSquareNB];
        extern FancyMagic   kRookMagics[kSquareNB];

        void InitPawnAttacks();
        void InitKnightAttacks();
        void InitKingAttacks();
        void InitBishopMagics();
        void InitRookMagics();

        inline size_t FancyMagic::index(Bitboard occ) const
        {
            return (occ & mask) * magic >> shift;
        }

        inline Bitboard FancyMagic::attackable(Bitboard occ) const
        {
            return attack_ptr[index(occ)];
        }
    }

    inline Bitboard PawnAttacks(Color c, Square sq)
    {
        return attacks::kPawnAttacks[c][sq];
    }

    inline Bitboard KnightAttacks(Square sq)
    {
        return attacks::kKnightAttacks[sq];
    }

    inline Bitboard KingAttacks(Square sq)
    {
        return attacks::kKingAttacks[sq];
    }

    inline Bitboard BishopAttacks(Bitboard occ, Square sq)
    {
        return attacks::kBishopMagics[sq].attackable(occ);
    }

    inline Bitboard RookAttacks(Bitboard occ, Square sq)
    {
        return attacks::kRookMagics[sq].attackable(occ);
    }

    inline Bitboard QueenAttacks(Bitboard occ, Square sq)
    {
        return BishopAttacks(occ, sq) | RookAttacks(occ, sq);    
    }
}

#endif