#include "engine.h"
#include "hash.h"
#include "io.h"
#include "types.h"
#include "util.h"

#include <iostream>

using namespace cohen_chess;

void BootEngine()
{
    bit_util::InitPopCountTable(bit_util::kU16PopCountTable, sizeof(bit_util::kU16PopCountTable) / sizeof(uint8_t));
    direction::InitRayBetween(direction::kRayBetween);

    bitboard::InitLineBitboards(bitboard::kLineBitboards);
    bitboard::InitBetweenBitboards(bitboard::kBetweenBitboards);

    attacks::InitPawnAttackTable(attacks::kPawnAttackTable);
    attacks::InitKnightAttackTable(attacks::kKnightAttackTable);
    attacks::InitKingAttackTable(attacks::kKingAttackTable);
    attacks::InitBishopMagicTable();
    attacks::InitRookMagicTable();
}

int main(int argc, char* argv[])
{
    BootEngine();
    for(Square sq = kA1; sq < kSquareNB; ++sq)
    {
        //Bitboard bb = KingAttacks(sq);
        //std::string hex_string = util::HexString(bb);
        //std::string ascii_board = io::AsciiBoard<kWhite>(bb);
        //std::cout << "0x" << hex_string << std::endl;
        //std::cout << ascii_board << std::endl;
        //std::cout << std::endl;

        std::string white_pawn_attacks_ascii_board = io::AsciiBoard<kWhite>(PawnAttacks(kWhite, sq));
        std::string black_pawn_attacks_ascii_board = io::AsciiBoard<kWhite>(PawnAttacks(kBlack, sq));
        std::string knight_attacks_ascii_board = io::AsciiBoard<kWhite>(KnightAttacks(sq));
        std::string king_attacks_ascii_board = io::AsciiBoard<kWhite>(KingAttacks(sq));
        
        std::string gap(3, ' '), str;
        str = util::HorizontalMerge(white_pawn_attacks_ascii_board, black_pawn_attacks_ascii_board, gap);
        str = util::HorizontalMerge(str, knight_attacks_ascii_board, gap);
        str = util::HorizontalMerge(str, king_attacks_ascii_board, gap);
        std::cout << str << std::endl << std::endl;
    }
    return 0;
}
