#include <cohen_chess.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <locale>

using namespace cohen_chess;

int main(int argc, char* argv[])
{
    const auto lambda = [](auto mask_generator, auto attacks_generator, auto alt_attacks_generator)
    {
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            Bitboard mask = mask_generator(sq);
            Bitboard occ  = kEmptyBB;
            do
            {
                assert(attacks_generator(occ, sq) == alt_attacks_generator(occ, sq));
                // std::cout << AsciiBoard(occ) << std::endl;
                // std::cout << AsciiBoard(attacks_generator(occ, sq)) << std::endl;
                // std::cout << AsciiBoard(alt_attacks_generator(occ, sq)) << std::endl << std::endl;
            }
            while ((occ = (occ - mask) & mask));
        }
    };
    lambda(MagicBishopMask, MagicBishopAttacks, RayBishopAttacks);
    lambda(MagicRookMask, MagicRookAttacks, RayRookAttacks);
    std::cout << "Success!" << std::endl;
    return 0;
}
