#ifndef COHEN_CHESS_ENGINE_ATTACKS_HPP_INCLUDED
#define COHEN_CHESS_ENGINE_ATTACKS_HPP_INCLUDED

#include <types/bitboard.hpp>
#include <types/direction.hpp>
#include <types/key.hpp>
#include <types/piece.hpp>
#include <types/square.hpp>

#include <array>

namespace cohen_chess
{
    template <Color side>
    constexpr Bitboard SetwisePawnAttacks(Bitboard pawns)
    {
        if constexpr (side == kWhite)
        {
            return ShiftBB<kNorthEast>(pawns) | ShiftBB<kNorthWest>(pawns);
        }
        else
        {
            return ShiftBB<kSouthEast>(pawns) | ShiftBB<kSouthWest>(pawns);
        }
    }

    constexpr Bitboard SetwisePawnAttacks(Bitboard pawns, Color side)
    {
        if (side == kWhite)
        {
            return SetwisePawnAttacks<kWhite>(pawns);
        }
        else
        {
            return SetwisePawnAttacks<kBlack>(pawns); 
        }
    }

    constexpr Bitboard SetwiseKnightAttacks(Bitboard knights)
    {
        return ShiftBB<kNorthNorthEast>(knights) | ShiftBB<kEastEastNorth>(knights) |
               ShiftBB<kNorthNorthWest>(knights) | ShiftBB<kEastEastSouth>(knights) |
               ShiftBB<kSouthSouthEast>(knights) | ShiftBB<kWestWestNorth>(knights) |
               ShiftBB<kSouthSouthWest>(knights) | ShiftBB<kWestWestSouth>(knights);
    }

    constexpr Bitboard SetwiseKingAttacks(Bitboard kings)
    {
        Bitboard attacks = ShiftBB<kEast>(kings) | ShiftBB<kWest>(kings);
        kings   |= attacks;
        attacks |= ShiftBB<kNorth>(kings) | ShiftBB<kSouth>(kings);
        return attacks;
    }

