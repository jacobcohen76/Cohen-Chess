#ifndef COHEN_CHESS_ENGINE_ATTACKS_H_INCLUDED
#define COHEN_CHESS_ENGINE_ATTACKS_H_INCLUDED

#include "../types/bitboard.h"
#include "../types/direction.h"
#include "../types/key.h"
#include "../types/piece_type.h"
#include "../types/square.h"

namespace cohen_chess
{
    template <Color side>
    constexpr Bitboard SetwisePawnAttacks(Bitboard pawns)
    {
        if constexpr (side == kWhite)
            return ShiftBB<kNorthEast>(pawns) | ShiftBB<kNorthWest>(pawns);
        else
            return ShiftBB<kSouthEast>(pawns) | ShiftBB<kSouthWest>(pawns);
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

    constexpr Bitboard BishopMask(Square sq)
    {
        return ((DiagBB(DiagOf(sq)) | AntiBB(AntiOf(sq))) & ~SquareBB(sq)) & ~kEdgesBB;
    }

    constexpr Bitboard RookMask(Square sq)
    {
        return ((RankBB(RankOf(sq)) & ~kRankEdgesBB) | (FileBB(FileOf(sq)) & ~kFileEdgesBB)) & ~SquareBB(sq);
    }

    template <typename Magic>
    constexpr size_t MagicSize(Magic m)
    {
        Key max_key = kKeyZero;
        Bitboard occ = kEmptyBB;
        do
            max_key = std::max(max_key, m.key(occ));
        while ((occ = (occ - m.mask) & m.mask));
        return max_key - m.start + 1;
    }

    template <typename Magic>
    constexpr size_t MagicTableSize(std::array<Magic, kSquareNB> table)
    {
        size_t size = 0;
        for (Square sq = kA1; sq < kSquareNB; ++sq)
            size += MagicSize(table[sq]);
        return size;
    }

    struct FancyMagic
    {
        Key         start;
        Bitboard    magic;
        Bitboard    mask;
        int         shift;

        constexpr Key key(Bitboard occ) const
        {
            return ((occ & mask) * magic >> shift) + start;
        }
    };

    constexpr Bitboard FancyMagicBishopAttacks(Bitboard occ, Square sq)
    {
        constexpr std::array<Bitboard, kSquareNB> kMagicNumbers =
        {
            0xD8F25A869CF6A34F, 0xF385EBE2E0DC808C, 0x41A40D450E7EE10F, 0xE87C1C0081DCA923, 0xA85710C04784FE18, 0xE332080F086570BA, 0x5B8F6AD6AE38D707, 0x48C3324C0357FFEB, 
            0x02A2C4A494F2740A, 0x86B3668EE2E9047F, 0x2C66A841FC0FEE58, 0x7748EC0C2982BA4C, 0xECF0CA1210578DE1, 0x06FF1BB477F1A0C6, 0xC9A43062C325CC73, 0x2E4090CCA9A1C412, 
            0x743F9CDA6F8AA595, 0x74606B52DA868EC2, 0xB23007B80648C368, 0x351F013E0617FE36, 0x98D400875C2072D8, 0x81D4E0AA0190083D, 0xECE2FF562090E26C, 0xD0F061E1C9897300, 
            0x74705036C15A3A11, 0xCF44200F1E3A0421, 0x931E500178028053, 0x0000000000000000, 0x0000000000000000, 0x802D92005F011780, 0xAC2C1B04159CFF8D, 0xC410809449034802, 
            0xFDBA70404AF0AA20, 0xF85B30125688283E, 0x735C020803490745, 0x0000000000000000, 0x0000000000000000, 0xC14A4282003700CF, 0x2125B6D6EC7C0467, 0xDAF4011A08C347CD, 
            0x02DD9004228E5042, 0x022A445AA4C19FF5, 0x9C0271D0880BF00D, 0xC0DE0EE01309A807, 0x4BC4C00319060600, 0xBA61220B82047900, 0xA2590D18DBFD7A1C, 0x73F0294CC5D07501, 
            0x8050C2EC0C05A743, 0x6C41C0C146830090, 0x3D9EBB1E48903369, 0x31C3C14B420A0168, 0xE99EE830D60A1388, 0x360DDC2D2ECDFF08, 0x56EB7655E145D095, 0x2E30970C82B656F3, 
            0x01A3FDE2AE0C6360, 0xCAD33DDBC66D7271, 0x268ADCD86A05104C, 0x56084FB86920882F, 0xBC79F20C50260626, 0x87FF52D0B5AE5514, 0xB50BBF46A5F17461, 0x92562AADF46B99DC,
        };
        constexpr std::array<FancyMagic, kSquareNB> kMagicTable = [](std::array<Bitboard, kSquareNB> magic_numbers)
        {
            size_t table_pos = 0;
            std::array<FancyMagic, kSquareNB> magic_table = {};
            for (Square sq = kA1; sq < kSquareNB; ++sq)
            {
                FancyMagic& fm = magic_table[sq];
                fm.start    = table_pos;
                fm.magic    = magic_numbers[sq];
                fm.mask     = BishopMask(sq);
                fm.shift    = kSquareNB - PopCount(fm.mask);
                table_pos += MagicSize(fm);
            }
            return magic_table;
        }(kMagicNumbers);
        constexpr std::array<Bitboard, MagicTableSize(kMagicTable)> kAttackTable = [&](std::array<FancyMagic, kSquareNB> magic_table)
        {
            std::array<Bitboard, MagicTableSize(kMagicTable)> attack_table;
            for (Square sq = kA1; sq < kSquareNB; ++sq)
            {
                FancyMagic m = magic_table[sq];
                Bitboard occ = kEmptyBB;
                do
                    attack_table[m.key(occ)] = RayBishopAttacks(occ, sq);
                while ((occ = (occ - m.mask) & m.mask));
            }
            return attack_table;
        }(kMagicTable);
        return kAttackTable[kMagicTable[sq].key(occ)];
    }

    constexpr Bitboard FancyMagicRookAttacks(Bitboard occ, Square sq)
    {
        constexpr std::array<Bitboard, kSquareNB> kMagicNumbers =
        {
            0x40A021B231800140, 0xA002041020080050, 0x0020900140800830, 0x00B0000401002009, 0x8031020411000688, 0x84008007E0804102, 0x482400A151010006, 0x040C208000200041,
            0x1142940004002020, 0x0108924000120022, 0x4180200000040804, 0x0504021000201010, 0x000C842100008008, 0x0C08409204904004, 0x000E000C00410011, 0x0681408030018011,
            0x2022050480606040, 0x8028040480005010, 0x0020062000010408, 0x213000A80C280104, 0x0A00044000408082, 0x8C00021C2004A501, 0x201C820000400101, 0x0409004290040601,
            0x0082E02A60110042, 0x3045208A01082292, 0x2108620002001041, 0x10320088C0004612, 0x0100500400160805, 0x2002000800200412, 0x21A1020800280401, 0x4100068B04100041,
            0xC020002004044012, 0x0410320004008304, 0x0A80200002108010, 0x0880080998808010, 0x0300241000090108, 0x0200100404000802, 0x0080428000008019, 0x0100008320440451,
            0x9000400000004022, 0x0840101000204804, 0x8800401028280051, 0x0821001830014010, 0x0800802B80008004, 0x8C00404080010205, 0x0040202010008322, 0x2002808000230043,
            0x00400080801099A1, 0x00400041421100A0, 0x0581120048004022, 0x004412003000200A, 0x01000480000008A4, 0x0A014040910006C4, 0xC408040209483202, 0x0000404040000081,
            0x0080804100002019, 0x002100120000488A, 0x4944200100088911, 0x1031204200000806, 0x0044100310011008, 0xD500010908000204, 0x8000890622001802, 0x502020812005A063,
        };
        constexpr std::array<FancyMagic, kSquareNB> kMagicTable = [](std::array<Bitboard, kSquareNB> magic_numbers)
        {
            size_t table_pos = 0;
            std::array<FancyMagic, kSquareNB> magic_table = {};
            for (Square sq = kA1; sq < kSquareNB; ++sq)
            {
                FancyMagic& fm = magic_table[sq];
                fm.start    = table_pos;
                fm.magic    = magic_numbers[sq];
                fm.mask     = RookMask(sq);
                fm.shift    = kSquareNB - PopCount(fm.mask);
                table_pos += MagicSize(fm);
            }
            return magic_table;
        }(kMagicNumbers);
        constexpr std::array<Bitboard, MagicTableSize(kMagicTable)> kAttackTable = [](std::array<FancyMagic, kSquareNB> magic_table)
        {
            std::array<Bitboard, MagicTableSize(kMagicTable)> attack_table;
            for (Square sq = kA1; sq < kSquareNB; ++sq)
            {
                FancyMagic m = magic_table[sq];
                Bitboard occ = kEmptyBB;
                do
                    attack_table[m.key(occ)] = RayRookAttacks(occ, sq);
                while ((occ = (occ - m.mask) & m.mask));
            }
            return attack_table;
        }(kMagicTable);
        return kAttackTable[kMagicTable[sq].key(occ)];
    }
}

#endif