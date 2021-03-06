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

    for(Square sq = kA1; sq < kSquareNB; ++sq)
    {
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

    // std::chrono::nanoseconds sleep_time(0);

    Bitboard mask, occ, attacks;
    for(Square sq = kA1; sq < kSquareNB; ++sq)
    {
        std::cout << "sq = " << io::CoordinateString(sq) << std::endl;
        mask = (DiagBB(DiagOf(sq)) | AntiBB(AntiOf(sq))) & ~SquareBB(sq) & ~kEdgesBB;
        occ = kEmptyBB;
        do
        {
            attacks = IterativeBishopAttacks(occ, sq);
            std::string sq_str = "Square:\n" + io::AsciiBoard(SquareBB(sq));
            std::string mask_str = "Mask:\n" + io::AsciiBoard(mask);
            std::string occ_str = "Occupancy:\n" + io::AsciiBoard(occ);
            std::string attacks_str = "Attacks:\n" + io::AsciiBoard(attacks);
            std::string gap(3, ' ');

            // std::system("clear");
            std::cout << util::HorizontalMerge(sq_str, util::HorizontalMerge(mask_str, util::HorizontalMerge(occ_str, attacks_str, gap), gap), gap) << std::endl << std::endl;
            // std::this_thread::sleep_for(sleep_time);
        } while(occ = (occ - mask) & mask);
    }
    for(Square sq = kA1; sq < kSquareNB; ++sq)
    {
        std::cout << "sq = " << io::CoordinateString(sq) << std::endl;
        mask = ((RankBB(RankOf(sq)) & ~kRankEdgesBB) | (FileBB(FileOf(sq)) & ~kFileEdgesBB)) & ~SquareBB(sq);
        occ = kEmptyBB;
        do
        {
            attacks = IterativeRookAttacks(occ, sq);
            std::string sq_str = "Square:\n" + io::AsciiBoard(SquareBB(sq));
            std::string mask_str = "Mask:\n" + io::AsciiBoard(mask);
            std::string occ_str = "Occupancy:\n" + io::AsciiBoard(occ);
            std::string attacks_str = "Attacks:\n" + io::AsciiBoard(attacks);
            std::string gap(3, ' ');

            // std::system("clear");
            std::cout << util::HorizontalMerge(sq_str, util::HorizontalMerge(mask_str, util::HorizontalMerge(occ_str, attacks_str, gap), gap), gap) << std::endl << std::endl;
            // std::this_thread::sleep_for(sleep_time);
        } while(occ = (occ - mask) & mask);
    }

    return 0;
}
