#ifndef COHEN_CHESS_MAGICS_HPP_INCLUDED
#define COHEN_CHESS_MAGICS_HPP_INCLUDED

#include <algorithm>
#include <array>
#include <cassert>
#include <ranges>
#include <span>

#include <cohen/chess/type/bitboard.hpp>
#include <cohen/chess/type/key.hpp>
#include <cohen/chess/type/square.hpp>
#include <cohen/chess/attacks.hpp>

#include <cohen/util/bits.hpp>
#include <cohen/util/functor.hpp>

namespace cohen::chess::magics
{
    template <typename T>
    concept Magic = requires(T magic, Bitboard occ)
    {
        { magic.key(occ) } -> std::same_as<Key>;
    };

    template <Magic T, size_t table_size>
    constexpr void FillMagicAttackTable(
        std::array<Bitboard, table_size>&          attacks_table,
        const std::array<T, kSquareNB>&            magic_table,
        Functor<Bitboard(Square)> auto&&           mask_fn,
        Functor<Bitboard(Bitboard, Square)> auto&& attacks_fn) noexcept
    {
        for (Square sq = kA1; const T& magic : magic_table)
        {
            Bitboard mask = mask_fn(sq);
            Bitboard  occ = kEmptyBB;
            do
            {
                attacks_table[magic.key(occ)] = attacks_fn(occ, sq);
            }
            while ((occ = (occ - mask) & mask)); ++sq;
        }
    }

    constexpr Key MagicMinKey(const Magic auto& magic, Bitboard mask) noexcept
    {
        Key  min_key = kKeyAll;
        Bitboard occ = kEmptyBB;
        do
        {
            min_key = std::min(min_key, magic.key(occ));
        }
        while ((occ = (occ - mask) & mask));
        return min_key;
    }

    template <Magic T>
    constexpr Key MagicMinKey(const std::array<T, kSquareNB>&       magic_table,
                              const Functor<Bitboard(Square)> auto& mask_fn) noexcept
    {
        Key min_key = kKeyNone;
        for (Square sq = kA1; const T& magic : magic_table)
        {
            min_key = std::min(min_key, MagicMinKey(magic, mask_fn(sq++)));
        }
        return min_key;
    }

    constexpr Key MagicMaxKey(const Magic auto& magic, Bitboard mask) noexcept
    {
        Key  max_key = kKeyNone;
        Bitboard occ = kEmptyBB;
        do
        {
            max_key = std::max(max_key, magic.key(occ));
        }
        while ((occ = (occ - mask) & mask));
        return max_key;
    }

    template <Magic T>
    constexpr Key MagicMaxKey(const std::array<T, kSquareNB>&       magic_table,
                              const Functor<Bitboard(Square)> auto& mask_fn) noexcept
    {
        Key max_key = kKeyNone;
        for (Square sq = kA1; const T& magic : magic_table)
        {
            max_key = std::max(max_key, MagicMaxKey(magic, mask_fn(sq++)));
        }
        return max_key;
    }

    constexpr std::pair<Key, Key> MagicKeyRange(const Magic auto& magic, Bitboard mask) noexcept
    {
        Key  min_key = kKeyAll, max_key = kKeyNone;
        Bitboard occ = kEmptyBB;
        do
        {
            Key key = magic.key(occ);
            min_key = std::min(min_key, key);
            max_key = std::max(max_key, key);
        }
        while ((occ = (occ - mask) & mask));
        return {min_key, max_key};
    }

    template <Magic T>
    constexpr std::pair<Key, Key> MagicKeyRange(const std::array<T, kSquareNB>&       magic_table,
                                                const Functor<Bitboard(Square)> auto& mask_fn) noexcept
    {
        Key min_key = kKeyAll, max_key = kKeyNone;
        for (Square sq = kA1; const T& magic : magic_table)
        {
            auto [sq_min_key, sq_max_key] = MagicKeyRange(magic, mask_fn(sq++));
            min_key = std::min(min_key, sq_min_key);
            max_key = std::max(max_key, sq_max_key);
        }
        return {min_key, max_key};
    }

    constexpr Key MagicWidth(const Magic auto& magic, Bitboard mask) noexcept
    {
        auto [min_key, max_key] = MagicKeyRange(magic, mask);
        return max_key - min_key + 1;
    }

    template <Magic T>
    constexpr Key MagicWidth(const std::array<T, kSquareNB>&       magic_table,
                             const Functor<Bitboard(Square)> auto& mask_fn) noexcept
    {
        auto [min_key, max_key] = MagicKeyRange(magic_table, mask_fn);
        return max_key - min_key + 1;
    }

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

    struct FancyMagic
    {
        Key      offset;
        Bitboard magic, mask;
        int      shift;

        constexpr Key key(Bitboard occ) const noexcept
        {
            return ((occ & mask) * magic >> shift) + offset;
        }
    };

