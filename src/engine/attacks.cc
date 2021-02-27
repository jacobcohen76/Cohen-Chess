#include "attacks.h"

namespace cohen_chess
{
    namespace attacks
    {
        Bitboard    kPseudoAttacks[kPieceTypeNB][kSquareNB];
        Bitboard    kPawnAttacks[kColorNB][kSquareNB];
        Bitboard    kMagicAttackTable[];
        FancyMagic  kBishopMagics[kSquareNB];
        FancyMagic  kRookMagics[kSquareNB];

        void InitPseudoAttacks()
        {
            for(Square sq = kA1; sq < kSquareNB; ++sq)
            {

                kPseudoAttacks[kBishop][sq] = DiagBB(DiagOf(sq)) | AntiBB(AntiOf(sq));
                kPseudoAttacks  [kRook][sq] = RankBB(RankOf(sq)) | FileBB(FileOf(sq));
                kPseudoAttacks [kQueen][sq] = kPseudoAttacks[kBishop][sq] | kPseudoAttacks[kRook][sq];
            }
        }

        void InitPawnAttacks()
        {

        }

        void InitBishopMagics()
        {
            for(Square sq = kA1; sq < kSquareNB; ++sq)
            {
                FancyMagic& fm = kBishopMagics[sq];
                fm.mask = PseudoAttacks(kBishop, sq) & ~kEdgesBB;
            }
        }

        void InitRookMagics()
        {
            for(Square sq = kA1; sq < kSquareNB; ++sq)
            {
                FancyMagic& fm = kRookMagics[sq];
                fm.mask = PseudoAttacks(kRook, sq) & ~kEdgesBB;
            }
        }
    }
}