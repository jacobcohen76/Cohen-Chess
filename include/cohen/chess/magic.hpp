#ifndef COHEN_CHESS_MAGIC_HPP_INCLUDED
#define COHEN_CHESS_MAGIC_HPP_INCLUDED

#include <algorithm>
#include <cassert>

#include <cohen/chess/type/bitboard.hpp>
#include <cohen/chess/type/key.hpp>
#include <cohen/chess/type/square.hpp>
#include <cohen/chess/attacks.hpp>

#include <cohen/util/bits.hpp>
#include <cohen/util/functor.hpp>

namespace cohen::chess::magic
{
    template <typename T>
    concept Magic = requires(T magic, Bitboard occ)
    {
        magic.magic;
        magic.key(occ);
    };

    constexpr Key MagicMinKey(Magic auto magic, Bitboard mask) noexcept
    {
        Key  min_key = kKeyAll;
        Bitboard occ = kEmptyBB;
        do
        {
            Key key = magic.key(occ);
            min_key = std::min(min_key, key);
        }
        while ((occ = (occ - mask) & mask));
        return min_key;
    }

    constexpr Key MagicMaxKey(Magic auto magic, Bitboard mask) noexcept
    {
        Key  max_key = kKeyNone;
        Bitboard occ = kEmptyBB;
        do
        {
            Key key = magic.key(occ);
            max_key = std::max(max_key, key);
        }
        while ((occ = (occ - mask) & mask));
        return max_key;
    }

