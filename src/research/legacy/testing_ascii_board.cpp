#include "ascii_board.h"

#include <iostream>

int main(int argc, char* argv[])
{
    using namespace cohen_chess;
    std::cout << ascii_board::EmptyAsciiBoard('.') << std::endl;
    std::cout << ascii_board::EmptyAsciiBoard<ascii_board::kFileNorth | ascii_board::kFileSouth | ascii_board::kRankEast | ascii_board::kRankWest>('.') << std::endl;
    return 0;
}