#include <assert.h>

#include <iomanip>
#include <ios>
#include <iostream>

#include <cohen/chess.hpp>

using namespace cohen;
using namespace cohen::chess;
// using namespace cohen::chess::magics;

// void TestMagics()
// {
//     constexpr auto assert_magic = [](Square sq, Bitboard mask,
//                                      Functor<Bitboard(Square, Bitboard)> auto&& control,
//                                      Functor<Bitboard(Square, Bitboard)> auto&& testing) -> void
//     {
//         Bitboard occ = kEmptyBB;
//         do
//         {
//             assert(testing(sq, occ) == control(sq, occ));
//         }
//         while ((occ = CarryRipple(occ, mask)));
//     };
//     for (Square sq = kA1; sq < kSquareNB; ++sq)
//     {
//         assert_magic(sq, MagicBishopMask(sq), RayBishopAttacks, FancyMagicBishopAttacks);
//         assert_magic(sq, MagicBishopMask(sq), RayBishopAttacks, BlackMagicBishopAttacks);
//         assert_magic(sq, MagicBishopMask(sq), RayBishopAttacks, FancyByteMagicBishopAttacks);
//         assert_magic(sq, MagicBishopMask(sq), RayBishopAttacks, BlackByteMagicBishopAttacks);
//         assert_magic(sq, MagicRookMask(sq),   RayRookAttacks,   FancyMagicRookAttacks);
//         assert_magic(sq, MagicRookMask(sq),   RayRookAttacks,   BlackMagicRookAttacks);
//         assert_magic(sq, MagicRookMask(sq),   RayRookAttacks,   FancyByteMagicRookAttacks);
//         assert_magic(sq, MagicRookMask(sq),   RayRookAttacks,   BlackByteMagicRookAttacks);
//     }
// }

int main(int argc, char* argv[])
{
    // TestMagics();
    // std::cout << "Byte Bishop Offsets:" << '\n';
    // for (const Bitboard* ptr : magics::kByteMagicBishopPointerTable)
    // {
    //     const Key offset = ptr - std::begin(magics::kByteMagicBishopAttackTable);
    //     std::cout << "offset = " << offset << '\n';
    // }
    // std::cout << '\n';

    // std::cout << "Byte Rook Offsets:" << '\n';
    // for (const Bitboard* ptr : magics::kByteMagicRookPointerTable)
    // {
    //     const Key offset = ptr - std::begin(magics::kByteMagicRookAttackTable);
    //     std::cout << "offset = " << offset << '\n';
    // }
    // std::cout << '\n';
    std::cout << std::boolalpha;
    std::cout << "Attack Table:" << '\n';
    std::cout << "Fancy: " << (magics::kFancyMagicAttackTable == magic_bitboards::kFancyMagicAttackTable) << '\n';
    std::cout << "Black: " << (magics::kBlackMagicAttackTable == magic_bitboards::kBlackMagicAttackTable) << '\n';
    std::cout << '\n';

    std::cout << "Offset Table:" << '\n';
    std::cout << "Fancy: " << (magics::kFancyMagicOffsetTable == magic_bitboards::kFancyMagicOffsetTable) << '\n';
    std::cout << "Black: " << (magics::kBlackMagicOffsetTable == magic_bitboards::kBlackMagicOffsetTable) << '\n';
    std::cout << '\n';

    // std::cout << std::size(magics::k)

    return 0;
}
