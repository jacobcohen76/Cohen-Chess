#include "cohen_chess.h"

#include <iostream>

int main(int argc, char* argv[])
{
    using namespace cohen_chess;
    
    std::cout << io::AsciiBoard(RankBB(kRank1)) << std::endl << std::endl;
    std::cout << io::AsciiBoard(SquareBB(kB3)) << std::endl << std::endl;

    std::cout << io::AsciiBoard(LineBB(kB3, kE6)) << std::endl << std::endl;
    std::cout << io::AsciiBoard(BetweenBB(kB3, kE6)) << std::endl << std::endl;

    return 0;
}
