#include "cohen_chess.h"

using namespace cohen_chess;

void GenerateSquareBitboards(std::string_view fn_name, std::function<Bitboard(Square)> fn)
{
    std::cout << fn_name << std::endl;
    for (Square sq = kA1; sq < kSquareNB; ++sq)
    {
        Bitboard bb = fn(sq);
        if (sq && FileOf(sq) == 0)
        {
            std::cout << std::endl;
        }
        std::cout << "0x" << HexString(bb) << ", ";
    }
    std::cout << std::endl << std::endl;
}

int main(int argc, char* argv[])
{
    GenerateSquareBitboards("MagicBishopMask",  MagicBishopMask);
    GenerateSquareBitboards("MagicRookMask",    MagicRookMask);
    return 0;
}