#include <cassert>

#include <cohen/chess.hpp>

int main(int argc, char* argv[])
{
    using namespace cohen::chess;
    for (Square sq = kA1; sq < kSquareNB; ++sq)
    {
        assert(RayBishopAttacks(sq) == MagicBishopAttacks(sq));
        assert(RayRookAttacks  (sq) == MagicRookAttacks  (sq));
        assert(RayQueenAttacks (sq) == MagicQueenAttacks (sq));
    }
    return 0;
}
