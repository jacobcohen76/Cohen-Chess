#include "../cohen_chess.h"

#include <iostream>
#include <random>
#include <set>

using namespace cohen_chess;

struct FancyMagic
{
    Bitboard*   attacks;
    Bitboard    magic;
    Bitboard    mask;
    int         shift;

    inline size_t index(Bitboard occ)
    {
        return (occ & mask) * magic >> shift;
    }

    inline Bitboard attackable(Bitboard occ)
    {
        return attacks[index(occ)];
    }
};

Bitboard kBishopAttackTable[32768];
Bitboard kRookAttackTable[262144];

FancyMagic kBishopTable[kSquareNB];
FancyMagic kRookTable[kSquareNB];

void InitBishopTable(FancyMagic bishop_table[kSquareNB], Bitboard magics[kSquareNB], Bitboard* attack_table)
{
    size_t max_index = -1, occ_index;
    for (Square sq = kA1; sq < kSquareNB; ++sq)
    {
        FancyMagic& fm = bishop_table[sq];
        fm.attacks  = attack_table + ++max_index;
        fm.magic    = magics[sq];
        fm.mask     = BishopMask(sq);
        fm.shift    = kSquareNB - PopCount(fm.mask);

        Bitboard occ = kEmptyBB;
        do
        {
            occ_index = fm.index(occ);
            std::cout << occ_index << std::endl;
            fm.attacks[occ_index] = RayBishopAttacks(occ, sq);
            if (occ_index > max_index)
                max_index = occ_index;
        }
        while(occ = (occ - fm.mask) & fm.mask);
        break;
    }
}

void InitRookTable(FancyMagic rook_table[kSquareNB], Bitboard magics[kSquareNB], Bitboard* attack_table)
{
    size_t max_index = -1, occ_index;
    for (Square sq = kA1; sq < kSquareNB; ++sq)
    {
        FancyMagic& fm = rook_table[sq];
        fm.attacks  = attack_table + ++max_index;
        fm.magic    = magics[sq];
        fm.mask     = RookMask(sq);
        fm.shift    = kSquareNB - PopCount(fm.mask);

        Bitboard occ = kEmptyBB;
        do
        {
            occ_index = fm.index(occ);
            fm.attacks[occ_index] = RayRookAttacks(occ, sq);
            if (occ_index > max_index)
                max_index = occ_index;
        }
        while (occ = (occ - fm.mask) & fm.mask);
    }
}

template <typename Generator, typename Distribution>
Bitboard FindBishopMagic(Generator gen, Distribution distr, Square sq)
{
    FancyMagic fm;
    fm.attacks  = new Bitboard[512];
    fm.mask     = BishopMask(sq);
    fm.shift    = kSquareNB - PopCount(fm.mask);

    std::set<Bitboard> visited;
    size_t max_index, occ_index;
    bool overwrite;
    do
    {
        fm.magic = distr(gen);
        max_index = 0;
        overwrite = false;
        visited.clear();

        Bitboard occ = kEmptyBB, ray_attacks;
        do
        {
            occ_index = fm.index(occ);
            ray_attacks = RayRookAttacks(occ, sq);
            overwrite = visited.contains(occ_index) && fm.attacks[occ_index] != ray_attacks;
            fm.attacks[occ_index] = ray_attacks;
            visited.insert(occ_index);
            if (occ_index > max_index)
                max_index = occ_index;
        }
        while ((occ = (occ - fm.mask) & fm.mask) && !overwrite);

        std::cout << "fm.magic =" << fm.magic << std::endl;
        std::cout << "max_index=" << max_index << std::endl;
        std::cout << "overwrite=" << overwrite << std::endl;
        std::cout << std::endl;
    }
    while (max_index > 256 || overwrite);

    return fm.magic;
}

size_t BishopMagicSize(Bitboard magic, Square sq)
{
    FancyMagic fm;
    fm.magic = magic;
    fm.mask = BishopMask(sq);
    fm.shift = kSquareNB - PopCount(fm.mask);

    size_t max_index = 0, occ_index;
    Bitboard occ = kEmptyBB;
    do
    {
        occ_index = fm.index(occ);
        if (occ_index > max_index)
            max_index = occ_index;
    }
    while (occ = (occ - fm.mask) & fm.mask);
    
    return max_index;
}

Bitboard BishopAttacks(Bitboard occ, Square sq)
{
    return kBishopTable[sq].attackable(occ);
}

int main(int argc, char* argv[])
{
    // std::cout << BishopMagicSize(0x7c0c028f5b34ff76, kG3) << std::endl;

    Square sq = kA1;
    size_t no_iterations = 100000000;

    // std::default_random_engine gen;
    // std::uniform_int_distribution<Bitboard> dist;

    // Bitboard min_magic = 0;
    // size_t min_magic_size = -1;
    // for (size_t i = 0; i < no_iterations; ++i)
    // {
    //     Bitboard magic = dist(gen);
    //     size_t magic_size = BishopMagicSize(magic, sq);
    //     if (magic_size < min_magic_size)
    //     {
    //         min_magic = magic;
    //         min_magic_size = magic_size;
    //     }
    // }
    // std::cout << "    min_magic=" << HexString(min_magic) << std::endl;
    // std::cout << "min_magic_size=" << min_magic_size << std::endl;



    // std::default_random_engine gen;
    // std::uniform_int_distribution<Bitboard> distr;
    // for (Square sq = kA1; sq < kSquareNB; ++sq)
    // {
    //     Bitboard magic = FindBishopMagic(gen, distr, sq);
    //     std::cout << HexString(magic) << std::endl;
    // }

    Bitboard magics[kSquareNB] =
    {
        0xED82C04010301842,
    };
    InitBishopTable(kBishopTable, magics, kBishopAttackTable);
    Bitboard occ = 0;
    Bitboard mask = kBishopTable[kA1].mask;
    do
    {
        std::cout << util::HorizontalMerge(io::AsciiBoard(occ), io::AsciiBoard(BishopAttacks(occ, kA1)), "   ") << std::endl << std::endl;
    }
    while(occ = (occ - mask) & mask);
    return 0;
}