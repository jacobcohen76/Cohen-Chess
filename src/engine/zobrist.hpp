#ifndef COHEN_CHESS_HASH_ZOBRIST_HPP_INCLUDED
#define COHEN_CHESS_HASH_ZOBRIST_HPP_INCLUDED

#include <algorithm>
#include <array>

#include <type/castling.hpp>
#include <type/key.hpp>
#include <type/piece.hpp>
#include <type/square.hpp>
#include <util/bits.hpp>
#include <util/random.hpp>

namespace cohen_chess::engine::zobrist
{
    constexpr auto kZobristPieceSquareKeyRandomizer = LinearCongruentialGenerator(0xF5586876FC706684);
    constexpr std::array<std::array<Key, kSquareNB>, kPieceNB>
    kZobristPieceSquareKeyTable = [](auto randomizer)
    {
        std::array<std::array<Key, kSquareNB>, kPieceNB> pc_sq_table = {};
        for (Color color = kWhite; color < kColorNB; ++color)
        {
            for (Piece piece = kPawn; piece <= kKing; ++piece)
            {
                auto& sq_table = pc_sq_table[MakePiece(color, piece)];
                std::generate(sq_table.begin(), sq_table.end(), randomizer);
            }
        }
        return pc_sq_table;
    }(kZobristPieceSquareKeyRandomizer);

    constexpr Key ZobristPieceSquareKey(Piece pc, Square sq) noexcept
    {
        assert(kPieceNone <= pc && pc < kPieceNB);
        assert(kA1 <= sq && sq < kSquareNB);
        return kZobristPieceSquareKeyTable[pc][sq];
    }

    constexpr auto kZobristCastlingKeyRandomizer = LinearCongruentialGenerator(0xF5586876FC706684);
    constexpr std::array<Key, kCastlingNB>
    kZobristCastlingKeyTable = [](auto randomizer)
    {
        std::array<Key, kCastlingNB> castling_table = {};
        castling_table[kWhiteOO]  = randomizer();
        castling_table[kWhiteOOO] = randomizer();
        castling_table[kBlackOO]  = randomizer();
        castling_table[kBlackOOO] = randomizer();
        for (Castling cr = kCastlingNone; cr < kCastlingNB; ++cr)
        {
            if (FlipLSB(cr))
            {
                if (kWhiteOO & cr)
                    castling_table[cr] ^= castling_table[kWhiteOO];
                if (kWhiteOOO & cr)
                    castling_table[cr] ^= castling_table[kWhiteOOO];
                if (kBlackOO & cr)
                    castling_table[cr] ^= castling_table[kBlackOO];
                if (kBlackOOO & cr)
                    castling_table[cr] ^= castling_table[kBlackOOO];
            }
        }
        return castling_table;
    }(kZobristCastlingKeyRandomizer);

    constexpr Key ZobristCastlingKey(Castling castling) noexcept
    {
        assert(kCastlingNone <= castling && castling < kCastlingNB);
        return kZobristCastlingKeyTable[castling];
    }

    constexpr auto kZobristEnPassantFileKeyRandomizer = LinearCongruentialGenerator(0x9F0471D8CD082F7B);
    constexpr std::array<Key, kFileNB + 1>
    kZobristEnPassantFileKeyTable = [](auto randomizer)
    {
        std::array<Key, kFileNB + 1> ep_file_table = {};
        std::generate(ep_file_table.begin(), ep_file_table.end(), randomizer);
        ep_file_table[kFileNB] = kKeyNone;
        return ep_file_table;
    }(kZobristEnPassantFileKeyRandomizer);

    constexpr Key ZobristEnPassantKey(File file) noexcept
    {
        assert(kFileA <= file && file < kFileNB + 1);
        return kZobristEnPassantFileKeyTable[file];
    }

    constexpr Key kZobristSideKey = 0x9634520BD3C345BA;

    constexpr Key ZobristSideKey(Color side) noexcept
    {
        return kZobristSideKey;
    }
}

namespace cohen_chess
{
    using engine::zobrist::ZobristPieceSquareKey;
    using engine::zobrist::ZobristCastlingKey;
    using engine::zobrist::ZobristEnPassantKey;
    using engine::zobrist::ZobristSideKey;
}

#endif