    inline constexpr std::array<Bitboard, kSquareNB> kFancyMagicBishopNumberTable =
    {
        0xFFEDF9FD7CFCFFFF, 0xFC0962854A77F576, 0x405000A251180664, 0x2AE2AA09600046CA, 0x05920A10B4425210, 0x4002091018015824, 0xFC0A66C64A7EF576, 0x7FFDFDFCBD79FFFF,
        0xFC0846A64A34FFF6, 0xFC087A874A3CF7F6, 0x402D444C41820061, 0x40408820882C0020, 0x0133520A1091A120, 0x6E13011002302011, 0xFC0864AE59B4FF76, 0x3C0860AF4B35FF76,
        0x73C01AF56CF4CFFB, 0x41A01CFAD64AAFFC, 0x2018206402440228, 0x9408041404321240, 0x2352002402314002, 0x1044400601102720, 0x7C0C028F5B34FF76, 0xFC0A028E5AB4DF76,
        0x161C400530108980, 0xA510104014249085, 0x82148804D00FC030, 0x0022008008008013, 0x401E8C0049802005, 0x131C090114900280, 0xC488A10004014812, 0x1000610100440203,
        0x0110020844204852, 0x6AE8882804201208, 0x086440E800300050, 0x0304440101300900, 0x4170840A400C0100, 0x06010206002C0900, 0x00082205888C028D, 0x0284C900401F040E,
        0xDCEFD9B54BFCC09F, 0xF95FFA765AFD602B, 0x020201004800E103, 0x20601C2013000805, 0x204040210A000100, 0x3B50051007200100, 0x43FF9A5CF4CA0C01, 0x4BFFCD8E7C587601,
        0xFC0FF2865334F576, 0xFC0BF6CE5924F576, 0x0008B11240D0A807, 0x150412A084040204, 0x339004517A0A0200, 0x4100601505720029, 0xC3FFB7DC36CA8C89, 0xC3FF8A54F4CA2C89,
        0xFFFFFCFCFD79EDFF, 0xFC0863FCCB147576, 0x0211110132389020, 0x4294700222104405, 0x4460904820842420, 0x3280312554101160, 0xFC087E8E4BB2F736, 0x43FF9E4EF4CA2C89,
    };

    inline constexpr std::array<int, kSquareNB> kFancyMagicBishopShiftTable =
    {
        5, 4, 5, 5, 5, 5, 4, 5,
        4, 4, 5, 5, 5, 5, 4, 4,
        4, 4, 7, 7, 7, 7, 4, 4,
        5, 5, 7, 9, 9, 7, 5, 5,
        5, 5, 7, 9, 9, 7, 5, 5,
        4, 4, 7, 7, 7, 7, 4, 4,
        4, 4, 5, 5, 5, 5, 4, 4,
        5, 4, 5, 5, 5, 5, 4, 5,
    };

