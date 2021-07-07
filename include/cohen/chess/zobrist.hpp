#ifndef COHEN_CHESS_ZOBRIST_HPP_INCLUDED
#define COHEN_CHESS_ZOBRIST_HPP_INCLUDED

#include <algorithm>
#include <array>

#include <cohen/chess/type/castling.hpp>
#include <cohen/chess/type/key.hpp>
#include <cohen/chess/type/piece.hpp>
#include <cohen/chess/type/square.hpp>

#include <cohen/util/bits.hpp>
#include <cohen/util/functor.hpp>
#include <cohen/util/random.hpp>

namespace cohen::chess::zobrist
{
    constexpr auto kZobristPieceSquareKeyTable = [](Functor<Key()> auto rand_fn)
    {
        std::array<std::array<Key, kSquareNB>, kPieceNB> pc_sq_table = {};
        for (Color color = kWhite; color < kColorNB; ++color)
        {
            for (Piece piece = kPawn; piece <= kKing; ++piece)
            {
                auto& sq_table = pc_sq_table[MakePiece(color, piece)];
                std::generate(sq_table.begin(), sq_table.end(), rand_fn);
            }
        }
        return pc_sq_table;
    }(LinearCongruentialGenerator(0xF5586876FC706684));

    constexpr Key ZobristPieceSquareKey(Piece pc, Square sq) noexcept
    {
        assert(kPieceNone <= pc && pc < kPieceNB);
        assert(kA1 <= sq && sq < kSquareNB);
        return kZobristPieceSquareKeyTable[pc][sq];
    }

    constexpr auto kZobristCastlingKeyTable = [](Functor<Key()> auto rand_fn)
    {
        std::array<Key, kCastlingNB> castling_table = {};
        castling_table[kWhiteOO]  = rand_fn();
        castling_table[kWhiteOOO] = rand_fn();
        castling_table[kBlackOO]  = rand_fn();
        castling_table[kBlackOOO] = rand_fn();
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
    }(LinearCongruentialGenerator(0xF5586876FC706684));

    constexpr Key ZobristCastlingKey(Castling castling) noexcept
    {
        assert(kCastlingNone <= castling && castling < kCastlingNB);
        return kZobristCastlingKeyTable[castling];
    }

    constexpr auto kZobristEnPassantFileKeyTable = [](Functor<Key()> auto rand_fn)
    {
        std::array<Key, kFileNB + 1> ep_file_table = {};
        std::generate(ep_file_table.begin(), ep_file_table.end() - 1, rand_fn);
        return ep_file_table;
    }(LinearCongruentialGenerator(0x9F0471D8CD082F7B));

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

namespace cohen::chess
{
    using cohen::chess::zobrist::ZobristPieceSquareKey;
    using cohen::chess::zobrist::ZobristCastlingKey;
    using cohen::chess::zobrist::ZobristEnPassantKey;
    using cohen::chess::zobrist::ZobristSideKey;
}

#endif
