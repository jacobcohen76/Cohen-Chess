#ifndef COHEN_CHESS_MAGICS_HPP_INCLUDED
#define COHEN_CHESS_MAGICS_HPP_INCLUDED

#include <assert.h>

#include <concepts>
#include <ranges>

#include <cohen/util/bits.hpp>
#include <cohen/util/functor.hpp>
#include <cohen/chess/type/bitboard.hpp>
#include <cohen/chess/type/key.hpp>
#include <cohen/chess/type/square.hpp>
#include <cohen/chess/attacks.hpp>

namespace cohen::chess::magics
{
    template <typename T>
    concept Magic = requires(T magic, Bitboard occ)
    {
        { magic.key(occ) } -> std::same_as<Key>;
    };

    constexpr Bitboard RuntimeMagicBishopMask(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        Bitboard mask = kEmptyBB;
        mask |=  DiagBB(DiagOf(sq));
        mask |=  AntiBB(AntiOf(sq));
        mask &= ~SquareBB(sq) & ~kEdgesBB;
        return mask;
    }

    inline constexpr std::array<Bitboard, kSquareNB> kMagicBishopMaskTable = []()
    {
        std::array<Bitboard, kSquareNB> mask_table = {};
        auto range = std::views::iota(Square{kA1}, Square{kSquareNB})
                   | std::views::transform(RuntimeMagicBishopMask);
        std::ranges::copy(range, std::data(mask_table));
        return mask_table;
    }();

    constexpr Bitboard LookupMagicBishopMask(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return kMagicBishopMaskTable[sq];
    }

    constexpr Bitboard MagicBishopMask(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return LookupMagicBishopMask(sq);
    }

    constexpr Bitboard RuntimeMagicRookMask(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        Bitboard mask = kEmptyBB;
        mask |=  RankBB(RankOf(sq)) & ~kRankEdgesBB;
        mask |=  FileBB(FileOf(sq)) & ~kFileEdgesBB;
        mask &= ~SquareBB(sq);
        return mask;
    }

    inline constexpr std::array<Bitboard, kSquareNB> kMagicRookMaskTable = []()
    {
        std::array<Bitboard, kSquareNB> mask_table = {};
        auto range = std::views::iota(Square{kA1}, Square{kSquareNB})
                   | std::views::transform(RuntimeMagicRookMask);
        std::ranges::copy(range, std::data(mask_table));
        return mask_table;
    }();

    constexpr Bitboard LookupMagicRookMask(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return kMagicRookMaskTable[sq];
    }

    constexpr Bitboard MagicRookMask(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return LookupMagicRookMask(sq);
    }

    constexpr Bitboard* FillPureMagicAttackTable(
        Bitboard*                                  attack_table,
        std::input_iterator                 auto   magic_itr,
        Functor<Bitboard(Square)>           auto&& mask_fn,
        Functor<Bitboard(Bitboard, Square)> auto&& attacks_fn) noexcept
    {
        Bitboard* max_itr = nullptr;
        for (Square sq = kA1; sq < kSquareNB; ++sq, ++magic_itr)
        {
            Bitboard mask = mask_fn(sq);
            Bitboard occ  = kEmptyBB;
            do
            {
                Key occ_key = magic_itr->key(occ);
                attack_table[occ_key] = attacks_fn(occ, sq);
                max_itr = std::max(max_itr, attack_table + occ_key);
            }
            while (occ = CarryRipple(occ, mask));
        }
        return max_itr + 1;
    }

    constexpr Bitboard* FillByteMagicAttackTable(
        Bitboard*                                  table_data,
        Functor<Bitboard(Square)>           auto&& mask_fn,
        Functor<Bitboard(Bitboard, Square)> auto&& attacks_fn) noexcept
    {
        Bitboard* lower = nullptr;
        Bitboard* upper = table_data;
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            Bitboard mask = mask_fn(sq);
            Bitboard occ  = kEmptyBB;
            lower = upper;
            do
            {
                Bitboard attacks = attacks_fn(occ, sq);
                if (std::find(lower, upper, attacks) == upper)
                {
                    *upper++ = attacks;
                }
            }
            while (occ = CarryRipple(occ, mask));
        }
        return upper;
    }


}

#endif