    inline constexpr auto kFancyMagicBishopTable = [](Key curr_pos)
    {
        std::array<FancyMagic, kSquareNB> magic_table = {};
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            magic_table[sq] =
            {
                .offset = curr_pos,
                .magic  = kFancyMagicBishopNumberTable[sq],
                .mask   = MagicBishopMask(sq),
                .shift  = kSquareNB - kFancyMagicBishopShiftTable[sq],
            };
            curr_pos += MagicWidth(magic_table[sq], MagicBishopMask(sq));
        }
        return magic_table;
    }(kKeyZero);

    inline constexpr std::array<Bitboard, kSquareNB> kFancyMagicRookNumberTable =
    {
        0x0080042390400280, 0x50C0086002300042, 0x8880082001801000, 0x0080080010002480, 0x0200205402004870, 0x88800C0002008021, 0x740008030C841026, 0xC2000100640884C6,
        0xF982800981A04001, 0x642380400083A00C, 0x10070050C101A000, 0x2005002850042100, 0x1682000600202A0E, 0x0181004A08140100, 0x0402002200880124, 0xA004802041000180,
        0x0450818000C00032, 0x2EE1010063824000, 0x22A0030010410362, 0x3004A10050010008, 0x20D8808028002401, 0x008E2801100C6040, 0x0B09B40005060890, 0x01B1360010418C01,
        0x2123400580009061, 0x60008301004002A4, 0x0205024100200791, 0x000A0042001188A0, 0x5686040080080080, 0x20063400800A0080, 0xACF1184400091002, 0x7F4098820001095C,
        0x009480C0008002F0, 0xA30840018B002500, 0x4E05C20012002580, 0xC280820800801000, 0x0427005205000800, 0x0002000402003008, 0x4422B11A14001008, 0x6022C0410E002584,
        0x1182C00022808008, 0x0404400708810024, 0x8020018010008020, 0x6100100102490020, 0x4546004805220010, 0x0A40601040080124, 0x12051045420C0018, 0x4180B1440A820003,
        0x48FFFE99FECFAA00, 0x48FFFE99FECFAA00, 0x497FFFADFF9C2E00, 0x613FFFDDFFCE9200, 0xFFFFFFE9FFE7CE00, 0xFFFFFFF5FFF3E600, 0x0003FF95E5E6A4C0, 0x510FFFF5F63C96A0,
        0xEBFFFFB9FF9FC526, 0x61FFFEDDFEEDAEAE, 0x53BFFFEDFFDEB1A2, 0x127FFFB9FFDFB5F6, 0x411FFFDDFFDBF4D6, 0x022A000108100426, 0x0003FFEF27EEBE74, 0x7645FFFECBFEA79E,
    };

    inline constexpr std::array<int, kSquareNB> kFancyMagicRookShiftTable =
    {
        12, 11, 11, 11, 11, 11, 11, 12,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        10,  9,  9,  9,  9,  9,  9, 10,
        11, 10, 10, 10, 10, 11, 10, 11,
    };

    inline constexpr auto kFancyMagicRookTable = [](Key curr_pos)
    {
        std::array<FancyMagic, kSquareNB> magic_table = {};
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            magic_table[sq] =
            {
                .offset = curr_pos,
                .magic  = kFancyMagicRookNumberTable[sq],
                .mask   = MagicRookMask(sq),
                .shift  = kSquareNB - kFancyMagicRookShiftTable[sq],
            };
            curr_pos += MagicWidth(magic_table[sq], MagicRookMask(sq));
        }
        return magic_table;
    }(MagicWidth(kFancyMagicBishopTable, MagicBishopMask));

    inline constexpr auto kFancyMagicAttackTable = []()
    {
        constexpr Key kBishopMaxKey = MagicMaxKey(kFancyMagicBishopTable, MagicBishopMask);
        constexpr Key kRookMaxKey   = MagicMaxKey(kFancyMagicRookTable,   MagicRookMask);
        std::array<Bitboard, std::max(kBishopMaxKey, kRookMaxKey) + 1> attack_table = {};
        FillMagicAttackTable(attack_table, kFancyMagicBishopTable, MagicBishopMask, RayBishopAttacks);
        FillMagicAttackTable(attack_table, kFancyMagicRookTable,   MagicRookMask,   RayRookAttacks);
        return attack_table;
    }();

    constexpr Bitboard FancyMagicBishopAttacks(Bitboard occ, Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return kFancyMagicAttackTable[kFancyMagicBishopTable[sq].key(occ)];
    }

    constexpr Bitboard FancyMagicRookAttacks(Bitboard occ, Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return kFancyMagicAttackTable[kFancyMagicRookTable[sq].key(occ)];
    }

    constexpr Bitboard FancyMagicQueenAttacks(Bitboard occ, Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return FancyMagicBishopAttacks(occ, sq) | FancyMagicRookAttacks(occ, sq);
    }

    template <int shift>
    struct BlackMagic
    {
        Key      offset;
        Bitboard magic, not_mask;

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

    inline constexpr std::array<BishopBlackMagic, kSquareNB> kBlackMagicBishopTable = []()
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

    inline constexpr std::array<RookBlackMagic, kSquareNB> kBlackMagicRookTable = []()
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

    inline constexpr auto kBlackMagicAttackTable = []()
    {
        constexpr Key kBishopMaxKey = MagicMaxKey(kBlackMagicBishopTable, MagicBishopMask);
        constexpr Key kRookMaxKey   = MagicMaxKey(kBlackMagicRookTable,   MagicRookMask);
        std::array<Bitboard, std::max(kBishopMaxKey, kRookMaxKey) + 1> attack_table = {};
        FillMagicAttackTable(attack_table, kBlackMagicBishopTable, MagicBishopMask, RayBishopAttacks);
        FillMagicAttackTable(attack_table, kBlackMagicRookTable,   MagicRookMask,   RayRookAttacks);
        return attack_table;
    }();

    constexpr Bitboard BlackMagicBishopAttacks(Bitboard occ, Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return kBlackMagicAttackTable[kBlackMagicBishopTable[sq].key(occ)];
    }

    constexpr Bitboard BlackMagicRookAttacks(Bitboard occ, Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return kBlackMagicAttackTable[kBlackMagicRookTable[sq].key(occ)];
    }

    constexpr Bitboard BlackMagicQueenAttacks(Bitboard occ, Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return BlackMagicBishopAttacks(occ, sq) | BlackMagicRookAttacks(occ, sq);
    }
}

namespace cohen::chess
{
    using cohen::chess::magics::MagicMinKey;
    using cohen::chess::magics::MagicMaxKey;
    using cohen::chess::magics::MagicKeyRange;
    using cohen::chess::magics::MagicWidth;

    using cohen::chess::magics::MagicBishopMask;
    using cohen::chess::magics::MagicRookMask;

    using cohen::chess::magics::FancyMagicBishopAttacks;
    using cohen::chess::magics::FancyMagicRookAttacks;
    using cohen::chess::magics::FancyMagicQueenAttacks;

    using cohen::chess::magics::BlackMagicBishopAttacks;
    using cohen::chess::magics::BlackMagicRookAttacks;
    using cohen::chess::magics::BlackMagicQueenAttacks;
}

#endif