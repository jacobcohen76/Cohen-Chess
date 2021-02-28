#include "attacks.h"

#include "../types/direction.h"

namespace cohen_chess
{
    namespace attacks
    {
        Bitboard    kPawnAttacks[kColorNB][kSquareNB];
        Bitboard    kKnightAttacks[kSquareNB];
        Bitboard    kKingAttacks[kSquareNB];
        Bitboard    kMagicAttackTable[kSquareNB];
        FancyMagic  kBishopMagics[kSquareNB];
        FancyMagic  kRookMagics[kSquareNB];

        void InitPawnAttacks()
        {
            for(Square sq = kA1; sq < kSquareNB; ++sq)
            {
                kPawnAttacks[kWhite][sq] = kEmptyBB;
                if(IsNormal(sq + kNorthEast) && SquareDistance(sq, sq + kNorthEast) == 2)
                {
                    kPawnAttacks[kWhite][sq] |= SquareBB(sq + kNorthEast);
                }
                if(IsNormal(sq + kNorthWest) && SquareDistance(sq, sq + kNorthWest) == 2)
                {
                    kPawnAttacks[kWhite][sq] |= SquareBB(sq + kNorthWest);
                }
                kPawnAttacks[kBlack][sq] = kEmptyBB;
                if(IsNormal(sq + kSouthEast) && SquareDistance(sq, sq + kSouthEast) == 2)
                {
                    kPawnAttacks[kBlack][sq] |= SquareBB(sq + kSouthEast);
                }
                if(IsNormal(sq + kSouthWest) && SquareDistance(sq, sq + kSouthWest) == 2)
                {
                    kPawnAttacks[kBlack][sq] |= SquareBB(sq + kSouthWest);
                }
            }
        }

        void InitKnightAttacks()
        {
            for(Square sq = kA1; sq < kSquareNB; ++sq)
            {
                kKnightAttacks[sq] = kEmptyBB;
                if(IsNormal(sq + kNorthNorthEast) && SquareDistance(sq, sq + kNorthNorthEast) == 3)
                {
                    kKnightAttacks[sq] |= SquareBB(sq + kNorthNorthEast);
                }
                if(IsNormal(sq + kNorthNorthWest) && SquareDistance(sq, sq + kNorthNorthWest) == 3)
                {
                    kKnightAttacks[sq] |= SquareBB(sq + kNorthNorthWest);
                }
                if(IsNormal(sq + kSouthSouthEast) && SquareDistance(sq, sq + kSouthSouthEast) == 3)
                {
                    kKnightAttacks[sq] |= SquareBB(sq + kSouthSouthEast);
                }
                if(IsNormal(sq + kSouthSouthWest) && SquareDistance(sq, sq + kSouthSouthWest) == 3)
                {
                    kKnightAttacks[sq] |= SquareBB(sq + kSouthSouthWest);
                }
                if(IsNormal(sq + kEastEastNorth) && SquareDistance(sq, sq + kEastEastNorth) == 3)
                {
                    kKnightAttacks[sq] |= SquareBB(sq + kEastEastNorth);
                }
                if(IsNormal(sq + kEastEastSouth) && SquareDistance(sq, sq + kEastEastSouth) == 3)
                {
                    kKnightAttacks[sq] |= SquareBB(sq + kEastEastSouth);
                }
                if(IsNormal(sq + kWestWestNorth) && SquareDistance(sq, sq + kWestWestNorth) == 3)
                {
                    kKnightAttacks[sq] |= SquareBB(sq + kWestWestNorth);
                }
                if(IsNormal(sq + kWestWestSouth) && SquareDistance(sq, sq + kWestWestSouth) == 3)
                {
                    kKnightAttacks[sq] |= SquareBB(sq + kWestWestSouth);
                }
            }
        }

        void InitKingAttacks()
        {
            for(Square sq = kA1; sq < kSquareNB; ++sq)
            {
                kKingAttacks[sq] = kEmptyBB;
                if(IsNormal(sq + kNorth) && SquareDistance(sq, sq + kNorth) == 1)
                {
                    kKingAttacks[sq] |= SquareBB(sq + kNorth);
                }
                if(IsNormal(sq + kEast) && SquareDistance(sq, sq + kEast) == 1)
                {
                    kKingAttacks[sq] |= SquareBB(sq + kEast);
                }
                if(IsNormal(sq + kSouth) && SquareDistance(sq, sq + kSouth) == 1)
                {
                    kKingAttacks[sq] |= SquareBB(sq + kSouth);
                }
                if(IsNormal(sq + kWest) && SquareDistance(sq, sq + kWest) == 1)
                {
                    kKingAttacks[sq] |= SquareBB(sq + kWest);
                }
                if(IsNormal(sq + kNorthEast) && SquareDistance(sq, sq + kNorthEast) == 2)
                {
                    kKingAttacks[sq] |= SquareBB(sq + kNorthEast);
                }
                if(IsNormal(sq + kNorthWest) && SquareDistance(sq, sq + kNorthWest) == 2)
                {
                    kKingAttacks[sq] |= SquareBB(sq + kNorthWest);
                }
                if(IsNormal(sq + kSouthEast) && SquareDistance(sq, sq + kSouthEast) == 2)
                {
                    kKingAttacks[sq] |= SquareBB(sq + kSouthEast);
                }
                if(IsNormal(sq + kSouthWest) && SquareDistance(sq, sq + kSouthWest) == 2)
                {
                    kKingAttacks[sq] |= SquareBB(sq + kSouthWest);
                }
            }
        }

        void InitBishopMagics()
        {
            for(Square sq = kA1; sq < kSquareNB; ++sq)
            {
                FancyMagic& fm = kBishopMagics[sq];
                fm.mask = DiagBB(DiagOf(sq)) | AntiBB(AntiOf(sq)) & ~kEdgesBB;
            }
        }

        void InitRookMagics()
        {
            for(Square sq = kA1; sq < kSquareNB; ++sq)
            {
                FancyMagic& fm = kRookMagics[sq];
                fm.mask = RankBB(RankOf(sq)) | FileBB(FileOf(sq)) & ~kEdgesBB;
            }
        }
    }
}