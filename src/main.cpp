#include <assert.h>

#include <iostream>

#include <cohen/chess.hpp>

using namespace cohen;
using namespace cohen::chess;
using namespace cohen::chess::magics;

#include <stack>

void test()
{
    std::stack<std::tuple<int, int, int>> stack({{1, 2, 3}});
}

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
        // assert_magic(sq, MagicBishopMask(sq), RayBishopAttacks, FancyMagicBishopAttacks);
        // assert_magic(sq, MagicBishopMask(sq), RayBishopAttacks, BlackMagicBishopAttacks);
        // assert_magic(sq, MagicBishopMask(sq), RayBishopAttacks, FancyByteMagicBishopAttacks);
        assert_magic(sq, MagicBishopMask(sq), RayBishopAttacks, BlackByteMagicBishopAttacks);
        // assert_magic(sq, MagicRookMask(sq),   RayRookAttacks,   FancyMagicRookAttacks);
        // assert_magic(sq, MagicRookMask(sq),   RayRookAttacks,   BlackMagicRookAttacks);
        // assert_magic(sq, MagicRookMask(sq),   RayRookAttacks,   FancyByteMagicRookAttacks);
        assert_magic(sq, MagicRookMask(sq),   RayRookAttacks,   BlackByteMagicRookAttacks);
    }
}

int main(int argc, char* argv[])
{
    TestMagics();

    std::size_t magic_size = 0;
    magic_size += sizeof(magics::kByteMagicBishopAttackTable);
    magic_size += sizeof(magics::kByteMagicBishopPointerTable);
    magic_size += sizeof(magics::kByteMagicRookAttackTable);
    magic_size += sizeof(magics::kByteMagicRookPointerTable);
    magic_size += sizeof(magics::kFancyMagicBishopTable);
    magic_size += sizeof(magics::kFancyMagicRookTable);
    magic_size += sizeof(magics::kFancyMagicAttackTable);
    magic_size += sizeof(magics::kFancyMagicOffsetTable);
    magic_size += sizeof(magics::kBlackMagicBishopTable);
    magic_size += sizeof(magics::kBlackMagicRookTable);
    magic_size += sizeof(magics::kBlackMagicAttackTable);
    magic_size += sizeof(magics::kBlackMagicOffsetTable);

    std::size_t fancy_magic_size = 0;
    fancy_magic_size += sizeof(magics::kFancyMagicBishopTable);
    fancy_magic_size += sizeof(magics::kFancyMagicRookTable);
    fancy_magic_size += sizeof(magics::kFancyMagicAttackTable);

    std::size_t fancy_byte_magic_size = 0;
    fancy_byte_magic_size += sizeof(magics::kByteMagicBishopAttackTable);
    fancy_byte_magic_size += sizeof(magics::kByteMagicBishopPointerTable);
    fancy_byte_magic_size += sizeof(magics::kFancyMagicBishopTable);
    fancy_byte_magic_size += sizeof(magics::kByteMagicRookAttackTable);
    fancy_byte_magic_size += sizeof(magics::kByteMagicRookPointerTable);
    fancy_byte_magic_size += sizeof(magics::kFancyMagicRookTable);
    fancy_byte_magic_size += sizeof(magics::kFancyMagicOffsetTable);

    std::size_t black_magic_size = 0;
    black_magic_size += sizeof(magics::kBlackMagicBishopTable);
    black_magic_size += sizeof(magics::kBlackMagicRookTable);
    black_magic_size += sizeof(magics::kBlackMagicAttackTable);

    std::size_t black_byte_magic_size = 0;
    black_byte_magic_size += sizeof(magics::kByteMagicBishopAttackTable);
    black_byte_magic_size += sizeof(magics::kByteMagicBishopPointerTable);
    black_byte_magic_size += sizeof(magics::kBlackMagicBishopTable);
    black_byte_magic_size += sizeof(magics::kByteMagicRookAttackTable);
    black_byte_magic_size += sizeof(magics::kByteMagicRookPointerTable);
    black_byte_magic_size += sizeof(magics::kBlackMagicRookTable);
    black_byte_magic_size += sizeof(magics::kBlackMagicOffsetTable);

    auto kb = [](std::size_t bytes) -> std::string
    {
        return std::to_string(bytes / 1000.0) + std::string{"KB"};
    };

    std::cout << "magic_size            = " << kb(magic_size)            << '\n';
    std::cout << "fancy_magic_size      = " << kb(fancy_magic_size)      << '\n';
    std::cout << "fancy_byte_magic_size = " << kb(fancy_byte_magic_size) << '\n';
    std::cout << "black_magic_size      = " << kb(black_magic_size)      << '\n';
    std::cout << "black_byte_magic_size = " << kb(black_byte_magic_size) << '\n';
    std::cout << "Hello, World!" << '\n';

    return 0;
}
