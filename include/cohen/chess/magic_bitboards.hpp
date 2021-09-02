#ifndef COHEN_CHESS_MAGIC_BITBOARDS_HPP_INCLUDED
#define COHEN_CHESS_MAGIC_BITBOARDS_HPP_INCLUDED

#include <concepts>

#include <cohen/chess/type/bitboard.hpp>
#include <cohen/chess/type/key.hpp>
#include <cohen/chess/attacks.hpp>
#include <cohen/util/bits.hpp>
#include <cohen/util/functor.hpp>

namespace cohen::chess::magic_bitboards
{
    template <typename T>
    concept Magic = requires(const T magic, Bitboard occ)
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
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            mask_table[sq] = RuntimeMagicBishopMask(sq);
        }
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
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            mask_table[sq] = RuntimeMagicRookMask(sq);
        }
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

    template <Magic MagicType>
    constexpr void FillMagicTable(
        Bitboard*                                   table,
        Functor<MagicType(Square)>           auto&& magic_fn,
        Functor< Bitboard(Square)>           auto&& mask_fn,
        Functor< Bitboard(Square, Bitboard)> auto&& gen_fn) noexcept
    {
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            MagicType magic = magic_fn(sq);
            Bitboard  mask  = mask_fn(sq);
            Bitboard  occ   = kEmptyBB;
            do
            {
                Key key     = magic.key(occ);
                table[key]  = gen_fn(sq, occ);
            }
            while ((occ = CarryRipple(occ, mask)));
        }
    }

    template <Magic BishopType, Magic RookType>
    constexpr void FillMagicTable(
        Bitboard*                          table,
        Functor<BishopType(Square)> auto&& bishop_fn,
        Functor<  RookType(Square)> auto&& rook_fn) noexcept
    {
        FillMagicTable(table, bishop_fn, MagicBishopMask, RayBishopAttacks);
        FillMagicTable(table, rook_fn,   MagicRookMask,   RayRookAttacks);
    }

    struct FancyMagic
    {
        Key      magic, offset;
        Bitboard mask;
        int      shift;

        constexpr Key key(Bitboard occ) const noexcept
        {
            return (magic * (occ & mask) >> shift) + offset;
        }
    };

    template <int shift>
    struct BlackMagic
    {
        Key      magic, offset;
        Bitboard not_mask;

        constexpr Key key(Bitboard occ) const noexcept
        {
            return (magic * (occ | not_mask) >> (kSquareNB - shift)) + offset;
        }
    };

    using BlackBishopMagic = BlackMagic< 9>;
    using BlackRookMagic   = BlackMagic<12>;

    template <Magic T>
    struct ByteMagic
    {
        T   magic;
        Key offset;

        template <const uint8_t* byte_table = nullptr>
        constexpr Key key(Bitboard occ) const noexcept
        {
            return byte_table[magic.key(occ)] + offset;
        }
    };

    using ByteFancyMagic       = ByteMagic<FancyMagic>;
    using ByteBlackBishopMagic = ByteMagic<BlackBishopMagic>;
    using ByteBlackRookMagic   = ByteMagic<BlackRookMagic>;



}

#endif