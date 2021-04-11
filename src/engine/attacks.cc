#include "attacks.h"

#include "../types/direction.h"
#include "../util/bit_util.h"

namespace cohen_chess
{
    namespace attacks
    {
        Bitboard    kPawnAttackTable[kColorNB][kSquareNB];
        Bitboard    kKnightAttackTable[kSquareNB];
        Bitboard    kKingAttackTable[kSquareNB];
        // Bitboard    kMagicBishopAttackTable[kSquareNB];
        // Bitboard    kMagicRookAttackTable[kSquareNB];
        FancyMagic  kBishopMagicTable[kSquareNB];
        FancyMagic  kRookMagicTable[kSquareNB];

        void InitPawnAttackTable(Bitboard attack_table[kColorNB][kSquareNB])
        {
            for(Square sq = kA1; sq < kSquareNB; ++sq)
            {
                attack_table[kWhite][sq] = SetwisePawnAttacks(kWhite, SquareBB(sq)); 
                attack_table[kBlack][sq] = SetwisePawnAttacks(kBlack, SquareBB(sq)); 
            }
        }

        void InitKnightAttackTable(Bitboard attack_table[kSquareNB])
        {
            for(Square sq = kA1; sq < kSquareNB; ++sq)
            {
                attack_table[sq] = SetwiseKnightAttacks(SquareBB(sq));
            }
        }

        void InitKingAttackTable(Bitboard attack_table[kSquareNB])
        {
            for(Square sq = kA1; sq < kSquareNB; ++sq)
            {
                attack_table[sq] = SetwiseKingAttacks(SquareBB(sq));
            }
        }

        void InitBishopMagicTable(FancyMagic magic_table[kSquareNB], Bitboard magics[kSquareNB], Bitboard* attack_table)
        {
            size_t max_index, occ_index;
            for(Square sq = kA1; sq < kSquareNB; ++sq)
            {
                FancyMagic& fm = magic_table[sq];
                fm.mask     = BishopMask(sq);
                fm.magic    = magics[sq];
                fm.attacks  = sq ? magic_table[sq - 1].attacks + max_index : attack_table;
                // fm.shift    = kSquareNB - PopCount(fm.mask);

                Bitboard occ = kEmptyBB;
                max_index = 0;
                do
                {
                    occ_index = fm.index(occ);
                    max_index = occ_index > max_index ? occ_index : max_index;
                    fm.attacks[occ_index] = IterativeBishopAttacks(occ, sq);
                }
                while(occ = (occ - fm.mask) & fm.mask);
            }
        }

        void InitRookMagicTable(FancyMagic magic_table[kSquareNB], Bitboard magics[kSquareNB], Bitboard* attack_table)
        {
            size_t max_index, occ_index;
            for(Square sq = kA1; sq < kSquareNB; ++sq)
            {
                FancyMagic& fm = kBishopMagicTable[sq];
                fm.mask     = RookMask(sq);
                fm.magic    = magics[sq];
                fm.attacks  = sq ? magic_table[sq - 1].attacks + max_index : attack_table;
                // fm.shift    = kSquareNB - PopCount(fm.mask);

                Bitboard occ = kEmptyBB;
                max_index = 0;
                do
                {
                    occ_index = fm.index(occ);
                    max_index = occ_index > max_index ? occ_index : max_index;
                    fm.attacks[occ_index] = IterativeRookAttacks(occ, sq);
                }
                while(occ = (occ - fm.mask) & fm.mask);
            }
        }
    }
}