    constexpr std::array<std::array<Bitboard, kSquareNB>, kColorNB> kPawnAttackTable = []()
    {
        std::array<std::array<Bitboard, kSquareNB>, kColorNB> attack_table = {};
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            attack_table[kWhite][sq] = SetwisePawnAttacks<kWhite>(SquareBB(sq));
            attack_table[kBlack][sq] = SetwisePawnAttacks<kBlack>(SquareBB(sq));
        }
        return attack_table;
    }();

    constexpr Bitboard PawnAttacks(Square sq, Color side)
    {
        return kPawnAttackTable[side][sq];
    }

    constexpr std::array<Bitboard, kSquareNB> kKnightAttackTable = []()
    {
        std::array<Bitboard, kSquareNB> attack_table = {};
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            attack_table[sq] = SetwiseKingAttacks(SquareBB(sq));
        }
        return attack_table;
    }();

    constexpr Bitboard KnightAttacks(Square sq)
    {
        return kKnightAttackTable[sq];
    }

    constexpr std::array<Bitboard, kSquareNB> kKingAttackTable = []()
    {
        std::array<Bitboard, kSquareNB> attack_table = {};
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            attack_table[sq] = SetwiseKingAttacks(SquareBB(sq));
        }
        return attack_table;
    }();

    constexpr Bitboard KingAttacks(Square sq)
    {
        return kKingAttackTable[sq];
    }

    constexpr Bitboard RayBishopAttacks(Bitboard occ, Square sq)
    {
        return RayBB<kNorthEast>(occ, sq) | RayBB<kNorthWest>(occ, sq) |
               RayBB<kSouthEast>(occ, sq) | RayBB<kSouthWest>(occ, sq);
    }

    constexpr Bitboard RayRookAttacks(Bitboard occ, Square sq)
    {
        return RayBB<kNorth>(occ, sq) | RayBB<kEast>(occ, sq) |
               RayBB<kSouth>(occ, sq) | RayBB<kWest>(occ, sq);
    }

    constexpr Bitboard RayQueenAttacks(Bitboard occ, Square sq)
    {
        return RayBishopAttacks(occ, sq) | RayRookAttacks(occ, sq);
    }

    struct Magic
    {
        Key         begin;
        Bitboard    magic;
        Bitboard    mask;
        int         shift;

        constexpr Key key(Bitboard occ) const
        {
            return ((occ & mask) * magic >> shift) + begin;
        }
    };

    constexpr size_t MagicSize(Magic m)
    {
        Key max_key = kKeyZero;
        Bitboard occ = kEmptyBB;
        do
        {
            max_key = std::max(max_key, m.key(occ));
        }
        while ((occ = (occ - m.mask) & m.mask));
        return max_key - m.begin + 1;
    }

    constexpr size_t MagicTableSize(std::array<Magic, kSquareNB> table)
    {
        size_t size = 0;
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            size += MagicSize(table[sq]);
        }
        return size;
    }

    constexpr Bitboard MagicBishopMask(Square sq)
    {
        return ((DiagBB(DiagOf(sq)) | AntiBB(AntiOf(sq))) & ~SquareBB(sq)) & ~kEdgesBB;
    }

    constexpr std::array<Bitboard, kSquareNB> kMagicBishopNumbers =
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

    constexpr std::array<Magic, kSquareNB> kMagicBishopTable = []()
    {
        size_t table_pos = 0;
        std::array<Magic, kSquareNB> magic_table = {};
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            Magic& m = magic_table[sq];
            m.begin     = table_pos;
            m.magic     = kMagicBishopNumbers[sq];
            m.mask      = MagicBishopMask(sq);
            m.shift     = kSquareNB - PopCount(m.mask);
            table_pos  += MagicSize(m);
        }
        return magic_table;
    }();

    constexpr std::array<Bitboard, MagicTableSize(kMagicBishopTable)> kMagicBishopAttackTable = []()
    {
        std::array<Bitboard, MagicTableSize(kMagicBishopTable)> attack_table = {};
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            Magic m = kMagicBishopTable[sq];
            Bitboard occ = kEmptyBB;
            do
            {
                attack_table[m.key(occ)] = RayBishopAttacks(occ, sq);
            }
            while ((occ = (occ - m.mask) & m.mask));
        }
        return attack_table;
    }();

    constexpr Bitboard MagicRookMask(Square sq)
    {
        return ((RankBB(RankOf(sq)) & ~kRankEdgesBB) | (FileBB(FileOf(sq)) & ~kFileEdgesBB)) & ~SquareBB(sq);
    }

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

    constexpr std::array<Magic, kSquareNB> kMagicRookTable = []()
    {
        size_t table_pos = 0;
        std::array<Magic, kSquareNB> magic_table = {};
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            Magic& m = magic_table[sq];
            m.begin     = table_pos;
            m.magic     = kMagicRookNumbers[sq];
            m.mask      = MagicRookMask(sq);
            m.shift     = kSquareNB - PopCount(m.mask);
            table_pos  += MagicSize(m);
        }
        return magic_table;
    }();

    constexpr std::array<Bitboard, MagicTableSize(kMagicRookTable)> kMagicRookAttackTable = []()
    {
        std::array<Bitboard, MagicTableSize(kMagicRookTable)> attack_table = {};
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            Magic m = kMagicRookTable[sq];
            Bitboard occ = kEmptyBB;
            do
            {
                attack_table[m.key(occ)] = RayRookAttacks(occ, sq);
            }
            while ((occ = (occ - m.mask) & m.mask));
        }
        return attack_table;
    }();

    constexpr Bitboard MagicBishopAttacks(Bitboard occ, Square sq)
    {
        return kMagicBishopAttackTable[kMagicBishopTable[sq].key(occ)];
    }

    constexpr Bitboard MagicRookAttacks(Bitboard occ, Square sq)
    {
        return kMagicRookAttackTable[kMagicRookTable[sq].key(occ)];
    }

    constexpr Bitboard MagicQueenAttacks(Bitboard occ, Square sq)
    {
        return MagicBishopAttacks(occ, sq) | MagicRookAttacks(occ, sq);
    }
}

#endif