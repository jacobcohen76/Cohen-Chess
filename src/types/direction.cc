#include "direction.h"

namespace cohen_chess
{
    namespace direction
    {
        Direction kRayBetween[kSquareNB][kSquareNB];

        void InitRayBetween()
        {
            for(Square sq1 = kA1; sq1 < kSquareNB; ++sq1)
            {
                for(Square sq2 = kA1; sq2 < kSquareNB; ++sq2)
                {
                    if(sq1 == sq2)
                    {
                        kRayBetween[sq1][sq2] = kDirectionNone;
                    }
                    else if(RankOf(sq1) == RankOf(sq2))
                    {
                        kRayBetween[sq1][sq2] = (sq1 < sq2) ? kEast : kWest;
                    }
                    else if(FileOf(sq1) == FileOf(sq2))
                    {
                        kRayBetween[sq1][sq2] = (sq1 < sq2) ? kNorth : kSouth;
                    }
                    else if(DiagOf(sq1) == DiagOf(sq2))
                    {
                        kRayBetween[sq1][sq2] = (sq1 < sq2) ? kNorthEast : kSouthWest;
                    }
                    else if(AntiOf(sq1) == AntiOf(sq2))
                    {
                        kRayBetween[sq1][sq2] = (sq1 < sq2) ? kNorthWest : kSouthEast;
                    }
                    else
                    {
                        kRayBetween[sq1][sq2] = kDirectionNone;
                    }
                }
            }
        }
    };
};
