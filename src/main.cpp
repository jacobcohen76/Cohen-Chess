#include "cohen_chess.h"

#include <iostream>

void TestFancyBishopMagic()
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
            Bitboard magic_attacks = FancyMagicBishopAttacks(occ, sq);
            std::string ascii_board_occ         = "occ:\n"           + io::AsciiBoard(occ);
            std::string ascii_board_ray         = "ray_attacks:\n"   + io::AsciiBoard(ray_attacks);
            std::string ascii_board_fancy_magic = "magic_attacks:\n" + io::AsciiBoard(magic_attacks);
            std::string gap = "   ";
            std::string merged;
            merged = util::HorizontalMerge(ascii_board_fancy_magic, ascii_board_ray, gap);
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

void TestFancyRookMagic()
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
            Bitboard magic_attacks = FancyMagicRookAttacks(occ, sq);
            std::string ascii_board_occ         = "occ:\n"           + io::AsciiBoard(occ);
            std::string ascii_board_ray         = "ray_attacks:\n"   + io::AsciiBoard(ray_attacks);
            std::string ascii_board_fancy_magic = "magic_attacks:\n" + io::AsciiBoard(magic_attacks);
            std::string gap = "   ";
            std::string merged;
            merged = util::HorizontalMerge(ascii_board_fancy_magic, ascii_board_ray, gap);
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
    TestFancyBishopMagic();
    TestFancyRookMagic();
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
