#include <iostream>
#include <map>

#include <cohen/chess.hpp>

int main(int argc, char* argv[])
{
    using namespace cohen;
    using namespace cohen::chess;
    using namespace cohen::chess::magic;
    Square sq = kA1; auto magic = kBlackMagicBishopTable[sq]; magic.position = 0;
    Bitboard mask = MagicBishopMask(sq);
    Bitboard  occ = kEmptyBB;
    std::map<int, Key> map;
    do
    {
        if (occ)
        {
            if (map.find(BitScanForward(occ)) != map.end())
            {
                assert(map[BitScanForward(occ)] == magic.key(occ));
            }
            map[BitScanForward(occ)] = magic.key(occ);
        }
    }
    while ((occ = (occ - mask) & mask));
}