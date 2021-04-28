#include "cohen_chess.h"

using namespace cohen_chess;

int main(int argc, char* argv[])
{
    for (Square sq = kA1; sq < kSquareNB; ++sq)
    {
        std::cout << "sq = " << int(sq) << std::endl;
        std::cout << io::AsciiBoard(SquareBB(sq)) << std::endl << std::endl;
    }
    return 0;
}
