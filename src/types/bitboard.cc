#include "bitboard.h"

namespace cohen_chess
{
    namespace bitboard
    {
        Bitboard kLineBitboards[kSquareNB][kSquareNB];
        Bitboard kBetweenBitboards[kSquareNB][kSquareNB];

        void InitLineBitboards(Bitboard line_bitboards[kSquareNB][kSquareNB])
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
                    line_bitboards[sq1][sq2] = bb;
                    line_bitboards[sq2][sq1] = bb;
                }
            }
        }

        void InitBetweenBitboards(Bitboard between_bitboards[kSquareNB][kSquareNB])
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
                    between_bitboards[sq1][sq2] = bb;
                    between_bitboards[sq2][sq1] = bb;
                }
            }
        }
    }
}
