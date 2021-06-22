#ifndef COHEN_CHESS_ENGINE_MAGIC_HPP_INCLUDED
#define COHEN_CHESS_ENGINE_MAGIC_HPP_INCLUDED

#include <algorithm>
#include <cassert>

#include <engine/attacks.hpp>
#include <type/bitboard.hpp>
#include <type/key.hpp>
#include <type/square.hpp>
#include <util/bits.hpp>

namespace cohen_chess::engine::magic
{
    template <typename T>
    concept Magic = requires(T magic, Bitboard occ)
    {
        magic.index(occ);
    };

    constexpr Key MagicMaxIndex(Magic auto m, Bitboard mask) noexcept
    {
        Key max_index = kKeyNone;
        Bitboard  occ = kEmptyBB;
        do
        {
            max_index = std::max(max_index, m.index(occ));
        }
        while ((occ = (occ - mask) & mask));
        return max_index;
    }

    template <Magic M>
    constexpr Key MagicTableSize(const std::array<M, kSquareNB>& table)
    {

    }

    constexpr Bitboard MagicBishopMask(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        Bitboard mask = kEmptyBB;
        mask |=  DiagBB(DiagOf(sq));
        mask |=  AntiBB(AntiOf(sq));
        mask &= ~SquareBB(sq) & ~kEdgesBB;
        return mask;
    }

    constexpr Bitboard MagicRookMask(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        Bitboard mask = kEmptyBB;
        mask |=  RankBB(RankOf(sq)) & ~kRankEdgesBB;
        mask |=  FileBB(FileOf(sq)) & ~kFileEdgesBB;
        mask &= ~SquareBB(sq);
        return mask;
    }

    struct FancyMagic
    {
        Key      begin;
        Bitboard magic, mask;
        int      shift;

        constexpr Key index(Bitboard occ) const noexcept
        {
            return ((occ & mask) * magic >> shift) + begin;
        }
    };

    template <int shift>
    struct FixedMagic
    {
        Key      begin;
        Bitboard magic, mask;

        constexpr Key index(Bitboard occ) const noexcept
        {
            return ((occ & mask) * magic >> 64 - shift) + begin;
        }
    };

    template <int shift>
    struct BlackMagic
    {
        Key      begin;
        Bitboard magic, not_mask;

        constexpr Key index(Bitboard occ) const noexcept
        {
            return ((occ | not_mask) * magic >> 64 - shift) + begin;
        }
    };


}

namespace cohen_chess
{

}

#endif