#include "direction.h"

namespace cohen_chess
{
    namespace direction
    {
        Direction kRayBetween[kSquareNB][kSquareNB];

        void InitRayBetween(Direction ray_between[kSquareNB][kSquareNB])
        {
            for(Square sq1 = kA1; sq1 < kSquareNB; ++sq1)
            {
                for(Square sq2 = sq1; sq2 < kSquareNB; ++sq2)
                {
                    if(sq1 == sq2)
                    {
                        ray_between[sq1][sq2] = kDirectionNone;
                        ray_between[sq2][sq1] = kDirectionNone;
                    }
                    else if(RankOf(sq1) == RankOf(sq2))
                    {
                        ray_between[sq1][sq2] = (sq1 < sq2) ? kEast : kWest;
                        ray_between[sq2][sq1] = -ray_between[sq1][sq2];
                    }
                    else if(FileOf(sq1) == FileOf(sq2))
                    {
                        ray_between[sq1][sq2] = (sq1 < sq2) ? kNorth : kSouth;
                        ray_between[sq2][sq1] = -ray_between[sq1][sq2];
                    }
                    else if(DiagOf(sq1) == DiagOf(sq2))
                    {
                        ray_between[sq1][sq2] = (sq1 < sq2) ? kNorthEast : kSouthWest;
                        ray_between[sq2][sq1] = -ray_between[sq1][sq2];
                    }
                    else if(AntiOf(sq1) == AntiOf(sq2))
                    {
                        ray_between[sq1][sq2] = (sq1 < sq2) ? kNorthWest : kSouthEast;
                        ray_between[sq2][sq1] = -ray_between[sq1][sq2];
                    }
                    else
                    {
                        ray_between[sq1][sq2] = kDirectionNone;
                        ray_between[sq1][sq2] = kDirectionNone;
                    }
                }
            }
        }

        void Init()
        {
            static bool initialized = false;
            if (!initialized)
            {
                InitRayBetween(kRayBetween);
            }
        }
    }
}