    constexpr Key MagicWidth(Magic auto magic, Bitboard mask) noexcept
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
        return max_key - min_key + 1;
    }

    template <Functor<Bitboard(Square)> auto mask_fn, Magic T>
    constexpr Key MagicTableWidth(std::array<T, kSquareNB> table) noexcept
    {
        Key table_width = kKeyNone;
        for (Square sq = kA1; T magic : table)
        {
            table_width += MagicWidth(magic, mask_fn(sq++));
        }
        return table_width;
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

    inline constexpr std::array<Bitboard, kSquareNB> kMagicRookMaskTable = []()
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
        Key      position;
        Bitboard magic, mask;
        int      shift;

        constexpr Key key(Bitboard occ) const noexcept
        {
            return ((occ & mask) * magic >> shift) + position;
        }
    };

    inline constexpr std::array<Bitboard, kSquareNB> kFancyMagicBishopNumbers =
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

    inline constexpr auto kFancyMagicBishopTable = []()
    {
        std::array<FancyMagic, kSquareNB> magic_table = {};
        std::generate(begin(magic_table), end(magic_table),
        [sq = Square(kA1), curr_key = Key(0)]() mutable -> FancyMagic
        {
            FancyMagic fm = {};
            fm.magic    = kFancyMagicBishopNumbers[sq];
            fm.mask     = MagicBishopMask(sq);
            fm.shift    = kSquareNB - PopCount(MagicBishopMask(sq));
            fm.position = curr_key - MagicMinKey(fm, MagicBishopMask(sq));
            curr_key   += MagicWidth(fm, MagicBishopMask(sq));
            return ++sq, fm;
        });
        return magic_table;
    }();

    inline constexpr auto kFancyMagicBishopAttackTable = []()
    {
        constexpr Key kTableWidth = MagicTableWidth<MagicBishopMask>(kFancyMagicBishopTable);
        std::array<Bitboard, kTableWidth> attacks_table = {};
        std::for_each(std::begin(kFancyMagicBishopTable), std::end(kFancyMagicBishopTable),
        [&attacks_table, sq = Square(kA1)](auto magic) mutable -> void
        {
            Bitboard mask = MagicBishopMask(sq);
            Bitboard  occ = kEmptyBB;
            do
            {
                attacks_table[magic.key(occ)] = RayBishopAttacks(occ, sq);
            }
            while ((occ = (occ - mask) & mask)); ++sq;
        });
        return attacks_table;
    }();

    constexpr Bitboard FancyMagicBishopAttacks(Bitboard occ, Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return kFancyMagicBishopAttackTable[kFancyMagicBishopTable[sq].key(occ)];
    }

    inline constexpr std::array<Bitboard, kSquareNB> kFancyMagicRookNumbers =
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

    inline constexpr auto kFancyMagicRookTable = []()
    {
        std::array<FancyMagic, kSquareNB> magic_table = {};
        std::generate(begin(magic_table), end(magic_table),
        [sq = Square(kA1), curr_key = Key(0)]() mutable -> FancyMagic
        {
            FancyMagic fm = {};
            fm.magic    = kFancyMagicRookNumbers[sq];
            fm.mask     = MagicRookMask(sq);
            fm.shift    = kSquareNB - PopCount(MagicRookMask(sq));
            fm.position = curr_key - MagicMinKey(fm, MagicRookMask(sq));
            curr_key   += MagicWidth(fm, MagicRookMask(sq));
            return ++sq, fm;
        });
        return magic_table;
    }();

    inline constexpr auto kFancyMagicRookAttackTable = []()
    {
        constexpr Key kTableWidth = MagicTableWidth<MagicRookMask>(kFancyMagicRookTable);
        std::array<Bitboard, kTableWidth> attacks_table = {};
        std::for_each(std::begin(kFancyMagicRookTable), std::end(kFancyMagicRookTable),
        [&attacks_table, sq = Square(kA1)](auto magic) mutable -> void
        {
            Bitboard mask = MagicRookMask(sq);
            Bitboard  occ = kEmptyBB;
            do
            {
                attacks_table[magic.key(occ)] = RayRookAttacks(occ, sq);
            }
            while ((occ = (occ - mask) & mask)); ++sq;
        });
        return attacks_table;
    }();

    constexpr Bitboard FancyMagicRookAttacks(Bitboard occ, Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return kFancyMagicRookAttackTable[kFancyMagicRookTable[sq].key(occ)];
    }

    constexpr Bitboard FancyMagicQueenAttacks(Bitboard occ, Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return FancyMagicBishopAttacks(occ, sq) | FancyMagicRookAttacks(occ, sq);
    }

    template <int shift>
    struct BlackMagic
    {
        Key      position;
        Bitboard magic, not_mask;

        constexpr Key key(Bitboard occ) const noexcept
        {
            return ((occ | not_mask) * magic >> (kSquareNB - shift)) + position;
        }
    };

    using BishopBlackMagic = BlackMagic<7>;

    inline constexpr std::array<Bitboard, kSquareNB> kBlackMagicBishopNumbers =
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

    inline constexpr auto kBlackMagicBishopTable = []()
    {
        std::array<BishopBlackMagic, kSquareNB> magic_table = {};
        std::generate(begin(magic_table), end(magic_table),
        [sq = Square(kA1), curr_key = Key(0)]() mutable -> BishopBlackMagic
        {
            BishopBlackMagic bm = {};
            bm.magic    =  kBlackMagicBishopNumbers[sq];
            bm.not_mask = ~MagicBishopMask(sq);
            bm.position =  curr_key - MagicMinKey(bm, MagicBishopMask(sq));
            curr_key   +=  MagicWidth(bm, MagicBishopMask(sq));
            return ++sq, bm;
        });
        return magic_table;
    }();

    inline constexpr auto kBlackMagicBishopAttackTable = []()
    {
        constexpr Key kTableWidth = MagicTableWidth<MagicBishopMask>(kBlackMagicBishopTable);
        std::array<Bitboard, kTableWidth> attacks_table = {};
        std::for_each(std::begin(kBlackMagicBishopTable), std::end(kBlackMagicBishopTable),
        [&attacks_table, sq = Square(kA1)](auto magic) mutable -> void
        {
            Bitboard mask = MagicBishopMask(sq);
            Bitboard  occ = kEmptyBB;
            do
            {
                attacks_table[magic.key(occ)] = RayBishopAttacks(occ, sq);
            }
            while ((occ = (occ - mask) & mask)); ++sq;
        });
        return attacks_table;
    }();

    constexpr Bitboard BlackMagicBishopAttacks(Bitboard occ, Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return kBlackMagicBishopAttackTable[kBlackMagicBishopTable[sq].key(occ)];
    }

    using RookBlackMagic = BlackMagic<9>;

    inline constexpr std::array<Bitboard, kSquareNB> kBlackMagicRookNumbers =
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

    inline constexpr auto kBlackMagicRookTable = []()
    {
        std::array<RookBlackMagic, kSquareNB> magic_table = {};
        std::generate(begin(magic_table), end(magic_table),
        [sq = Square(kA1), curr_key = Key(0)]() mutable -> RookBlackMagic
        {
            RookBlackMagic bm = {};
            bm.magic    =  kBlackMagicRookNumbers[sq];
            bm.not_mask = ~MagicRookMask(sq);
            bm.position =  curr_key - MagicMinKey(bm, MagicRookMask(sq));
            curr_key   +=  MagicWidth(bm, MagicRookMask(sq));
            return ++sq, bm;
        });
        return magic_table;
    }();

    inline constexpr auto kBlackMagicRookAttackTable = []()
    {
        constexpr Key kTableWidth = MagicTableWidth<MagicRookMask>(kBlackMagicRookTable);
        std::array<Bitboard, kTableWidth> attacks_table = {};
        std::for_each(std::begin(kBlackMagicRookTable), std::end(kBlackMagicRookTable),
        [&attacks_table, sq = Square(kA1)](auto magic) mutable -> void
        {
            Bitboard mask = MagicRookMask(sq);
            Bitboard  occ = kEmptyBB;
            do
            {
                attacks_table[magic.key(occ)] = RayRookAttacks(occ, sq);
            }
            while ((occ = (occ - mask) & mask)); ++sq;
        });
        return attacks_table;
    }();

    constexpr Bitboard BlackMagicRookAttacks(Bitboard occ, Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return kBlackMagicRookAttackTable[kBlackMagicRookTable[sq].key(occ)];
    }

    constexpr Bitboard BlackMagicQueenAttacks(Bitboard occ, Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return BlackMagicBishopAttacks(occ, sq) | BlackMagicRookAttacks(occ, sq);
    }
}

namespace cohen::chess
{
    using cohen::chess::magic::MagicBishopMask;
    using cohen::chess::magic::MagicRookMask;
    using cohen::chess::magic::FancyMagicBishopAttacks;
    using cohen::chess::magic::FancyMagicRookAttacks;
    using cohen::chess::magic::BlackMagicBishopAttacks;
    using cohen::chess::magic::BlackMagicRookAttacks;
}

#endif
