#include <iostream>

#include <cohen_chess.hpp>

using namespace cohen_chess;

void Init()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

int main(int argc, char* argv[])
{
    Init();

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

    return 0;
}
