#include "../cohen_chess.h"

#include <functional>
#include <iostream>
#include <map>
#include <limits>
#include <random>
#include <unordered_map>

using namespace cohen_chess;

template <typename Magic>
size_t EvaluateMagic(Magic m, std::function<Bitboard(Bitboard)> attack_generator)
{
    std::unordered_map<size_t, Bitboard> index_map;
    size_t max_index = 0, index;
    Bitboard occ = kEmptyBB, attacks;
    do
    {
        attacks = attack_generator(occ);
        index = m.key(occ);
        max_index = std::max(max_index, index);
        if (index_map.contains(index) && index_map[index] != attacks)
        {
            return 0;
        }
        index_map[index] = attacks;
    }
    while (occ = (occ - m.mask) & m.mask);
    return max_index;
}

template <typename Magic>
Bitboard GenerateMagic(Magic m, size_t num_iterations, std::function<Bitboard()> randomizer, std::function<Bitboard(Bitboard)> attack_generator)
{
    size_t min_index = std::numeric_limits<size_t>::max(), max_index;
    Bitboard best_magic = kEmptyBB;
    for (size_t i = 0; i < num_iterations; ++i)
    {
        m.magic = randomizer();
        max_index = EvaluateMagic(m, attack_generator);
        if (max_index && max_index < min_index)
        {
            min_index = max_index;
            best_magic = m.magic;
        }
    }
    return best_magic;
}

size_t EvaluateBishopFancyMagic(Bitboard magic, Square sq)
{
    FancyMagic fm;
    fm.begin    = 0;
    fm.magic    = magic;
    fm.mask     = MagicBishopMask(sq);
    fm.shift    = kSquareNB - PopCount(fm.mask);
    auto attack_generator = [sq](Bitboard occ)
    {
        return RayBishopAttacks(occ, sq);
    };
    return EvaluateMagic(fm, attack_generator);
}

size_t EvaluateRookFancyMagic(Bitboard magic, Square sq)
{
    FancyMagic fm;
    fm.begin    = 0;
    fm.magic    = magic;
    fm.mask     = MagicRookMask(sq);
    fm.shift    = kSquareNB - PopCount(fm.mask);
    auto attack_generator = [sq](Bitboard occ)
    {
        return RayRookAttacks(occ, sq);
    };
    return EvaluateMagic(fm, attack_generator);
}

Bitboard GenerateBishopFancyMagic(Square sq, size_t num_iterations, std::function<Bitboard()> randomizer)
{
    FancyMagic fm;
    fm.begin    = 0;
    fm.mask     = MagicBishopMask(sq);
    fm.shift    = kSquareNB - PopCount(fm.mask);
    auto attack_generator = [sq](Bitboard occ)
    {
        return RayBishopAttacks(occ, sq);
    };
    return GenerateMagic(fm, num_iterations, randomizer, attack_generator);
}

Bitboard GenerateRookFancyMagic(Square sq, size_t num_iterations, std::function<Bitboard()> randomizer)
{
    FancyMagic fm;
    fm.begin    = 0;
    fm.mask     = MagicRookMask(sq);
    fm.shift    = kSquareNB - PopCount(fm.mask);
    auto attack_generator = [sq](Bitboard occ)
    {
        return RayRookAttacks(occ, sq);
    };
    return GenerateMagic(fm, num_iterations, randomizer, attack_generator);
}

int main(int argc, char* argv[])
{
    std::random_device rd;
    std::uniform_int_distribution<Bitboard> dist;
    auto rng = std::bind(dist, std::ref(rd));
    auto randomizer = [&]()
    {
        return rng() & rng();
    };

    if (argc > 3)
    {
        Square sq = CoordinateToSquare(argv[2]);
        size_t num_iterations = std::stoull(argv[3]);

        if (std::string(argv[1]) == "bishop")
        {
            Bitboard magic = GenerateBishopFancyMagic(sq, num_iterations, randomizer);
            std::cout << "0x" << HexString(magic) << ", " << EvaluateBishopFancyMagic(magic, sq) << std::endl;
        }
        else if(std::string(argv[1]) == "rook")
        {
            Bitboard magic = GenerateRookFancyMagic(sq, num_iterations, randomizer);
            std::cout << "0x" << HexString(magic) << ", " << EvaluateRookFancyMagic(magic, sq) << std::endl;
        }
    }
    else if (argc > 2)
    {
        size_t num_iterations = std::stoull(argv[2]);

        if (std::string(argv[1]) == "bishop")
        {
            std::cout << "Bishop Fancy Magics:" << std::endl;
            for (Square sq = kA1; sq < kSquareNB; ++sq)
            {
                if (sq != kA1 && FileOf(sq) == kFileA)
                {
                    std::cout << std::endl;
                }
                Bitboard magic = GenerateBishopFancyMagic(sq, num_iterations, randomizer);
                std::cout << "0x" << HexString(magic) << ", ";
            }
            std::cout << std::endl << std::endl;
        }
        else if (std::string(argv[1]) == "rook")
        {
            std::cout << "Rook Fancy Magics:" << std::endl;
            for (Square sq = kA1; sq < kSquareNB; ++sq)
            {
                if (sq != kA1 && FileOf(sq) == kFileA)
                {
                    std::cout << std::endl;
                }
                Bitboard magic = GenerateRookFancyMagic(sq, num_iterations, randomizer);
                std::cout << "0x" << HexString(magic) << ", ";
            }
            std::cout << std::endl << std::endl;
        }
    }
    return 0;
}