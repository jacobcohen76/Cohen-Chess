#ifndef COHEN_CHESS_MAGIC_BITBOARDS_HPP_INCLUDED
#define COHEN_CHESS_MAGIC_BITBOARDS_HPP_INCLUDED

#include "cohen/chess/type/square.hpp"
#include <concepts>
#include <span>

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

    template <typename GenType>
    constexpr void FillMagicTable(
        GenType*                                   table,
        Functor<     Key(Square, Bitboard)> auto&& key_fn,
        Functor< GenType(Square, Bitboard)> auto&& gen_fn,
        Functor<Bitboard(Square)>           auto&& mask_fn) noexcept
    {
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            Bitboard mask = mask_fn(sq);
            Bitboard occ  = kEmptyBB;
            do
            {
                table[key_fn(sq, occ)] = gen_fn(sq, occ);
            }
            while ((occ = CarryRipple(occ, mask)));
        }
    }

    template <Magic MagicType>
    constexpr void FillMagicAttackTable(
        Bitboard*                                  attack_table,
        std::span<MagicType, kSquareNB>            magic_table,
        Functor<Bitboard(Square, Bitboard)> auto&& gen_fn,
        Functor<Bitboard(Square)>           auto&& mask_fn) noexcept
    {
        const auto key_fn = [&](Square sq, Bitboard occ)
        {
            return magic_table[sq].key(occ);
        };
        FillMagicTable(attack_table, key_fn, gen_fn, mask_fn);
    }

    template <uint8_t* offset_table, Magic MagicType>
    constexpr void FillMagicAttackTable(
        Bitboard*                                  attack_table,
        std::span<MagicType, kSquareNB>            magic_table,
        Functor<Bitboard(Square, Bitboard)> auto&& gen_fn,
        Functor<Bitboard(Square)>           auto&& mask_fn) noexcept
    {
        const auto key_fn = [&](Square sq, Bitboard occ)
        {
            return magic_table[sq].key<offset_table>(occ);
        };
        FillMagicTable(attack_table, key_fn, gen_fn, mask_fn);
    }

    template <Key size, Magic BishopMagic, Magic RookMagic>
    constexpr std::array<Bitboard, size> MakeMagicAttackTable(
        const std::array<BishopMagic, kSquareNB>& bishop_table,
        const std::array<  RookMagic, kSquareNB>& rook_table) noexcept
    {
        std::array<Bitboard, size> attack_table = {};
        FillMagicAttackTable(std::data(attack_table), std::span{bishop_table}, RayBishopAttacks, MagicBishopMask);
        FillMagicAttackTable(std::data(attack_table), std::span{rook_table},   RayRookAttacks,   MagicRookMask);
        return attack_table;
    }

    template <Key size, uint8_t* offset_table, Magic BishopMagic, Magic RookMagic>
    constexpr std::array<Bitboard, size> MakeMagicAttackTable(
        const std::array<BishopMagic, kSquareNB>& bishop_table,
        const std::array<  RookMagic, kSquareNB>& rook_table) noexcept
    {
        std::array<Bitboard, size> attack_table = {};
        FillMagicAttackTable<offset_table>(std::data(attack_table), std::span{bishop_table}, RayBishopAttacks, MagicBishopMask);
        FillMagicAttackTable<offset_table>(std::data(attack_table), std::span{rook_table},   RayRookAttacks,   MagicRookMask);
        return attack_table;
    }

    template <Magic MagicType>
    constexpr void FillMagicOffsetTable(
        uint8_t*                                   offset_table,
        std::span<MagicType, kSquareNB>            magic_table,
        Functor<Bitboard(Square, Bitboard)> auto&& attacks_fn,
        Functor<Bitboard(Square)>           auto&& mask_fn) noexcept
    {
        using GenBuff = std::array<Bitboard, 256>;
        std::array<GenBuff, kSquareNB> gen_table = {};
        std::array<uint8_t, kSquareNB> key_table = {};
        auto key_fn = [&](Square sq, Bitboard occ)
        {
            return magic_table[sq].key(occ);
        };
        auto gen_fn = [&](Square sq, Bitboard occ) -> uint8_t
        {
            Bitboard attacks = attacks_fn(sq, occ);
            auto& gen_buff = gen_table[sq];
            auto* found = std::ranges::find(gen_buff, attacks);
            if (found == std::end(gen_buff))
            {
                uint8_t& key  = key_table[sq];
                gen_buff[key] = attacks;
                return key++;
            }
            return found - std::begin(gen_buff);
        };
        FillMagicTable(offset_table, key_fn, gen_fn, mask_fn);
    }

    template <Key size, Magic BishopMagic, Magic RookMagic>
    constexpr std::array<uint8_t, size> MakeMagicOffsetTable(
        const std::array<BishopMagic, kSquareNB>& bishop_table,
        const std::array<  RookMagic, kSquareNB>& rook_table) noexcept
    {
        std::array<uint8_t, size> offset_table = {};
        FillMagicOffsetTable(std::data(offset_table), std::span{bishop_table}, RayBishopAttacks, MagicBishopMask);
        FillMagicOffsetTable(std::data(offset_table), std::span{rook_table},   RayRookAttacks,   MagicRookMask);
        return offset_table;
    }

    struct FancyMagic
    {
        Bitboard magic, mask;
        Key      offset;
        int      shift;

        constexpr Key key(Bitboard occ) const noexcept
        {
            return (magic * (occ & mask) >> shift) + offset;
        }
    };

    template <int shift>
    struct BlackMagic
    {
        Bitboard magic, not_mask;
        Key      offset;

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

    inline constexpr std::array<FancyMagic, kSquareNB> kFancyBishopMagicTable =
    {
        FancyMagic{0xFFEDF9FD7CFCFFFF, MagicBishopMask(kA1),    0, kSquareNB - 5},
        FancyMagic{0xFC0962854A77F576, MagicBishopMask(kB1),   32, kSquareNB - 4},
        FancyMagic{0x405000A251180664, MagicBishopMask(kC1),   48, kSquareNB - 5},
        FancyMagic{0x2AE2AA09600046CA, MagicBishopMask(kD1),   79, kSquareNB - 5},
        FancyMagic{0x05920A10B4425210, MagicBishopMask(kE1),  110, kSquareNB - 5},
        FancyMagic{0x4002091018015824, MagicBishopMask(kF1),  142, kSquareNB - 5},
        FancyMagic{0xFC0A66C64A7EF576, MagicBishopMask(kG1),  174, kSquareNB - 4},
        FancyMagic{0x7FFDFDFCBD79FFFF, MagicBishopMask(kH1),  190, kSquareNB - 5},
        FancyMagic{0xFC0846A64A34FFF6, MagicBishopMask(kA2),  222, kSquareNB - 4},
        FancyMagic{0xFC087A874A3CF7F6, MagicBishopMask(kB2),  238, kSquareNB - 4},
        FancyMagic{0x402D444C41820061, MagicBishopMask(kC2),  254, kSquareNB - 5},
        FancyMagic{0x40408820882C0020, MagicBishopMask(kD2),  286, kSquareNB - 5},
        FancyMagic{0x0133520A1091A120, MagicBishopMask(kE2),  318, kSquareNB - 5},
        FancyMagic{0x6E13011002302011, MagicBishopMask(kF2),  350, kSquareNB - 5},
        FancyMagic{0xFC0864AE59B4FF76, MagicBishopMask(kG2),  382, kSquareNB - 4},
        FancyMagic{0x3C0860AF4B35FF76, MagicBishopMask(kH2),  398, kSquareNB - 4},
        FancyMagic{0x73C01AF56CF4CFFB, MagicBishopMask(kA3),  414, kSquareNB - 4},
        FancyMagic{0x41A01CFAD64AAFFC, MagicBishopMask(kB3),  430, kSquareNB - 4},
        FancyMagic{0x2018206402440228, MagicBishopMask(kC3),  446, kSquareNB - 7},
        FancyMagic{0x9408041404321240, MagicBishopMask(kD3),  574, kSquareNB - 7},
        FancyMagic{0x2352002402314002, MagicBishopMask(kE3),  702, kSquareNB - 7},
        FancyMagic{0x1044400601102720, MagicBishopMask(kF3),  830, kSquareNB - 7},
        FancyMagic{0x7C0C028F5B34FF76, MagicBishopMask(kG3),  958, kSquareNB - 4},
        FancyMagic{0xFC0A028E5AB4DF76, MagicBishopMask(kH3),  974, kSquareNB - 4},
        FancyMagic{0x161C400530108980, MagicBishopMask(kA4),  990, kSquareNB - 5},
        FancyMagic{0xA510104014249085, MagicBishopMask(kB4), 1022, kSquareNB - 5},
        FancyMagic{0x82148804D00FC030, MagicBishopMask(kC4), 1054, kSquareNB - 7},
        FancyMagic{0x0022008008008013, MagicBishopMask(kD4), 1182, kSquareNB - 9},
        FancyMagic{0x401E8C0049802005, MagicBishopMask(kE4), 1694, kSquareNB - 9},
        FancyMagic{0x131C090114900280, MagicBishopMask(kF4), 2206, kSquareNB - 7},
        FancyMagic{0xC488A10004014812, MagicBishopMask(kG4), 2334, kSquareNB - 5},
        FancyMagic{0x1000610100440203, MagicBishopMask(kH4), 2366, kSquareNB - 5},
        FancyMagic{0x0110020844204852, MagicBishopMask(kA5), 2398, kSquareNB - 5},
        FancyMagic{0x6AE8882804201208, MagicBishopMask(kB5), 2430, kSquareNB - 5},
        FancyMagic{0x086440E800300050, MagicBishopMask(kC5), 2462, kSquareNB - 7},
        FancyMagic{0x0304440101300900, MagicBishopMask(kD5), 2590, kSquareNB - 9},
        FancyMagic{0x4170840A400C0100, MagicBishopMask(kE5), 3102, kSquareNB - 9},
        FancyMagic{0x06010206002C0900, MagicBishopMask(kF5), 3614, kSquareNB - 7},
        FancyMagic{0x00082205888C028D, MagicBishopMask(kG5), 3742, kSquareNB - 5},
        FancyMagic{0x0284C900401F040E, MagicBishopMask(kH5), 3774, kSquareNB - 5},
        FancyMagic{0xDCEFD9B54BFCC09F, MagicBishopMask(kA6), 3806, kSquareNB - 4},
        FancyMagic{0xF95FFA765AFD602B, MagicBishopMask(kB6), 3822, kSquareNB - 4},
        FancyMagic{0x020201004800E103, MagicBishopMask(kC6), 3838, kSquareNB - 7},
        FancyMagic{0x20601C2013000805, MagicBishopMask(kD6), 3966, kSquareNB - 7},
        FancyMagic{0x204040210A000100, MagicBishopMask(kE6), 4094, kSquareNB - 7},
        FancyMagic{0x3B50051007200100, MagicBishopMask(kF6), 4222, kSquareNB - 7},
        FancyMagic{0x43FF9A5CF4CA0C01, MagicBishopMask(kG6), 4350, kSquareNB - 4},
        FancyMagic{0x4BFFCD8E7C587601, MagicBishopMask(kH6), 4366, kSquareNB - 4},
        FancyMagic{0xFC0FF2865334F576, MagicBishopMask(kA7), 4382, kSquareNB - 4},
        FancyMagic{0xFC0BF6CE5924F576, MagicBishopMask(kB7), 4398, kSquareNB - 4},
        FancyMagic{0x0008B11240D0A807, MagicBishopMask(kC7), 4414, kSquareNB - 5},
        FancyMagic{0x150412A084040204, MagicBishopMask(kD7), 4445, kSquareNB - 5},
        FancyMagic{0x339004517A0A0200, MagicBishopMask(kE7), 4477, kSquareNB - 5},
        FancyMagic{0x4100601505720029, MagicBishopMask(kF7), 4509, kSquareNB - 5},
        FancyMagic{0xC3FFB7DC36CA8C89, MagicBishopMask(kG7), 4541, kSquareNB - 4},
        FancyMagic{0xC3FF8A54F4CA2C89, MagicBishopMask(kH7), 4557, kSquareNB - 4},
        FancyMagic{0xFFFFFCFCFD79EDFF, MagicBishopMask(kA8), 4573, kSquareNB - 5},
        FancyMagic{0xFC0863FCCB147576, MagicBishopMask(kB8), 4605, kSquareNB - 4},
        FancyMagic{0x0211110132389020, MagicBishopMask(kC8), 4621, kSquareNB - 5},
        FancyMagic{0x4294700222104405, MagicBishopMask(kD8), 4652, kSquareNB - 5},
        FancyMagic{0x4460904820842420, MagicBishopMask(kE8), 4684, kSquareNB - 5},
        FancyMagic{0x3280312554101160, MagicBishopMask(kF8), 4716, kSquareNB - 5},
        FancyMagic{0xFC087E8E4BB2F736, MagicBishopMask(kG8), 4747, kSquareNB - 4},
        FancyMagic{0x43FF9E4EF4CA2C89, MagicBishopMask(kH8), 4763, kSquareNB - 5},
    };

    inline constexpr std::array<FancyMagic, kSquareNB> kFancyRookMagicTable =
    {
        FancyMagic{0x0080042390400280, MagicRookMask(kA1),  4795, kSquareNB - 12},
        FancyMagic{0x50C0086002300042, MagicRookMask(kB1),  8891, kSquareNB - 11},
        FancyMagic{0x8880082001801000, MagicRookMask(kC1), 10939, kSquareNB - 11},
        FancyMagic{0x0080080010002480, MagicRookMask(kD1), 12987, kSquareNB - 11},
        FancyMagic{0x0200205402004870, MagicRookMask(kE1), 15035, kSquareNB - 11},
        FancyMagic{0x88800C0002008021, MagicRookMask(kF1), 17083, kSquareNB - 11},
        FancyMagic{0x740008030C841026, MagicRookMask(kG1), 19131, kSquareNB - 11},
        FancyMagic{0xC2000100640884C6, MagicRookMask(kH1), 21179, kSquareNB - 12},
        FancyMagic{0xF982800981A04001, MagicRookMask(kA2), 25275, kSquareNB - 11},
        FancyMagic{0x642380400083A00C, MagicRookMask(kB2), 27323, kSquareNB - 10},
        FancyMagic{0x10070050C101A000, MagicRookMask(kC2), 28347, kSquareNB - 10},
        FancyMagic{0x2005002850042100, MagicRookMask(kD2), 29371, kSquareNB - 10},
        FancyMagic{0x1682000600202A0E, MagicRookMask(kE2), 30395, kSquareNB - 10},
        FancyMagic{0x0181004A08140100, MagicRookMask(kF2), 31419, kSquareNB - 10},
        FancyMagic{0x0402002200880124, MagicRookMask(kG2), 32443, kSquareNB - 10},
        FancyMagic{0xA004802041000180, MagicRookMask(kH2), 33467, kSquareNB - 11},
        FancyMagic{0x0450818000C00032, MagicRookMask(kA3), 35515, kSquareNB - 11},
        FancyMagic{0x2EE1010063824000, MagicRookMask(kB3), 37563, kSquareNB - 10},
        FancyMagic{0x22A0030010410362, MagicRookMask(kC3), 38587, kSquareNB - 10},
        FancyMagic{0x3004A10050010008, MagicRookMask(kD3), 39611, kSquareNB - 10},
        FancyMagic{0x20D8808028002401, MagicRookMask(kE3), 40635, kSquareNB - 10},
        FancyMagic{0x008E2801100C6040, MagicRookMask(kF3), 41659, kSquareNB - 10},
        FancyMagic{0x0B09B40005060890, MagicRookMask(kG3), 42683, kSquareNB - 10},
        FancyMagic{0x01B1360010418C01, MagicRookMask(kH3), 43707, kSquareNB - 11},
        FancyMagic{0x2123400580009061, MagicRookMask(kA4), 45755, kSquareNB - 11},
        FancyMagic{0x60008301004002A4, MagicRookMask(kB4), 47803, kSquareNB - 10},
        FancyMagic{0x0205024100200791, MagicRookMask(kC4), 48827, kSquareNB - 10},
        FancyMagic{0x000A0042001188A0, MagicRookMask(kD4), 49851, kSquareNB - 10},
        FancyMagic{0x5686040080080080, MagicRookMask(kE4), 50875, kSquareNB - 10},
        FancyMagic{0x20063400800A0080, MagicRookMask(kF4), 51899, kSquareNB - 10},
        FancyMagic{0xACF1184400091002, MagicRookMask(kG4), 52923, kSquareNB - 10},
        FancyMagic{0x7F4098820001095C, MagicRookMask(kH4), 53947, kSquareNB - 11},
        FancyMagic{0x009480C0008002F0, MagicRookMask(kA5), 55995, kSquareNB - 11},
        FancyMagic{0xA30840018B002500, MagicRookMask(kB5), 58043, kSquareNB - 10},
        FancyMagic{0x4E05C20012002580, MagicRookMask(kC5), 59067, kSquareNB - 10},
        FancyMagic{0xC280820800801000, MagicRookMask(kD5), 60091, kSquareNB - 10},
        FancyMagic{0x0427005205000800, MagicRookMask(kE5), 61115, kSquareNB - 10},
        FancyMagic{0x0002000402003008, MagicRookMask(kF5), 62139, kSquareNB - 10},
        FancyMagic{0x4422B11A14001008, MagicRookMask(kG5), 63163, kSquareNB - 10},
        FancyMagic{0x6022C0410E002584, MagicRookMask(kH5), 64187, kSquareNB - 11},
        FancyMagic{0x1182C00022808008, MagicRookMask(kA6), 66235, kSquareNB - 11},
        FancyMagic{0x0404400708810024, MagicRookMask(kB6), 68283, kSquareNB - 10},
        FancyMagic{0x8020018010008020, MagicRookMask(kC6), 69307, kSquareNB - 10},
        FancyMagic{0x6100100102490020, MagicRookMask(kD6), 70331, kSquareNB - 10},
        FancyMagic{0x4546004805220010, MagicRookMask(kE6), 71355, kSquareNB - 10},
        FancyMagic{0x0A40601040080124, MagicRookMask(kF6), 72379, kSquareNB - 10},
        FancyMagic{0x12051045420C0018, MagicRookMask(kG6), 73403, kSquareNB - 10},
        FancyMagic{0x4180B1440A820003, MagicRookMask(kH6), 74427, kSquareNB - 11},
        FancyMagic{0x48FFFE99FECFAA00, MagicRookMask(kA7), 76475, kSquareNB - 10},
        FancyMagic{0x48FFFE99FECFAA00, MagicRookMask(kB7), 77499, kSquareNB -  9},
        FancyMagic{0x497FFFADFF9C2E00, MagicRookMask(kC7), 78011, kSquareNB -  9},
        FancyMagic{0x613FFFDDFFCE9200, MagicRookMask(kD7), 78523, kSquareNB -  9},
        FancyMagic{0xFFFFFFE9FFE7CE00, MagicRookMask(kE7), 79035, kSquareNB -  9},
        FancyMagic{0xFFFFFFF5FFF3E600, MagicRookMask(kF7), 79547, kSquareNB -  9},
        FancyMagic{0x0003FF95E5E6A4C0, MagicRookMask(kG7), 80059, kSquareNB -  9},
        FancyMagic{0x510FFFF5F63C96A0, MagicRookMask(kH7), 80571, kSquareNB - 10},
        FancyMagic{0xEBFFFFB9FF9FC526, MagicRookMask(kA8), 81595, kSquareNB - 11},
        FancyMagic{0x61FFFEDDFEEDAEAE, MagicRookMask(kB8), 83643, kSquareNB - 10},
        FancyMagic{0x53BFFFEDFFDEB1A2, MagicRookMask(kC8), 84667, kSquareNB - 10},
        FancyMagic{0x127FFFB9FFDFB5F6, MagicRookMask(kD8), 85691, kSquareNB - 10},
        FancyMagic{0x411FFFDDFFDBF4D6, MagicRookMask(kE8), 86715, kSquareNB - 10},
        FancyMagic{0x022A000108100426, MagicRookMask(kF8), 87739, kSquareNB - 11},
        FancyMagic{0x0003FFEF27EEBE74, MagicRookMask(kG8), 89787, kSquareNB - 10},
        FancyMagic{0x7645FFFECBFEA79E, MagicRookMask(kH8), 90811, kSquareNB - 11},
    };

    inline constexpr auto kFancyMagicAttackTable = MakeMagicAttackTable<92859>(
        kFancyBishopMagicTable, kFancyRookMagicTable);

    constexpr Bitboard FancyMagicBishopAttacks(Square sq, Bitboard occ) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        const FancyMagic& magic = kFancyBishopMagicTable[sq];
        return kFancyMagicAttackTable[magic.key(occ)];
    }

    constexpr Bitboard FancyMagicRookAttacks(Square sq, Bitboard occ) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        const FancyMagic& magic = kFancyRookMagicTable[sq];
        return kFancyMagicAttackTable[magic.key(occ)];
    }

    inline constexpr auto kFancyMagicOffsetTable = MakeMagicOffsetTable<92859>(
        kFancyBishopMagicTable, kFancyRookMagicTable);

    inline constexpr std::array<BlackBishopMagic, kSquareNB> kBlackBishopMagicTable =
    {
        BlackBishopMagic{0x107AC08050500BFF, ~MagicBishopMask(kA1), 66157},
        BlackBishopMagic{0x7FFFDFDFD823FFFD, ~MagicBishopMask(kB1), 71730},
        BlackBishopMagic{0x0400C00FE8000200, ~MagicBishopMask(kC1), 37781},
        BlackBishopMagic{0x103F802004000000, ~MagicBishopMask(kD1), 21015},
        BlackBishopMagic{0xC03FE00100000000, ~MagicBishopMask(kE1), 47590},
        BlackBishopMagic{0x24C00BFFFF400000, ~MagicBishopMask(kF1),   835},
        BlackBishopMagic{0x0808101F40007F04, ~MagicBishopMask(kG1), 23592},
        BlackBishopMagic{0x100808201EC00080, ~MagicBishopMask(kH1), 30599},
        BlackBishopMagic{0xFFA2FEFFBFEFB7FF, ~MagicBishopMask(kA2), 68776},
        BlackBishopMagic{0x083E3EE040080801, ~MagicBishopMask(kB2), 19959},
        BlackBishopMagic{0x040180BFF7E80080, ~MagicBishopMask(kC2), 21783},
        BlackBishopMagic{0x0440007FE0031000, ~MagicBishopMask(kD2), 64836},
        BlackBishopMagic{0x2010007FFC000000, ~MagicBishopMask(kE2), 23417},
        BlackBishopMagic{0x1079FFE000FF8000, ~MagicBishopMask(kF2), 66724},
        BlackBishopMagic{0x7F83FFDFC03FFF80, ~MagicBishopMask(kG2), 74542},
        BlackBishopMagic{0x080614080FA00040, ~MagicBishopMask(kH2), 67266},
        BlackBishopMagic{0x7FFE7FFF817FCFF9, ~MagicBishopMask(kA3), 26575},
        BlackBishopMagic{0x7FFEBFFFA01027FD, ~MagicBishopMask(kB3), 67543},
        BlackBishopMagic{0x20018000C00F3C01, ~MagicBishopMask(kC3), 24409},
        BlackBishopMagic{0x407E0001000FFB8A, ~MagicBishopMask(kD3), 30779},
        BlackBishopMagic{0x201FE000FFF80010, ~MagicBishopMask(kE3), 17384},
        BlackBishopMagic{0xFFDFEFFFDE39FFEF, ~MagicBishopMask(kF3), 18778},
        BlackBishopMagic{0x7FFFF800203FBFFF, ~MagicBishopMask(kG3), 65109},
        BlackBishopMagic{0x7FF7FBFFF8203FFF, ~MagicBishopMask(kH3), 20184},
        BlackBishopMagic{0x000000FE04004070, ~MagicBishopMask(kA4), 38240},
        BlackBishopMagic{0x7FFF7F9FFFC0EFF9, ~MagicBishopMask(kB4), 16459},
        BlackBishopMagic{0x7FFEFF7F7F01F7FD, ~MagicBishopMask(kC4), 17432},
        BlackBishopMagic{0x3F6EFBBF9EFBFFFF, ~MagicBishopMask(kD4), 81040},
        BlackBishopMagic{0x0410008F01003FFD, ~MagicBishopMask(kE4), 84946},
        BlackBishopMagic{0x20002038001C8010, ~MagicBishopMask(kF4), 18276},
        BlackBishopMagic{0x087FF038000FC001, ~MagicBishopMask(kG4),  8512},
        BlackBishopMagic{0x00080C0C00083007, ~MagicBishopMask(kH4), 78544},
        BlackBishopMagic{0x00000080FC82C040, ~MagicBishopMask(kA5), 19974},
        BlackBishopMagic{0x000000407E416020, ~MagicBishopMask(kB5), 23850},
        BlackBishopMagic{0x00600203F8008020, ~MagicBishopMask(kC5), 11056},
        BlackBishopMagic{0xD003FEFE04404080, ~MagicBishopMask(kD5), 68019},
        BlackBishopMagic{0x100020801800304A, ~MagicBishopMask(kE5), 85965},
        BlackBishopMagic{0x7FBFFE700BFFE800, ~MagicBishopMask(kF5), 80524},
        BlackBishopMagic{0x107FF00FE4000F90, ~MagicBishopMask(kG5), 38221},
        BlackBishopMagic{0x7F8FFFCFF1D007F8, ~MagicBishopMask(kH5), 64647},
        BlackBishopMagic{0x0000004100F88080, ~MagicBishopMask(kA6), 61320},
        BlackBishopMagic{0x00000020807C4040, ~MagicBishopMask(kB6), 67281},
        BlackBishopMagic{0x00000041018700C0, ~MagicBishopMask(kC6), 79076},
        BlackBishopMagic{0x0010000080FC4080, ~MagicBishopMask(kD6), 17115},
        BlackBishopMagic{0x1000003C80180030, ~MagicBishopMask(kE6), 50718},
        BlackBishopMagic{0x2006001CF00C0018, ~MagicBishopMask(kF6), 24659},
        BlackBishopMagic{0xFFFFFFBFEFF80FDC, ~MagicBishopMask(kG6), 38291},
        BlackBishopMagic{0x000000101003F812, ~MagicBishopMask(kH6), 30605},
        BlackBishopMagic{0x0800001F40808200, ~MagicBishopMask(kA7), 37759},
        BlackBishopMagic{0x084000101F3FD208, ~MagicBishopMask(kB7),  4639},
        BlackBishopMagic{0x080000000F808081, ~MagicBishopMask(kC7), 21759},
        BlackBishopMagic{0x0004000008003F80, ~MagicBishopMask(kD7), 67799},
        BlackBishopMagic{0x08000001001FE040, ~MagicBishopMask(kE7), 22841},
        BlackBishopMagic{0x085F7D8000200A00, ~MagicBishopMask(kF7), 66689},
        BlackBishopMagic{0xFFFFFEFFBFEFF81D, ~MagicBishopMask(kG7), 62548},
        BlackBishopMagic{0xFFBFFFEFEFDFF70F, ~MagicBishopMask(kH7), 66597},
        BlackBishopMagic{0x100000101EC10082, ~MagicBishopMask(kA8), 86749},
        BlackBishopMagic{0x7FBAFFFFEFE0C02F, ~MagicBishopMask(kB8), 69558},
        BlackBishopMagic{0x7F83FFFFFFF07F7F, ~MagicBishopMask(kC8), 61589},
        BlackBishopMagic{0xFFF1FFFFFFF7FFC1, ~MagicBishopMask(kD8), 62533},
        BlackBishopMagic{0x0878040000FFE01F, ~MagicBishopMask(kE8), 64387},
        BlackBishopMagic{0x005D00000120200A, ~MagicBishopMask(kF8), 26581},
        BlackBishopMagic{0x0840800080200FDA, ~MagicBishopMask(kG8), 76355},
        BlackBishopMagic{0x100000C05F582008, ~MagicBishopMask(kH8), 11140},
    };

    inline constexpr std::array<BlackRookMagic, kSquareNB> kBlackRookMagicTable =
    {
        BlackRookMagic{0x80280013FF84FFFF, ~MagicRookMask(kA1), 10890},
        BlackRookMagic{0x5FFBFEFDFEF67FFF, ~MagicRookMask(kB1), 56054},
        BlackRookMagic{0xFFEFFAFFEFFDFFFF, ~MagicRookMask(kC1), 67495},
        BlackRookMagic{0x003000900300008A, ~MagicRookMask(kD1), 72797},
        BlackRookMagic{0x0030018003500030, ~MagicRookMask(kE1), 17179},
        BlackRookMagic{0x0020012120A00020, ~MagicRookMask(kF1), 63978},
        BlackRookMagic{0x0030006000C00030, ~MagicRookMask(kG1), 56650},
        BlackRookMagic{0xFFA8008DFF09FFF8, ~MagicRookMask(kH1), 15929},
        BlackRookMagic{0x7FBFF7FBFBEAFFFC, ~MagicRookMask(kA2), 55905},
        BlackRookMagic{0x0000140081050002, ~MagicRookMask(kB2), 26301},
        BlackRookMagic{0x0000180043800048, ~MagicRookMask(kC2), 78100},
        BlackRookMagic{0x7FFFE800021FFFB8, ~MagicRookMask(kD2), 86245},
        BlackRookMagic{0xFFFFCFFE7FCFFFAF, ~MagicRookMask(kE2), 75228},
        BlackRookMagic{0x00001800C0180060, ~MagicRookMask(kF2), 31661},
        BlackRookMagic{0xFFFFE7FF8FBFFFE8, ~MagicRookMask(kG2), 38053},
        BlackRookMagic{0x0000180030620018, ~MagicRookMask(kH2), 37433},
        BlackRookMagic{0x00300018010C0003, ~MagicRookMask(kA3), 74747},
        BlackRookMagic{0x0003000C0085FFFF, ~MagicRookMask(kB3), 53847},
        BlackRookMagic{0xFFFDFFF7FBFEFFF7, ~MagicRookMask(kC3), 70952},
        BlackRookMagic{0x7FC1FFDFFC001FFF, ~MagicRookMask(kD3), 49447},
        BlackRookMagic{0xFFFEFFDFFDFFDFFF, ~MagicRookMask(kE3), 62629},
        BlackRookMagic{0x7C108007BEFFF81F, ~MagicRookMask(kF3), 58996},
        BlackRookMagic{0x20408007BFE00810, ~MagicRookMask(kG3), 36009},
        BlackRookMagic{0x0400800558604100, ~MagicRookMask(kH3), 21230},
        BlackRookMagic{0x0040200010080008, ~MagicRookMask(kA4), 51882},
        BlackRookMagic{0x0010020008040004, ~MagicRookMask(kB4), 11841},
        BlackRookMagic{0xFFFDFEFFF7FBFFF7, ~MagicRookMask(kC4), 25794},
        BlackRookMagic{0xFEBF7DFFF8FEFFF9, ~MagicRookMask(kD4), 49689},
        BlackRookMagic{0xC00000FFE001FFE0, ~MagicRookMask(kE4), 63400},
        BlackRookMagic{0x2008208007004007, ~MagicRookMask(kF4), 33958},
        BlackRookMagic{0xBFFBFAFFFB683F7F, ~MagicRookMask(kG4), 21991},
        BlackRookMagic{0x0807F67FFA102040, ~MagicRookMask(kH4), 45618},
        BlackRookMagic{0x200008E800300030, ~MagicRookMask(kA5), 70134},
        BlackRookMagic{0x0000008780180018, ~MagicRookMask(kB5), 75944},
        BlackRookMagic{0x0000010300180018, ~MagicRookMask(kC5), 68392},
        BlackRookMagic{0x4000008180180018, ~MagicRookMask(kD5), 66472},
        BlackRookMagic{0x008080310005FFFA, ~MagicRookMask(kE5), 23236},
        BlackRookMagic{0x4000188100060006, ~MagicRookMask(kF5), 19067},
        BlackRookMagic{0xFFFFFF7FFFBFBFFF, ~MagicRookMask(kG5),     0},
        BlackRookMagic{0x0000802000200040, ~MagicRookMask(kH5), 43566},
        BlackRookMagic{0x20000202EC002800, ~MagicRookMask(kA6), 29810},
        BlackRookMagic{0xFFFFF9FF7CFFF3FF, ~MagicRookMask(kB6), 65558},
        BlackRookMagic{0x000000404B801800, ~MagicRookMask(kC6), 77684},
        BlackRookMagic{0x2000002FE03FD000, ~MagicRookMask(kD6), 73350},
        BlackRookMagic{0xFFFFFF6FFE7FCFFD, ~MagicRookMask(kE6), 61765},
        BlackRookMagic{0xBFF7EFFFBFC00FFF, ~MagicRookMask(kF6), 49282},
        BlackRookMagic{0x000000100800A804, ~MagicRookMask(kG6), 78840},
        BlackRookMagic{0xFFFBFFEFA7FFA7FE, ~MagicRookMask(kH6), 82904},
        BlackRookMagic{0x0000052800140028, ~MagicRookMask(kA7), 24594},
        BlackRookMagic{0x00000085008A0014, ~MagicRookMask(kB7),  9513},
        BlackRookMagic{0x8000002B00408028, ~MagicRookMask(kC7), 29012},
        BlackRookMagic{0x4000002040790028, ~MagicRookMask(kD7), 27684},
        BlackRookMagic{0x7800002010288028, ~MagicRookMask(kE7), 27901},
        BlackRookMagic{0x0000001800E08018, ~MagicRookMask(kF7), 61477},
        BlackRookMagic{0x1890000810580050, ~MagicRookMask(kG7), 25719},
        BlackRookMagic{0x2003D80000500028, ~MagicRookMask(kH7), 50020},
        BlackRookMagic{0xFFFFF37EEFEFDFBE, ~MagicRookMask(kA8), 41547},
        BlackRookMagic{0x40000280090013C1, ~MagicRookMask(kB8),  4750},
        BlackRookMagic{0xBF7FFEFFBFFAF71F, ~MagicRookMask(kC8),  6014},
        BlackRookMagic{0xFFFDFFFF777B7D6E, ~MagicRookMask(kD8), 41529},
        BlackRookMagic{0xEEFFFFEFF0080BFE, ~MagicRookMask(kE8), 84192},
        BlackRookMagic{0xAFE0000FFF780402, ~MagicRookMask(kF8), 33433},
        BlackRookMagic{0xEE73FFFBFFBB77FE, ~MagicRookMask(kG8),  8555},
        BlackRookMagic{0x0002000308482882, ~MagicRookMask(kH8),  1009},
    };

    inline constexpr auto kBlackMagicAttackTable = MakeMagicAttackTable<88507>(
        kBlackBishopMagicTable, kBlackRookMagicTable);

    constexpr Bitboard BlackMagicBishopAttacks(Square sq, Bitboard occ) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        const BlackBishopMagic& magic = kBlackBishopMagicTable[sq];
        return kBlackMagicAttackTable[magic.key(occ)];
    }

    constexpr Bitboard BlackMagicRookAttacks(Square sq, Bitboard occ) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        const BlackRookMagic& magic = kBlackRookMagicTable[sq];
        return kBlackMagicAttackTable[magic.key(occ)];
    }

    inline constexpr std::array<ByteBlackBishopMagic, kSquareNB> kByteBlackBishopMagicTable =
    {
        ByteBlackBishopMagic{kBlackBishopMagicTable[kA1],    0},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kB1],    7},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kC1],   13},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kD1],   23},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kE1],   35},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kF1],   47},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kG1],   57},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kH1],   63},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kA2],   70},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kB2],   76},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kC2],   82},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kD2],   92},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kE2],  104},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kF2],  116},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kG2],  126},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kH2],  132},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kA3],  138},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kB3],  148},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kC3],  158},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kD3],  198},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kE3],  246},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kF3],  294},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kG3],  334},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kH3],  344},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kA4],  354},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kB4],  366},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kC4],  378},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kD4],  426},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kE4],  534},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kF4],  642},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kG4],  690},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kH4],  702},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kA5],  714},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kB5],  726},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kC5],  738},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kD5],  786},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kE5],  894},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kF5], 1002},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kG5], 1050},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kH5], 1062},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kA6], 1074},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kB6], 1084},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kC6], 1094},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kD6], 1134},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kE6], 1182},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kF6], 1230},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kG6], 1270},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kH6], 1280},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kA7], 1290},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kB7], 1296},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kC7], 1302},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kD7], 1312},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kE7], 1324},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kF7], 1336},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kG7], 1346},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kH7], 1352},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kA8], 1358},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kB8], 1365},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kC8], 1371},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kD8], 1381},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kE8], 1393},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kF8], 1405},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kG8], 1415},
        ByteBlackBishopMagic{kBlackBishopMagicTable[kH8], 1421},
    };

    inline constexpr std::array<ByteBlackRookMagic, kSquareNB> kByteBlackRookMagicTable =
    {
        ByteBlackRookMagic{kBlackRookMagicTable[kA1], 1428},
        ByteBlackRookMagic{kBlackRookMagicTable[kB1], 1477},
        ByteBlackRookMagic{kBlackRookMagicTable[kC1], 1519},
        ByteBlackRookMagic{kBlackRookMagicTable[kD1], 1589},
        ByteBlackRookMagic{kBlackRookMagicTable[kE1], 1673},
        ByteBlackRookMagic{kBlackRookMagicTable[kF1], 1757},
        ByteBlackRookMagic{kBlackRookMagicTable[kG1], 1827},
        ByteBlackRookMagic{kBlackRookMagicTable[kH1], 1869},
        ByteBlackRookMagic{kBlackRookMagicTable[kA2], 1918},
        ByteBlackRookMagic{kBlackRookMagicTable[kB2], 1960},
        ByteBlackRookMagic{kBlackRookMagicTable[kC2], 1996},
        ByteBlackRookMagic{kBlackRookMagicTable[kD2], 2056},
        ByteBlackRookMagic{kBlackRookMagicTable[kE2], 2128},
        ByteBlackRookMagic{kBlackRookMagicTable[kF2], 2200},
        ByteBlackRookMagic{kBlackRookMagicTable[kG2], 2260},
        ByteBlackRookMagic{kBlackRookMagicTable[kH2], 2296},
        ByteBlackRookMagic{kBlackRookMagicTable[kA3], 2338},
        ByteBlackRookMagic{kBlackRookMagicTable[kB3], 2408},
        ByteBlackRookMagic{kBlackRookMagicTable[kC3], 2468},
        ByteBlackRookMagic{kBlackRookMagicTable[kD3], 2568},
        ByteBlackRookMagic{kBlackRookMagicTable[kE3], 2688},
        ByteBlackRookMagic{kBlackRookMagicTable[kF3], 2808},
        ByteBlackRookMagic{kBlackRookMagicTable[kG3], 2908},
        ByteBlackRookMagic{kBlackRookMagicTable[kH3], 2968},
        ByteBlackRookMagic{kBlackRookMagicTable[kA4], 3038},
        ByteBlackRookMagic{kBlackRookMagicTable[kB4], 3122},
        ByteBlackRookMagic{kBlackRookMagicTable[kC4], 3194},
        ByteBlackRookMagic{kBlackRookMagicTable[kD4], 3314},
        ByteBlackRookMagic{kBlackRookMagicTable[kE4], 3458},
        ByteBlackRookMagic{kBlackRookMagicTable[kF4], 3602},
        ByteBlackRookMagic{kBlackRookMagicTable[kG4], 3722},
        ByteBlackRookMagic{kBlackRookMagicTable[kH4], 3794},
        ByteBlackRookMagic{kBlackRookMagicTable[kA5], 3878},
        ByteBlackRookMagic{kBlackRookMagicTable[kB5], 3962},
        ByteBlackRookMagic{kBlackRookMagicTable[kC5], 4034},
        ByteBlackRookMagic{kBlackRookMagicTable[kD5], 4154},
        ByteBlackRookMagic{kBlackRookMagicTable[kE5], 4298},
        ByteBlackRookMagic{kBlackRookMagicTable[kF5], 4442},
        ByteBlackRookMagic{kBlackRookMagicTable[kG5], 4562},
        ByteBlackRookMagic{kBlackRookMagicTable[kH5], 4634},
        ByteBlackRookMagic{kBlackRookMagicTable[kA6], 4718},
        ByteBlackRookMagic{kBlackRookMagicTable[kB6], 4788},
        ByteBlackRookMagic{kBlackRookMagicTable[kC6], 4848},
        ByteBlackRookMagic{kBlackRookMagicTable[kD6], 4948},
        ByteBlackRookMagic{kBlackRookMagicTable[kE6], 5068},
        ByteBlackRookMagic{kBlackRookMagicTable[kF6], 5188},
        ByteBlackRookMagic{kBlackRookMagicTable[kG6], 5288},
        ByteBlackRookMagic{kBlackRookMagicTable[kH6], 5348},
        ByteBlackRookMagic{kBlackRookMagicTable[kA7], 5418},
        ByteBlackRookMagic{kBlackRookMagicTable[kB7], 5460},
        ByteBlackRookMagic{kBlackRookMagicTable[kC7], 5496},
        ByteBlackRookMagic{kBlackRookMagicTable[kD7], 5556},
        ByteBlackRookMagic{kBlackRookMagicTable[kE7], 5628},
        ByteBlackRookMagic{kBlackRookMagicTable[kF7], 5700},
        ByteBlackRookMagic{kBlackRookMagicTable[kG7], 5760},
        ByteBlackRookMagic{kBlackRookMagicTable[kH7], 5796},
        ByteBlackRookMagic{kBlackRookMagicTable[kA8], 5838},
        ByteBlackRookMagic{kBlackRookMagicTable[kB8], 5887},
        ByteBlackRookMagic{kBlackRookMagicTable[kC8], 5929},
        ByteBlackRookMagic{kBlackRookMagicTable[kD8], 5999},
        ByteBlackRookMagic{kBlackRookMagicTable[kE8], 6083},
        ByteBlackRookMagic{kBlackRookMagicTable[kF8], 6167},
        ByteBlackRookMagic{kBlackRookMagicTable[kG8], 6237},
        ByteBlackRookMagic{kBlackRookMagicTable[kH8], 6279},
    };

    inline constexpr auto kBlackMagicOffsetTable = MakeMagicOffsetTable<88507>(
        kBlackBishopMagicTable, kBlackRookMagicTable);

    inline constexpr auto kByteBlackMagicAttackTable =
        MakeMagicAttackTable<6328, std::data(kBlackMagicOffsetTable)>(
            kByteBlackBishopMagicTable, kByteBlackRookMagicTable);

    constexpr Bitboard ByteBlackMagicBishopAttacks(Square sq, Bitboard occ) noexcept
    {
        constexpr const uint8_t* offset_table = std::data(kBlackMagicOffsetTable);
        const BlackBishopMagic& magic = kBlackBishopMagicTable[sq];
        return kByteBlackMagicAttackTable[magic.key<offset_table>(occ)]
    }

    constexpr Bitboard ByteBlackMagicRookAttacks(Square sq, Bitboard occ) noexcept
    {
        constexpr const uint8_t* offset_table = std::data(kBlackMagicOffsetTable);
        const BlackRookMagic& magic = kBlackRookMagicTable[sq];
        return kByteBlackMagicAttackTable[magic.key<offset_table>(occ)]
    }
}

// namespace cohen::chess
// {
//     using cohen::chess::magic_bitboards::MagicBishopMask;
//     using cohen::chess::magic_bitboards::MagicRookMask;
// }

#endif