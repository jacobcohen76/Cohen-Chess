#include <cassert>
#include <iostream>

#include <cohen/chess.hpp>

using namespace cohen;
using namespace cohen::chess;
using namespace cohen::chess::magics;

void TestMagics()
{
    const auto assert_magic = [](Functor<Bitboard(Bitboard, Square)> auto&& control,
                                 Functor<Bitboard(Bitboard, Square)> auto&& testing,
                                 Bitboard mask, Square sq) -> void
    {
        Bitboard occ = kEmptyBB;
        do
        {
            assert(control(occ, sq) == testing(occ, sq));
        }
        while ((occ = (occ - mask) & mask));
    };
    for (Square sq = kA1; sq < kSquareNB; ++sq)
    {
        assert_magic(RayBishopAttacks, FancyMagicBishopAttacks, MagicBishopMask(sq), sq);
        assert_magic(RayBishopAttacks, BlackMagicBishopAttacks, MagicBishopMask(sq), sq);
        assert_magic(RayRookAttacks,   FancyMagicRookAttacks,   MagicRookMask(sq),   sq);
        assert_magic(RayRookAttacks,   BlackMagicRookAttacks,   MagicRookMask(sq),   sq);
    }
    std::cout << "kFancyMagicAttackTable.size() = " << kFancyMagicAttackTable.size() << std::endl;
    std::cout << "kBlackMagicAttackTable.size() = " << kBlackMagicAttackTable.size() << std::endl;
}

int main(int argc, char* argv[])
{
    TestMagics();
    std::cout << "kMagicRookAttackTable\n";
    for (Bitboard attacks : kMagicRookAttackTable)
    {
        std::cout << AsciiBoard(attacks) << '\n';
    }
    std::cout << "kMagicBishopAttackTable\n";
    for (Bitboard attacks : kMagicBishopAttackTable)
    {
        std::cout << AsciiBoard(attacks) << '\n';
    }
    return 0;
}
