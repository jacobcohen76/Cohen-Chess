#include "attacks.h"

#include "../types/direction.h"

namespace cohen_chess
{
    namespace attacks
    {
        Bitboard    kPawnAttackTable[kColorNB][kSquareNB];
        Bitboard    kKnightAttackTable[kSquareNB];
        Bitboard    kKingAttackTable[kSquareNB];
        Bitboard    kMagicAttackTable[kSquareNB];
        FancyMagic  kBishopMagicTable[kSquareNB];
        FancyMagic  kRookMagicTable[kSquareNB];

        void InitPawnAttackTable(Bitboard attack_table[kColorNB][kSquareNB])
        {
            for(Square sq = kA1; sq < kSquareNB; ++sq)
            {
                attack_table[kWhite][sq] = (CanStep(sq, kNorthEast) ? SquareBB(sq + kNorthEast) : kEmptyBB)
                                         | (CanStep(sq, kNorthWest) ? SquareBB(sq + kNorthWest) : kEmptyBB);
                
                attack_table[kBlack][sq] = (CanStep(sq, kSouthEast) ? SquareBB(sq + kSouthEast) : kEmptyBB)
                                         | (CanStep(sq, kSouthWest) ? SquareBB(sq + kSouthWest) : kEmptyBB);
            }
        }

        void InitKnightAttackTable(Bitboard attack_table[kSquareNB])
        {
            for(Square sq = kA1; sq < kSquareNB; ++sq)
            {
                attack_table[sq] = (CanStep(sq, kNorthNorthEast) ? SquareBB(sq + kNorthNorthEast) : kEmptyBB)
                                 | (CanStep(sq, kNorthNorthWest) ? SquareBB(sq + kNorthNorthWest) : kEmptyBB)
                                 | (CanStep(sq, kEastEastNorth)  ? SquareBB(sq + kEastEastNorth)  : kEmptyBB)
                                 | (CanStep(sq, kEastEastSouth)  ? SquareBB(sq + kEastEastSouth)  : kEmptyBB)
                                 | (CanStep(sq, kSouthSouthEast) ? SquareBB(sq + kSouthSouthEast) : kEmptyBB)
                                 | (CanStep(sq, kSouthSouthWest) ? SquareBB(sq + kSouthSouthWest) : kEmptyBB)
                                 | (CanStep(sq, kWestWestNorth)  ? SquareBB(sq + kWestWestNorth)  : kEmptyBB)
                                 | (CanStep(sq, kWestWestSouth)  ? SquareBB(sq + kWestWestSouth)  : kEmptyBB);
            }
        }

        void InitKingAttackTable(Bitboard attack_table[kSquareNB])
        {
            for(Square sq = kA1; sq < kSquareNB; ++sq)
            {
                attack_table[sq] = (CanStep(sq, kNorth)     ? SquareBB(sq + kNorth)     : kEmptyBB)
                                 | (CanStep(sq, kEast)      ? SquareBB(sq + kEast)      : kEmptyBB)
                                 | (CanStep(sq, kSouth)     ? SquareBB(sq + kSouth)     : kEmptyBB)
                                 | (CanStep(sq, kWest)      ? SquareBB(sq + kWest)      : kEmptyBB)
                                 | (CanStep(sq, kNorthEast) ? SquareBB(sq + kNorthEast) : kEmptyBB)
                                 | (CanStep(sq, kSouthEast) ? SquareBB(sq + kSouthEast) : kEmptyBB)
                                 | (CanStep(sq, kSouthWest) ? SquareBB(sq + kSouthWest) : kEmptyBB)
                                 | (CanStep(sq, kNorthWest) ? SquareBB(sq + kNorthWest) : kEmptyBB);
            }
        }

        void InitBishopMagicTable()
        {
            for(Square sq = kA1; sq < kSquareNB; ++sq)
            {
                FancyMagic& fm = kBishopMagicTable[sq];
                fm.mask = DiagBB(DiagOf(sq)) | AntiBB(AntiOf(sq)) & ~SquareBB(sq) & ~kEdgesBB;
            }
        }

        void InitRookMagicTable()
        {
            for(Square sq = kA1; sq < kSquareNB; ++sq)
            {
                FancyMagic& fm = kBishopMagicTable[sq];
                fm.mask = RankBB(RankOf(sq)) | FileBB(FileOf(sq)) & ~SquareBB(sq) & ~kEdgesBB;
            }
        }
    }
}