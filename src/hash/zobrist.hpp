#ifndef COHEN_CHESS_HASH_ZOBRIST_HPP_INCLUDED
#define COHEN_CHESS_HASH_ZOBRIST_HPP_INCLUDED

#include <types/castling_rights.hpp>
#include <types/file.hpp>
#include <types/key.hpp>
#include <types/piece.hpp>
#include <types/square.hpp>
#include <util/bits.hpp>
#include <util/random.hpp>

#include <array>
#include <cstdint>

namespace cohen_chess
{
    constexpr std::array<std::array<Key, kSquareNB>, kPieceNB> kZobristPieceSquareKeys = [](auto randomizer)
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
    }(LinearCongruentialGenerator(0xF5586876FC706684));

    constexpr Key ZobristPieceSquareKey(Piece pc, Square sq)
    {
        return kZobristPieceSquareKeys[pc][sq];
    }

    constexpr std::array<Key, kCastlingNB> kZobristCastlingKeys = [](auto randomizer)
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
    }(LinearCongruentialGenerator(0xA7D1552684A6FC08));

    constexpr Key ZobristCastlingKey(CastlingRights cr)
    {
        return kZobristCastlingKeys[cr];
    }

    constexpr std::array<Key, kFileNB + 1> kZobristEnPassantFileKeys = [](auto randomizer)
    {
        std::array<Key, kFileNB + 1> en_passant_file_keys = {};
        for (File file = kFileA; file < kFileNB; ++file)
        {
            en_passant_file_keys[file] = randomizer();
        }
        return en_passant_file_keys;
    }(LinearCongruentialGenerator(0x9F0471D8CD082F7B));

    constexpr Key ZobristEnPassantKey(File file)
    {
        return kZobristEnPassantFileKeys[file];
    }

    constexpr Key kZobristSideKey = 0x9634520BD3C345BA;
}

#endif