#ifndef COHEN_CHESS_HASH_ZOBRIST_H_INCLUDED
#define COHEN_CHESS_HASH_ZOBRIST_H_INCLUDED

#include "../types/castling_rights.h"
#include "../types/file.h"
#include "../types/key.h"
#include "../types/piece.h"
#include "../types/square.h"
#include "../util/bit_util.h"
#include "../util/random.h"

#include <array>
#include <cstdint>

namespace cohen_chess
{
    static constexpr auto kZobristRandomizer = LinearCongruentialGenerator();

    constexpr Key ZobristKey(Piece pc, Square sq)
    {
        constexpr std::array<std::array<Key, kSquareNB>, kPieceNB> kPieceSquareKeys = [](auto randomizer)
        {
            std::array<std::array<Key, kSquareNB>, kPieceNB> piece_square_keys = {};
            for (Piece pc = kWhitePawn; pc <= kWhiteKing; ++pc)
            {
                for (Square sq = kA1; sq < kSquareNB; ++sq)
                {
                    piece_square_keys[pc][sq] = randomizer();
                }
            }
            for (Piece pc = kBlackPawn; pc <= kBlackKing; ++pc)
            {
                for (Square sq = kA1; sq < kSquareNB; ++sq)
                {
                    piece_square_keys[pc][sq] = randomizer();
                }
            }
            return piece_square_keys;
        }(kZobristRandomizer);
        return kPieceSquareKeys[pc][sq];
    }

    constexpr Key ZobristKey(CastlingRights cr)
    {
        constexpr std::array<Key, kCastlingNB> kCastlingKeys = [](auto randomizer)
        {
            std::array<Key, kCastlingNB> castling_keys = {};
            castling_keys[kWhiteOO]  = randomizer();
            castling_keys[kWhiteOOO] = randomizer();
            castling_keys[kBlackOO]  = randomizer();
            castling_keys[kBlackOOO] = randomizer();
            for (CastlingRights cr = kCastlingNone; cr < kCastlingNB; ++cr)
            {
                if (FlipLSB(cr))
                {
                    if (cr & kWhiteOO)
                        castling_keys[cr] ^= castling_keys[kWhiteOO];
                    if (cr & kWhiteOOO)
                        castling_keys[cr] ^= castling_keys[kWhiteOOO];
                    if (cr & kBlackOO)
                        castling_keys[cr] ^= castling_keys[kBlackOO];
                    if (cr & kBlackOOO)
                        castling_keys[cr] ^= castling_keys[kBlackOOO];
                }
            }
            return castling_keys;
        }(kZobristRandomizer);
        return kCastlingKeys[cr];
    }

    constexpr Key ZobristKey(File file)
    {
        constexpr std::array<Key, kFileNB> kEnPassantFileKeys = [](auto randomizer)
        {
            std::array<Key, kFileNB> en_passant_file_keys = {};
            for (File file = kFileA; file < kFileNB; ++file)
            {
                en_passant_file_keys[file] = randomizer();
            }
            return en_passant_file_keys;
        }(kZobristRandomizer);
        return kEnPassantFileKeys[file];
    }

    // constexpr Key ZobristKey(Color color)
    // {
    //     constexpr Key kBlackKey = [](auto randomizer)
    //     {
    //         return randomizer();
    //     }(kZobristRandomizer);
    //     return color * kBlackKey;
    // }
}

#endif