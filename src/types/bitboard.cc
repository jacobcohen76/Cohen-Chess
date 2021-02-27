#include "bitboard.h"

#include "direction.h"

#include <iostream>

namespace cohen_chess
{
    namespace bitboard
    {
        Bitboard    kLineBitboards[kSquareNB][kSquareNB];
        Bitboard kBetweenBitboards[kSquareNB][kSquareNB];

        void InitLineBitboards()
        {
            for(Square sq1 = kA1; sq1 < kSquareNB; ++sq1)
            {
                for(Square sq2 = sq1; sq2 < kSquareNB; ++sq2)
                {
                    Bitboard bb = kEmptyBB;
                    Direction dir = RayBetween(sq1, sq2);
                    if(dir)
                    {
                        Square itr = sq1;
                        while(itr != sq2)
                        {
                            bb |= SquareBB(itr);
                            itr += dir;
                        }
                        bb |= SquareBB(sq2);
                    }
                    kLineBitboards[sq1][sq2] = bb;
                    kLineBitboards[sq2][sq1] = bb;
                }
            }
        }

        void InitBetweenBitboards()
        {
            for(Square sq1 = kA1; sq1 < kSquareNB; ++sq1)
            {
                for(Square sq2 = sq1; sq2 < kSquareNB; ++sq2)
                {
                    Bitboard bb = kEmptyBB;
                    Direction dir = RayBetween(sq1, sq2);
                    if(dir)
                    {
                        Square itr = sq1 + dir;
                        while(itr != sq2)
                        {
                            bb |= SquareBB(itr);
                            itr += dir;
                        }
                    }
                    kBetweenBitboards[sq1][sq2] = bb;
                    kBetweenBitboards[sq2][sq1] = bb;
                }
            }
        }
    }
};
