#include "cohen_chess.h"

#include <algorithm>
#include <functional>
#include <limits>
#include <random>
#include <iostream>

using namespace cohen_chess;

Bitboard random_device_uniform_int()
{
    static auto gen  = std::random_device();
    static auto dist = std::uniform_int_distribution<Bitboard>();
    return dist(gen);
}

auto randomizer = []()
{
    return random_device_uniform_int() & random_device_uniform_int();
};

Bitboard GenerateMagic(Magic m, std::function<Bitboard(Bitboard)> attack_generator, size_t num_iterations)
{
    static Bitboard attack_table[8196] = {};
    Bitboard best_magic = kEmptyBB;
    Key min_max_key = std::numeric_limits<Key>::max();
    for (size_t i = 0; i < num_iterations; ++i)
    {
        m.magic = randomizer();
        Key max_key = kKeyZero;
        Bitboard occ = kEmptyBB;
        bool is_valid_magic = true;
        do
        {
            Bitboard attacks = attack_generator(occ);
            Key key = m.key(occ);
            is_valid_magic = attack_table[key] == kEmptyBB || attack_table[key] == attacks;
            attack_table[key] = attacks;
            max_key = std::max(max_key, key);
        } while ((occ = (occ - m.mask) & m.mask) && is_valid_magic);
        if (is_valid_magic && max_key < min_max_key)
        {
            min_max_key = max_key;
            best_magic = m.magic;
        }
        std::fill(attack_table, attack_table + 8196, kEmptyBB);
    }
    return best_magic;
}

Bitboard GenerateMagic(Magic m, std::function<Bitboard(Bitboard)> attack_generator)
{
    static Bitboard attack_table[8196] = {};
    bool found_valid_magic = false;
    while (!found_valid_magic)
    {
        m.magic = randomizer();
        found_valid_magic = true;
        Bitboard occ = kEmptyBB;
        do
        {
            Bitboard attacks = attack_generator(occ);
            Key key = m.key(occ);
            if (key >= 8196 || (attack_table[key] != kEmptyBB && attack_table[key] != attacks))
            {
                std::cout << "key >= 8196 = " << (key >= 8196) << std::endl;
                std::cout << "attack_table[key] != kEmptyBB = " << (attack_table[key] != kEmptyBB) << std::endl;
                std::cout << "attack_table[key] != attacks  = " << (attack_table[key] != attacks)  << std::endl;
                std::cout << util::HorizontalMerge("occ:\n" + io::AsciiBoard(occ), util::HorizontalMerge("attacks:\n" + io::AsciiBoard(attacks), "attack_table[key]:\n" + io::AsciiBoard(attack_table[key]), "   "), "   ") << std::endl;
                std::cout << std::endl;
                found_valid_magic = false;
            }
            else
                attack_table[key] = attacks;
        } while ((occ = (occ - m.mask) & m.mask) && found_valid_magic);
        std::cout << "0x" << HexString(m.magic) << ", valid=" << found_valid_magic << std::endl;
        std::fill(attack_table, attack_table + 8196, kEmptyBB);
    }
    return m.magic;
}

template <PieceType pc_type>
Bitboard GenerateMagic(Square sq)
{
    static_assert(pc_type == kBishop || pc_type == kRook);
    if constexpr (pc_type == kBishop)
    {
        Magic m;
        m.begin     = 0;
        m.magic     = kEmptyBB;
        m.mask      = MagicBishopMask(sq);
        m.shift     = kSquareNB - PopCount(fm.mask);
        auto attack_generator = [&](Bitboard occ)
        {
            return FancyMagicBishopAttacks(occ, sq);
        };
        return GenerateMagic(m, attack_generator);
    }
    else
    {
        Magic m;
        m.begin     = 0;
        m.magic     = kEmptyBB;
        m.mask      = MagicRookMask(sq);
        m.shift     = kSquareNB - PopCount(fm.mask);
        auto attack_generator = [&](Bitboard occ)
        {
            return FancyMagicRookAttacks(occ, sq);
        };
        return GenerateMagic(m, attack_generator);
    }
}

template <PieceType pc_type>
Bitboard GenerateMagic(Square sq, size_t num_iterations)
{
    static_assert(pc_type == kBishop || pc_type == kRook);
    if constexpr (pc_type == kBishop)
    {
        Magic m;
        m.begin     = 0;
        m.magic     = kEmptyBB;
        m.mask      = MagicBishopMask(sq);
        m.shift     = kSquareNB - PopCount(fm.mask);
        auto attack_generator = [&](Bitboard occ)
        {
            return FancyMagicBishopAttacks(occ, sq);
        };
        return GenerateMagic(m, attack_generator, num_iterations);
    }
    else
    {
        Magic m;
        m.begin     = 0;
        m.magic     = kEmptyBB;
        m.mask      = MagicRookMask(sq);
        m.shift     = kSquareNB - PopCount(fm.mask);
        auto attack_generator = [&](Bitboard occ)
        {
            return FancyMagicRookAttacks(occ, sq);
        };
        return GenerateMagic(m, attack_generator, num_iterations);
    }
}

int main(int argc, char* argv[])
{
    std::cout << "Hello World!" << std::endl;
    Bitboard magic = GenerateMagic<kBishop>(kA1, 1000000);
    std::cout << "0x" << HexString(magic) << std::endl;
    return 0;
}