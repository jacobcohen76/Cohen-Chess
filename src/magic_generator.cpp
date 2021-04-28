#include "cohen_chess.h"

#include <bit>
#include <functional>
#include <limits>
#include <random>

using namespace cohen_chess;

size_t EvaluateMagic(std::function<Bitboard(Bitboard)> attack_generator, Magic m)
{
    std::array<Bitboard, 8196> attack_table = {};
    Key min_key = std::numeric_limits<Key>::max(), max_key = std::numeric_limits<Key>::min();
    Bitboard occ = kEmptyBB;
    do
    {
        Bitboard attacks = attack_generator(occ);
        Key key = m.key(occ);
        min_key = std::min(min_key, key);
        max_key = std::max(max_key, key);
        if (attack_table[key] && attack_table[key] != attacks)
        {
            return 0;
        }
        attack_table[key] = attacks;
    }
    while ((occ = (occ - m.mask) & m.mask));
    return max_key - min_key + 1;
}

Bitboard GenerateMagic(std::function<Bitboard()> randomizer, std::function<Bitboard(Bitboard)> attack_generator, Bitboard mask, size_t num_iterations)
{
    Magic m = {};
    m.mask  = mask;
    m.shift = 64 - std::popcount(mask);
    if (num_iterations)
    {
        Bitboard best_magic = kEmptyBB;
        size_t min_magic_size = std::numeric_limits<size_t>::max(), magic_size;
        for (size_t i = 0; i < num_iterations; ++i)
        {
            m.magic = randomizer();
            magic_size = EvaluateMagic(attack_generator, m);
            if (magic_size && magic_size < min_magic_size)
            {
                best_magic = m.magic;
                min_magic_size = magic_size;
            }
        }
        return best_magic;
    }
    else
    {
        do
        {
            m.magic = randomizer();
        }
        while (!EvaluateMagic(attack_generator, m));
        return m.magic;
    }
}

int main(int argc, char* argv[])
{
    Square sq = kA1;
    auto rng  = std::random_device();
    auto dist = std::uniform_int_distribution<Bitboard>();
    auto randomizer = [&]()
    {
        return dist(rng) & dist(rng);
    };
    auto attack_generator = std::bind(MagicRookAttacks, std::placeholders::_1, sq);
    Bitboard mask = MagicRookMask(sq);
    size_t num_iterations = 1000000;
    Bitboard magic = GenerateMagic(randomizer, attack_generator, mask, num_iterations);
    std::cout << "0x" << HexString(magic) << std::endl;
    return 0;
}