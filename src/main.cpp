#include <cassert>
#include <iostream>

#include <cohen/chess.hpp>

using namespace cohen;
using namespace cohen::chess;
using namespace cohen::chess::magics;

void TestMagics()
{
    constexpr auto assert_magic = [](Square sq, Bitboard mask,
                                     Functor<Bitboard(Square, Bitboard)> auto&& control,
                                     Functor<Bitboard(Square, Bitboard)> auto&& testing) -> void
    {
        Bitboard occ = kEmptyBB;
        do
        {
            assert(testing(sq, occ) == control(sq, occ));
        }
        while ((occ = CarryRipple(occ, mask)));
    };
    for (Square sq = kA1; sq < kSquareNB; ++sq)
    {
        std::cout << "FancyMagicBishohpAttacks" << '\n';     assert_magic(sq, MagicBishopMask(sq), RayBishopAttacks, FancyMagicBishopAttacks);
        std::cout << "BlackMagicBishohpAttacks" << '\n';     assert_magic(sq, MagicBishopMask(sq), RayBishopAttacks, BlackMagicBishopAttacks);
        std::cout << "FancyByteMagicBishohpAttacks" << '\n'; assert_magic(sq, MagicBishopMask(sq), RayBishopAttacks, FancyByteMagicBishopAttacks);
        std::cout << "BlackByteMagicBishohpAttacks" << '\n'; assert_magic(sq, MagicBishopMask(sq), RayBishopAttacks, BlackByteMagicBishopAttacks);
        std::cout << "FancyMagicRookAttacks" << '\n';        assert_magic(sq, MagicRookMask(sq),   RayRookAttacks,   FancyMagicRookAttacks);
        std::cout << "BlackMagicRookAttacks" << '\n';        assert_magic(sq, MagicRookMask(sq),   RayRookAttacks,   BlackMagicRookAttacks);
        std::cout << "FancyByteMagicRookAttacks" << '\n';    assert_magic(sq, MagicRookMask(sq),   RayRookAttacks,   FancyByteMagicRookAttacks);
        std::cout << "BlackByteMagicRookAttacks" << '\n';    assert_magic(sq, MagicRookMask(sq),   RayRookAttacks,   BlackByteMagicRookAttacks);
    }
}

int main(int argc, char* argv[])
{
    TestMagics();
    return 0;
}
