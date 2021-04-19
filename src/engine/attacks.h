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

    constexpr Bitboard MagicBishopMask(Square sq)
    {
        return ((DiagBB(DiagOf(sq)) | AntiBB(AntiOf(sq))) & ~SquareBB(sq)) & ~kEdgesBB;
    }

    constexpr Bitboard MagicRookMask(Square sq)
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
        return max_key - m.begin + 1;
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
        Key         begin;
        Bitboard    magic;
        Bitboard    mask;
        int         shift;

        constexpr Key key(Bitboard occ) const
        {
            return ((occ & mask) * magic >> shift) + begin;
        }
    };

    constexpr Bitboard FancyMagicBishopAttacks(Bitboard occ, Square sq)
    {
        constexpr std::array<Bitboard, kSquareNB> kMagicNumbers =
        {
            0x12090E02D0644820, 0xF385EBE2E0DC808C, 0x41A40D450E7EE10F, 0xE87C1C0081DCA923, 0xA85710C04784FE18, 0xE332080F086570BA, 0x5B8F6AD6AE38D707, 0x48C3324C0357FFEB, 
            0x02A2C4A494F2740A, 0x86B3668EE2E9047F, 0x2C66A841FC0FEE58, 0x7748EC0C2982BA4C, 0xECF0CA1210578DE1, 0x06FF1BB477F1A0C6, 0xC9A43062C325CC73, 0x2E4090CCA9A1C412, 
            0x743F9CDA6F8AA595, 0x74606B52DA868EC2, 0xB23007B80648C368, 0x351F013E0617FE36, 0x98D400875C2072D8, 0x81D4E0AA0190083D, 0xECE2FF562090E26C, 0xD0F061E1C9897300, 
            0x74705036C15A3A11, 0xCF44200F1E3A0421, 0x931E500178028053, 0x4044010080A01880, 0x8810840041812012, 0x802D92005F011780, 0xAC2C1B04159CFF8D, 0xC410809449034802, 
            0xFDBA70404AF0AA20, 0xF85B30125688283E, 0x735C020803490745, 0x1842960083880080, 0x4004040400023100, 0xC14A4282003700CF, 0x2125B6D6EC7C0467, 0xDAF4011A08C347CD, 
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
                fm.begin    = table_pos;
                fm.magic    = magic_numbers[sq];
                fm.mask     = MagicBishopMask(sq);
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
            0x44800040008210A4, 0x0A00211200410080, 0x508008A000829000, 0x0100100005004820, 0x86002200300C2008, 0x0600011200481C50, 0x04000A1004910804, 0x0200010410458322,
            0x5A018001C00C2680, 0x24220020410E0181, 0x40110010A002C100, 0x0161002050010208, 0x13A200080C102200, 0x041801200840100C, 0x00010023000A0004, 0x2082001060820104, 
            0x19E1888004400022, 0x2091820022010846, 0x8CA1010010A00048, 0x1419010022100069, 0xC841010010A80004, 0x2025010008A40002, 0x0108640010811842, 0x0129820000740385,
            0xC2028005002100C0, 0x2106400300210583, 0x2430048080326002, 0x84007001000AE102, 0x8010040080800800, 0x540C3C0080020080, 0x0B00901400291836, 0x4808011200018A54,
            0x2A024002A2800092, 0x8063802501004004, 0x08CA420082001021, 0x202200A832004020, 0x15A890623A001A00, 0xCE62860080800400, 0xC909001C0100A200, 0x0800954122000984,
            0x2424806640018003, 0x040981044202002C, 0x0006C06001050011, 0x9000100021010008, 0x080100104801002D, 0x9A22000810020084, 0x4428182605740010, 0x0926804100820004, 
            0x01958020430A0A00, 0x950886C004A10900, 0x24A2021080604A00, 0x153A900100E23900, 0x8004DC8800110100, 0xB101804401120080, 0xA0D6D05832011C00, 0x1086040D0B95C200, 
            0x02020820F1018242, 0x0811809102204001, 0x4C10420010092082, 0x8183001001642039, 0x1212001C1020781A, 0x0C0200190410A802, 0x28004D1618100284, 0x9894424504008062,
        };
        constexpr std::array<FancyMagic, kSquareNB> kMagicTable = [](std::array<Bitboard, kSquareNB> magic_numbers)
        {
            size_t table_pos = 0;
            std::array<FancyMagic, kSquareNB> magic_table = {};
            for (Square sq = kA1; sq < kSquareNB; ++sq)
            {
                FancyMagic& fm = magic_table[sq];
                fm.begin    = table_pos;
                fm.magic    = magic_numbers[sq];
                fm.mask     = MagicRookMask(sq);
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