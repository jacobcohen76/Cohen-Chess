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

    constexpr Bitboard RuntimeMagicBishopMask(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        Bitboard mask = kEmptyBB;
        mask |=  DiagBB(DiagOf(sq));
        mask |=  AntiBB(AntiOf(sq));
        mask &= ~SquareBB(sq) & ~kEdgesBB;
        return mask;
    }

    constexpr std::array<Bitboard, kSquareNB> kMagicBishopMaskTable = []()
    {
        std::array<Bitboard, kSquareNB> mask_table = {};
        std::generate(std::begin(mask_table), std::end(mask_table),
        [sq = Square(kA1)]() mutable -> Bitboard
        {
            return RuntimeMagicBishopMask(sq++);
        });
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

    constexpr std::array<Bitboard, kSquareNB> kMagicRookMaskTable = []()
    {
        std::array<Bitboard, kSquareNB> mask_table = {};
        std::generate(std::begin(mask_table), std::end(mask_table),
        [sq = Square(kA1)]() mutable -> Bitboard
        {
            return RuntimeMagicRookMask(sq++);
        });
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
        Key      begin;
        Bitboard magic, mask;
        int      shift;

        constexpr Key index(Bitboard occ) const noexcept
        {
            return ((occ & mask) * magic >> shift) + begin;
        }
    };

    constexpr std::array<Bitboard, kSquareNB> kFancyMagicBishopNumbers =
    {
        0x1020830406840840, 0x10E0214141409A88, 0x405000A251180664, 0x2AE2AA09600046CA, 0x05920A10B4425210, 0x4002091018015824, 0xA239280583080000, 0x01021A058182C005,
        0x9A8022174401006D, 0x46620382C3040067, 0x402D444C41820061, 0x40408820882C0020, 0x0133520A1091A120, 0x6E13011002302011, 0x00B8A198D0060B01, 0xA001AA00718604A4,
        0x11400162340C0092, 0x0810090D12A804D0, 0x2018206402440228, 0x9408041404321240, 0x2352002402314002, 0x1044400601102720, 0x40A4080162420361, 0x0C49000264389218,
        0x161C400530108980, 0xA510104014249085, 0x82148804D00FC030, 0x0022008008008013, 0x401E8C0049802005, 0x131C090114900280, 0xC488A10004014812, 0x1000610100440203,
        0x0110020844204852, 0x6AE8882804201208, 0x086440E800300050, 0x0304440101300900, 0x4170840A400C0100, 0x06010206002C0900, 0x00082205888C028D, 0x0284C900401F040E,
        0x1834792004601002, 0x00A0440A08832001, 0x020201004800E103, 0x20601C2013000805, 0x204040210A000100, 0x3B50051007200100, 0x6026102147A03200, 0x222C409586040B08,
        0x00ACA9902C065A08, 0xE030807108532E90, 0x0008B11240D0A807, 0x150412A084040204, 0x339004517A0A0200, 0x4100601505720029, 0xA0B00BC610908B10, 0xA00C729984621045,
        0x2E545090D18A971C, 0x125AB600C146C314, 0x0211110132389020, 0x4294700222104405, 0x4460904820842420, 0x3280312554101160, 0x04A02023D2411860, 0x004002919400D818,
    };

    constexpr std::array<Bitboard, kSquareNB> kMagicRookNumbers =
    {
        0x0080042390400280, 0x50C0086002300042, 0x8880082001801000, 0x0080080010002480, 0x0200205402004870, 0x88800C0002008021, 0x740008030C841026, 0xC2000100640884C6,
        0xF982800981A04001, 0x642380400083A00C, 0x10070050C101A000, 0x2005002850042100, 0x1682000600202A0E, 0x0181004A08140100, 0x0402002200880124, 0xA004802041000180,
        0x0450818000C00032, 0x2EE1010063824000, 0x22A0030010410362, 0x3004A10050010008, 0x20D8808028002401, 0x008E2801100C6040, 0x0B09B40005060890, 0x01B1360010418C01,
        0x2123400580009061, 0x60008301004002A4, 0x0205024100200791, 0x000A0042001188A0, 0x5686040080080080, 0x20063400800A0080, 0xACF1184400091002, 0x7F4098820001095C,
        0x009480C0008002F0, 0xA30840018B002500, 0x4E05C20012002580, 0xC280820800801000, 0x0427005205000800, 0x0002000402003008, 0x4422B11A14001008, 0x6022C0410E002584,
        0x1182C00022808008, 0x0404400708810024, 0x8020018010008020, 0x6100100102490020, 0x4546004805220010, 0x0A40601040080124, 0x12051045420C0018, 0x4180B1440A820003,
        0x01108301A4420200, 0x020160048E400280, 0x0063001040A00700, 0x00F0500268008180, 0x0010280100901500, 0x0162000910040200, 0x91463A0510080400, 0x004080050002F480,
        0x6204800411004121, 0x014000C102887221, 0x0180CC6000114101, 0x04E058A012420052, 0x0403001004822801, 0x022A000108100426, 0x218D011008049A34, 0x20A8C3804C03006A,
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