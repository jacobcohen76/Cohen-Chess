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
        Bitboard* upper = attack_table;
        for (Square sq = kA1; sq < kSquareNB; ++sq, ++magic_itr)
        {
            Bitboard mask = mask_fn(sq);
            Bitboard occ  = kEmptyBB;
            do
            {
                Key occ_key = magic_itr->key(occ);
                attack_table[occ_key] = attacks_fn(occ, sq);
                upper = std::max(upper, attack_table + occ_key);
            }
            while (occ = CarryRipple(occ, mask));
        }
        return upper + 1;
    }

    constexpr Bitboard* FillByteMagicAttackTable(
        Bitboard*                                  attack_table,
        Functor<Bitboard(Square)>           auto&& mask_fn,
        Functor<Bitboard(Bitboard, Square)> auto&& attacks_fn) noexcept
    {
        Bitboard* lower = nullptr;
        Bitboard* upper = attack_table;
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

    struct FancyMagic
    {
        Key      offset, magic;
        Bitboard mask;
        int      shift;

        constexpr Key key(Bitboard occ) const noexcept
        {
            return ((occ & mask) * magic >> shift) + offset;
        }
    };

    template <int shift>
    struct BlackMagic
    {
        Key      offset, magic;
        Bitboard not_mask;

        constexpr Key key(Bitboard occ) const noexcept
        {
            return ((occ | not_mask) * magic >> (kSquareNB - shift)) + offset;
        }
    };

    using BishopBlackMagic = BlackMagic<9>;

    inline constexpr std::array<Bitboard, kSquareNB> kBlackMagicBishopNumberTable =
    {
        0x107AC08050500BFF, 0x7FFFDFDFD823FFFD, 0x0400C00FE8000200, 0x103F802004000000, 0xC03FE00100000000, 0x24C00BFFFF400000, 0x0808101F40007F04, 0x100808201EC00080,
        0xFFA2FEFFBFEFB7FF, 0x083E3EE040080801, 0x040180BFF7E80080, 0x0440007FE0031000, 0x2010007FFC000000, 0x1079FFE000FF8000, 0x7F83FFDFC03FFF80, 0x080614080FA00040,
        0x7FFE7FFF817FCFF9, 0x7FFEBFFFA01027FD, 0x20018000C00F3C01, 0x407E0001000FFB8A, 0x201FE000FFF80010, 0xFFDFEFFFDE39FFEF, 0x7FFFF800203FBFFF, 0x7FF7FBFFF8203FFF,
        0x000000FE04004070, 0x7FFF7F9FFFC0EFF9, 0x7FFEFF7F7F01F7FD, 0x3F6EFBBF9EFBFFFF, 0x0410008F01003FFD, 0x20002038001C8010, 0x087FF038000FC001, 0x00080C0C00083007,
        0x00000080FC82C040, 0x000000407E416020, 0x00600203F8008020, 0xD003FEFE04404080, 0x100020801800304A, 0x7FBFFE700BFFE800, 0x107FF00FE4000F90, 0x7F8FFFCFF1D007F8,
        0x0000004100F88080, 0x00000020807C4040, 0x00000041018700C0, 0x0010000080FC4080, 0x1000003C80180030, 0x2006001CF00C0018, 0xFFFFFFBFEFF80FDC, 0x000000101003F812,
        0x0800001F40808200, 0x084000101F3FD208, 0x080000000F808081, 0x0004000008003F80, 0x08000001001FE040, 0x085F7D8000200A00, 0xFFFFFEFFBFEFF81D, 0xFFBFFFEFEFDFF70F,
        0x100000101EC10082, 0x7FBAFFFFEFE0C02F, 0x7F83FFFFFFF07F7F, 0xFFF1FFFFFFF7FFC1, 0x0878040000FFE01F, 0x005D00000120200A, 0x0840800080200FDA, 0x100000C05F582008,
    };

    inline constexpr std::array<Key, kSquareNB> kBlackMagicBishopOffsetTable =
    {
        66157, 71730, 37781, 21015, 47590,   835, 23592, 30599,
        68776, 19959, 21783, 64836, 23417, 66724, 74542, 67266,
        26575, 67543, 24409, 30779, 17384, 18778, 65109, 20184,
        38240, 16459, 17432, 81040, 84946, 18276,  8512, 78544,
        19974, 23850, 11056, 68019, 85965, 80524, 38221, 64647,
        61320, 67281, 79076, 17115, 50718, 24659, 38291, 30605,
        37759,  4639, 21759, 67799, 22841, 66689, 62548, 66597,
        86749, 69558, 61589, 62533, 64387, 26581, 76355, 11140,
    };

    inline constexpr auto kBlackMagicBishopTable = []()
    {
        std::array<BishopBlackMagic, kSquareNB> magic_table = {};
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            magic_table[sq] =
            {
                .offset   =  kBlackMagicBishopOffsetTable[sq],
                .magic    =  kBlackMagicBishopNumberTable[sq],
                .not_mask = ~MagicBishopMask(sq),
            };
        }
        return magic_table;
    }();

    using RookBlackMagic = BlackMagic<12>;

    inline constexpr std::array<Bitboard, kSquareNB> kBlackMagicRookNumberTable =
    {
        0x80280013FF84FFFF, 0x5FFBFEFDFEF67FFF, 0xFFEFFAFFEFFDFFFF, 0x003000900300008A, 0x0030018003500030, 0x0020012120A00020, 0x0030006000C00030, 0xFFA8008DFF09FFF8,
        0x7FBFF7FBFBEAFFFC, 0x0000140081050002, 0x0000180043800048, 0x7FFFE800021FFFB8, 0xFFFFCFFE7FCFFFAF, 0x00001800C0180060, 0xFFFFE7FF8FBFFFE8, 0x0000180030620018,
        0x00300018010C0003, 0x0003000C0085FFFF, 0xFFFDFFF7FBFEFFF7, 0x7FC1FFDFFC001FFF, 0xFFFEFFDFFDFFDFFF, 0x7C108007BEFFF81F, 0x20408007BFE00810, 0x0400800558604100,
        0x0040200010080008, 0x0010020008040004, 0xFFFDFEFFF7FBFFF7, 0xFEBF7DFFF8FEFFF9, 0xC00000FFE001FFE0, 0x2008208007004007, 0xBFFBFAFFFB683F7F, 0x0807F67FFA102040,
        0x200008E800300030, 0x0000008780180018, 0x0000010300180018, 0x4000008180180018, 0x008080310005FFFA, 0x4000188100060006, 0xFFFFFF7FFFBFBFFF, 0x0000802000200040,
        0x20000202EC002800, 0xFFFFF9FF7CFFF3FF, 0x000000404B801800, 0x2000002FE03FD000, 0xFFFFFF6FFE7FCFFD, 0xBFF7EFFFBFC00FFF, 0x000000100800A804, 0xFFFBFFEFA7FFA7FE,
        0x0000052800140028, 0x00000085008A0014, 0x8000002B00408028, 0x4000002040790028, 0x7800002010288028, 0x0000001800E08018, 0x1890000810580050, 0x2003D80000500028,
        0xFFFFF37EEFEFDFBE, 0x40000280090013C1, 0xBF7FFEFFBFFAF71F, 0xFFFDFFFF777B7D6E, 0xEEFFFFEFF0080BFE, 0xAFE0000FFF780402, 0xEE73FFFBFFBB77FE, 0x0002000308482882,
    };

    inline constexpr std::array<Key, kSquareNB> kBlackMagicRookOffsetTable =
    {
        10890, 56054, 67495, 72797, 17179, 63978, 56650, 15929,
        55905, 26301, 78100, 86245, 75228, 31661, 38053, 37433,
        74747, 53847, 70952, 49447, 62629, 58996, 36009, 21230,
        51882, 11841, 25794, 49689, 63400, 33958, 21991, 45618,
        70134, 75944, 68392, 66472, 23236, 19067,     0, 43566,
        29810, 65558, 77684, 73350, 61765, 49282, 78840, 82904,
        24594,  9513, 29012, 27684, 27901, 61477, 25719, 50020,
        41547,  4750,  6014, 41529, 84192, 33433,  8555,  1009,
    };

    inline constexpr auto kBlackMagicRookTable = []()
    {
        std::array<RookBlackMagic, kSquareNB> magic_table = {};
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            magic_table[sq] =
            {
                .offset   =  kBlackMagicRookOffsetTable[sq],
                .magic    =  kBlackMagicRookNumberTable[sq],
                .not_mask = ~MagicRookMask(sq),
            };
        }
        return magic_table;
    }();

}

#endif