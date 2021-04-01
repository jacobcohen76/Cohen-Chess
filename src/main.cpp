#include "engine.h"
#include "hash.h"
#include "io.h"
#include "types.h"
#include "util.h"

#include <chrono>
#include <iostream>
#include <thread>

using namespace cohen_chess;

void InitEngine()
{
    bit_util::InitPopCountTable(bit_util::kU16PopCountTable, sizeof(bit_util::kU16PopCountTable) / sizeof(uint8_t));

    direction::InitRayBetween(direction::kRayBetween);

    //zobrist::InitPieceOnSquareKeys(zobrist::kPieceOnSquareKeys, );
    //zobrist::InitCastlingRightsKeys(zobrist::kCastlingRightsKeys, );
    //zobrist::InitEnPassantFileTargetKeys(zobrist::kEnPassantFileTargetKeys, )

    bitboard::InitLineBitboards(bitboard::kLineBitboards);
    bitboard::InitBetweenBitboards(bitboard::kBetweenBitboards);

    attacks::InitPawnAttackTable(attacks::kPawnAttackTable);
    attacks::InitKnightAttackTable(attacks::kKnightAttackTable);
    attacks::InitKingAttackTable(attacks::kKingAttackTable);
    
    //attacks::InitBishopMagicTable(attacks::kBishopMagicTable, attacks::kMagicAttackTable);
    //attacks::InitRookMagicTable(attacks::kRookMagicTable, attacks::kMagicAttackTable);
}

int main(int argc, char* argv[])
{
    InitEngine();
    Bitboard wpawn_bb = RankBB(kRank2);
    Bitboard wpawn_attacks = SetwisePawnAttacks(kWhite, wpawn_attacks);
    std::string lhs = io::AsciiBoard(wpawn_bb, ".p");
    std::string rhs = io::AsciiBoard(wpawn_attacks, ".x");
    std::cout << util::HorizontalMerge<true> (lhs, rhs, " | ") << std::endl << std::endl
              << util::HorizontalMerge<false>(lhs, rhs, " | ") << std::endl;
    

    Bitboard bb = SquareBB(kC3);
    Bitboard occ = SquareBB(kC7);
    std::cout << io::AsciiBoard(RayBB<kNorth>(bb, occ)) << std::endl;

    return 0;
}
