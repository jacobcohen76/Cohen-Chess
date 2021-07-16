// #include <cassert>
// #include <iostream>

// #include <cohen/chess.hpp>

// void Init()
// {
//     std::ios::sync_with_stdio(false);
//     std::cin.tie(nullptr); std::cout.tie(nullptr);
// }

// int main(int argc, char* argv[])
// {
//     Init();
//     for (int i = 2; i < argc; ++i)
//     {
//         cohen::chess::Board board = {};
//         int repeat = std::stoi(argv[1]);
//         for (int j = 0; j < repeat; ++j)
//         {
//             cohen::chess::SetFenPosition(argv[i], board);
//             assert(argv[i] == cohen::chess::FormatFenPosition(board));
//         }
//     }
//     return 0;
// }

#include <cassert>

#include <cohen/chess.hpp>
#include <cohen/util.hpp>

using namespace cohen;
using namespace cohen::chess;

void Init()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
}

int main(int argc, char* argv[])
{
    Init();
    auto assert_magic = [](Functor<Bitboard(Bitboard, Square)> auto control,
                           Functor<Bitboard(Bitboard, Square)> auto testing,
                           Bitboard mask, Square sq)
        -> void
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
    return 0;
}
