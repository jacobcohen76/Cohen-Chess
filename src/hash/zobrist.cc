#include "zobrist.h"

#include <cstdint>

namespace cohen_chess
{
    namespace zobrist
    {
        Key   kPieceOnSquareKeys[kPieceNB][kSquareNB] = {};
        Key  kCastlingRightsKeys[kCastlingNB];
        Key kEnPassantFileTarget[kFileNB];

        void InitPieceOnSquareKeys(uint64_t (*randomizer)())
        {
            for(Piece pc = kWhitePawn; pc <= kWhiteKing; ++pc)
            {
                for(Square sq = kA1; sq < kSquareNB; ++sq)
                {
                    kPieceOnSquareKeys[pc][sq] = Key(randomizer());
                }
            }
            for(Piece pc = kBlackPawn; pc <= kBlackKing; ++pc)
            {
                for(Square sq = kA1; sq < kSquareNB; ++sq)
                {
                    kPieceOnSquareKeys[pc][sq] = Key(randomizer());
                }
            }
        }

        void InitCastlingRightsKeys(uint64_t (*randomizer)())
        {
            kCastlingRightsKeys[kWhiteOO]   = Key(randomizer());
            kCastlingRightsKeys[kWhiteOOO]  = Key(randomizer());
            kCastlingRightsKeys[kBlackOO]   = Key(randomizer());
            kCastlingRightsKeys[kBlackOOO]  = Key(randomizer());
            for(CastlingRights cr = kCastlingNone; cr < kCastlingNB; ++cr)
            {
                if(cr != kWhiteOO && cr != kWhiteOOO && cr != kBlackOO && cr != kBlackOOO)
                {
                    kCastlingRightsKeys[cr] = kKeyZero;
                    if(cr & kWhiteOO)
                    {
                        kCastlingRightsKeys[cr] ^= kCastlingRightsKeys[kWhiteOO];
                    }
                    if(cr & kWhiteOOO)
                    {
                        kCastlingRightsKeys[cr] ^= kCastlingRightsKeys[kWhiteOOO];
                    }
                    if(cr & kBlackOO)
                    {
                        kCastlingRightsKeys[cr] ^= kCastlingRightsKeys[kBlackOO];
                    }
                    if(cr & kBlackOOO)
                    {
                        kCastlingRightsKeys[cr] ^= kCastlingRightsKeys[kBlackOOO];
                    }
                }
            }
        }

        void InitEnPassantFileTargetKeys(uint64_t (*randomizer)())
        {
            for(File f = kFileA; f < kFileNB; ++f)
            {
                kEnPassantFileTarget[f] = Key(randomizer());
            }
        }
    };
};