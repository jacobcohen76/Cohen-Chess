#include <iostream>

#include <cohen/chess.hpp>

void Init()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
}

int main(int argc, char* argv[])
{
    Init();
    using namespace cohen::chess;
    auto lambda = [](auto& ascii_board, auto attr, auto char_set)
    {
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            ascii_board.set(sq, char_set[attr(sq)]);
        }
    };
    AsciiBoard rank_board, file_board, diag_board, anti_board;
    lambda(rank_board, RankOf, "12345678");
    lambda(file_board, FileOf, "ABCDEFGH");
    lambda(diag_board, DiagOf, "123456789ABCDEF");
    lambda(anti_board, AntiOf, "123456789ABCDEF");
    std::cout << "rank_board:" << std::endl << rank_board << std::endl;
    std::cout << "file_board:" << std::endl << file_board << std::endl;
    std::cout << "diag_board:" << std::endl << diag_board << std::endl;
    std::cout << "anti_board:" << std::endl << anti_board << std::endl;

    using namespace cohen::chess::magic;
    for (Square sq = kA1; sq < kSquareNB; ++sq)
    {
        Bitboard mask = MagicBishopMask(sq);
        Bitboard  occ = kEmptyBB;
        do
        {
            assert(RayBishopAttacks(occ, sq) == FancyMagicBishopAttacks(occ, sq));
            assert(RayBishopAttacks(occ, sq) == BlackMagicBishopAttacks(occ, sq));
        }
        while((occ = (occ - mask) & mask));
    }
    for (Square sq = kA1; sq < kSquareNB; ++sq)
    {
        Bitboard mask = MagicRookMask(sq);
        Bitboard  occ = kEmptyBB;
        do
        {
            assert(RayRookAttacks(occ, sq) == FancyMagicRookAttacks(occ, sq));
            assert(RayRookAttacks(occ, sq) == BlackMagicRookAttacks(occ, sq));
        }
        while((occ = (occ - mask) & mask));
    }
    std::cout << "FancyMagic: " << kFancyMagicBishopAttackTable.size() + kFancyMagicRookAttackTable.size() << std::endl;
    std::cout << "BlackMagic: " << kBlackMagicBishopAttackTable.size() + kBlackMagicRookAttackTable.size() << std::endl;
    return 0;
}
