#include "zobrist.h"

#include <cstdint>

namespace cohen_chess
{
    namespace zobrist
    {
        Key kPieceOnSquareKeys[kPieceNB][kSquareNB];
        Key kCastlingRightsKeys[kCastlingNB];
        Key kEnPassantFileTargetKeys[kFileNB];

        void InitPieceOnSquareKeys(Key piece_on_square_keys[kPieceNB][kSquareNB], Randomizer randomizer)
        {
            for(Piece pc = kPieceNone; pc < kPieceNB; ++pc)
            {
                PieceType pc_type = PieceTypeOf(pc);
            }
            for(Piece pc = kWhitePawn; pc <= kWhiteKing; ++pc)
            {
                for(Square sq = kA1; sq < kSquareNB; ++sq)
                {
                    piece_on_square_keys[pc][sq] = Key(randomizer());
                }
            }
            for(Piece pc = kBlackPawn; pc <= kBlackKing; ++pc)
            {
                for(Square sq = kA1; sq < kSquareNB; ++sq)
                {
                    piece_on_square_keys[pc][sq] = Key(randomizer());
                }
            }
        }

        void InitCastlingRightsKeys(Key castling_rights_keys[kCastlingNB], Randomizer randomizer)
        {
            castling_rights_keys[kWhiteOO]  = Key(randomizer());
            castling_rights_keys[kWhiteOOO] = Key(randomizer());
            castling_rights_keys[kBlackOO]  = Key(randomizer());
            castling_rights_keys[kBlackOOO] = Key(randomizer());
            for(CastlingRights cr = kCastlingNone; cr < kCastlingNB; ++cr)
            {
                if(cr != kWhiteOO && cr != kWhiteOOO && cr != kBlackOO && cr != kBlackOOO)
                {
                    castling_rights_keys[cr] = kKeyZero;
                    if(cr & kWhiteOO)
                    {
                        castling_rights_keys[cr] ^= castling_rights_keys[kWhiteOO];
                    }
                    if(cr & kWhiteOOO)
                    {
                        castling_rights_keys[cr] ^= castling_rights_keys[kWhiteOOO];
                    }
                    if(cr & kBlackOO)
                    {
                        castling_rights_keys[cr] ^= castling_rights_keys[kBlackOO];
                    }
                    if(cr & kBlackOOO)
                    {
                        castling_rights_keys[cr] ^= castling_rights_keys[kBlackOOO];
                    }
                }
            }
        }

        void InitEnPassantFileTargetKeys(Key en_passant_file_target_keys[kFileNB], Randomizer randomizer)
        {
            for(File f = kFileA; f < kFileNB; ++f)
            {
                en_passant_file_target_keys[f] = Key(randomizer());
            }
        }

        void Init(Randomizer randomizer)
        {
            static bool initialized = false;
            if (!initialized)
            {
                InitPieceOnSquareKeys(kPieceOnSquareKeys, randomizer);
                InitCastlingRightsKeys(kCastlingRightsKeys, randomizer);
                InitEnPassantFileTargetKeys(kEnPassantFileTargetKeys, randomizer);
                initialized = true;
            }
        }
    }
}