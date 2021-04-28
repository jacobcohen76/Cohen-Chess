#include "cohen_chess.h"

#include <iostream>

void TestMagicBishopAttacks()
{
    using namespace cohen_chess;

    for (Square sq = kA1; sq < kSquareNB; ++sq)
    {
        std::cout << "Square " << CoordinateString(sq) << ":" << std::endl << std::endl;
        Bitboard mask = MagicBishopMask(sq);
        Bitboard occ = kEmptyBB;
        do
        {
            Bitboard ray_attacks = RayBishopAttacks(occ, sq);
            Bitboard magic_attacks = MagicBishopAttacks(occ, sq);
            std::string ascii_board_occ         = "occ:\n"           + AsciiBoard(occ, '1').to_string();
            std::string ascii_board_ray         = "ray_attacks:\n"   + AsciiBoard(ray_attacks, '1').to_string();
            std::string ascii_board_magic = "magic_attacks:\n" + AsciiBoard(magic_attacks, '1').to_string();
            std::string gap = "   ";
            std::string merged;
            merged = util::HorizontalMerge(ascii_board_magic, ascii_board_ray, gap);
            merged = util::HorizontalMerge(ascii_board_occ, merged, gap);
            std::cout << merged << std::endl << std::endl;
            if (ray_attacks != magic_attacks)
            {
                std::cout << "ERROR!!!" << std::endl;
                exit(1);
            }
        }
        while ((occ = (occ - mask) & mask));
    }
}

void TestMagicRookAttacks()
{
    using namespace cohen_chess;

    for (Square sq = kA1; sq < kSquareNB; ++sq)
    {
        std::cout << "Square " << CoordinateString(sq) << ":" << std::endl << std::endl;
        Bitboard mask = MagicRookMask(sq);
        Bitboard occ = kEmptyBB;
        do
        {
            Bitboard ray_attacks = RayRookAttacks(occ, sq);
            Bitboard magic_attacks = MagicRookAttacks(occ, sq);
            std::string ascii_board_occ         = "occ:\n"           + AsciiBoard(occ, '1').to_string();
            std::string ascii_board_ray         = "ray_attacks:\n"   + AsciiBoard(ray_attacks, '1').to_string();
            std::string ascii_board_magic = "magic_attacks:\n" + AsciiBoard(magic_attacks, '1').to_string();
            std::string gap = "   ";
            std::string merged;
            merged = util::HorizontalMerge(ascii_board_magic, ascii_board_ray, gap);
            merged = util::HorizontalMerge(ascii_board_occ, merged, gap);
            std::cout << merged << std::endl << std::endl;
            if (ray_attacks != magic_attacks)
            {
                std::cout << "ERROR!!!" << std::endl;
                exit(1);
            }
        }
        while ((occ = (occ - mask) & mask));
    }
}

int main(int argc, char* argv[])
{
    TestMagicBishopAttacks();
    TestMagicRookAttacks();
    std::cout << "SUCCESS!!!" << std::endl;

    // Bitboard occ = 0xAB83EF87C7123;
    // std::cout << "occ:" << std::endl;
    // std::cout << io::AsciiBoard(occ) << std::endl << std::endl;

    // std::cout << "RayBishopAttacks:" << std::endl;
    // std::cout << io::AsciiBoard(RayBishopAttacks(occ, kD5)) << std::endl << std::endl;
    // cohen_chess::LookupSquareBB(kA2);

    // std::cout << io::AsciiBoard(0x7f7f7f7f7f7f7f7f) << std::endl << std::endl;

    return 0;
}
