#include <random>

#include <cohen/chess.hpp>
#include <cohen/util.hpp>

using namespace cohen;
using namespace cohen::chess;
using namespace cohen::chess::magic;

bool ValidMagic(Magic auto magic, auto attacks_fn, Bitboard mask, Key min_key)
{
    std::array<Bitboard, 100000> hash_table = {};
    Bitboard occ = kEmptyBB;
    do
    {
        Key key = magic.key(occ) - min_key;
        Bitboard attacks = attacks_fn(occ);
        if (hash_table[key] && hash_table[key] != attacks)
        {
            return false;
        }
        hash_table[key] = attacks;
    }
    while ((occ = (occ - mask) & mask));
    return true;
}

Bitboard GenerateMagic(Magic auto m, auto attacks_fn, auto rand_fn, Bitboard mask)
{
    Key min_width = kKeyAll;
    Bitboard best_magic = kEmptyBB;
    for (int i = 0; i < 1000000; ++i)
    {
        m.magic = rand_fn();
        auto [min_key, max_key] = MagicKeyRange(m, mask);
        auto magic_width = max_key - min_key + 1;
        if (ValidMagic(m, attacks_fn, mask, min_key) && magic_width < min_width)
        {
            best_magic = m.magic;
            min_width  = magic_width;
        }
    }
    return best_magic;
}

int main(int argc, char* argv[])
{
    std::random_device rd;
    std::mt19937 engine(rd());
    auto rand_fn = [&engine]()
    {
        uint64_t x = engine() & engine() & engine();
        x <<= 32;
        x |= engine() & engine() & engine();
        return x;
    };

    Square sq = kA1;
    auto attacks_fn = [sq](Bitboard occ) { return FancyMagicBishopAttacks(occ, sq); };
    Bitboard mask = MagicBishopMask(sq);
    BishopBlackMagic bm = {};
    bm.not_mask = ~MagicBishopMask(sq);
    bm.magic    =  GenerateMagic(bm, attacks_fn, rand_fn, mask);
    std::cout << bm.magic << ",width=" << MagicWidth(bm, mask) <<  std::endl;
    bm.magic = 0x107AC08050500BFF;
    std::cout << "control=" << MagicWidth(bm, mask) << std::endl;
}
