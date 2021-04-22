#include "cohen_chess.h"

#include <chrono>
#include <functional>
#include <iostream>
#include <random>

using namespace cohen_chess;

template <typename clock = std::chrono::high_resolution_clock>
inline auto TimeTest(auto process)
{
    auto begin = clock::now();
    process();
    auto cease = clock::now();
    return cease - begin;
}

void LongProcess()
{
    for (size_t i = 0; i < 100000; ++i)
    {
        for (size_t j = 0; j < i; ++ j)
        {

        }
    }
}

int main(int argc, char* argv[])
{
    size_t num_iterations = 10000000000;

    auto random_bb = []()
    {
        static auto rd = std::default_random_engine();
        static auto dist = std::uniform_int_distribution<Bitboard>();
        return Bitboard(rand());
    };

    auto random_sq = []()
    {
        static auto rd = std::default_random_engine();
        static auto dist = std::uniform_int_distribution<Square>(0, 63);
        return Square(rand() & 0x3F);
    };

    auto repeat_process = [&](std::function<Bitboard(Bitboard, Square)> process)
    {
        for (size_t i = 0; i < num_iterations; ++i)
        {
            process(random_bb(), random_sq());
        }
    };

    
    std::chrono::duration<double> duration;

    auto begin = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < num_iterations; ++i)
    {
        random_bb();
        random_sq();
    }
    auto cease = std::chrono::high_resolution_clock::now();
    duration = cease - begin;
    std::cout << duration.count() << "s" << std::endl;

    duration = TimeTest<std::chrono::high_resolution_clock>(std::bind(repeat_process, RayBishopAttacks));
    std::cout << "RayBishopAttacks:        " << duration.count() << "s" << std::endl;

    duration = TimeTest<std::chrono::high_resolution_clock>(std::bind(repeat_process, RayRookAttacks));
    std::cout << "RayRookAttacks:          " << duration.count() << "s" << std::endl;

    duration = TimeTest<std::chrono::high_resolution_clock>(std::bind(repeat_process, RayQueenAttacks));
    std::cout << "RayQueenAttacks:         " << duration.count() << "s" << std::endl;

    duration = TimeTest<std::chrono::high_resolution_clock>(std::bind(repeat_process, MagicBishopAttacks));
    std::cout << "FancyMagicBishopAttacks: " << duration.count() << "s" << std::endl;

    duration = TimeTest<std::chrono::high_resolution_clock>(std::bind(repeat_process, MagicRookAttacks));
    std::cout << "FancyMagicRookAttacks:   " << duration.count() << "s" << std::endl;

    duration = TimeTest<std::chrono::high_resolution_clock>(std::bind(repeat_process, MagicQueenAttacks));
    std::cout << "FancyMagicQueenAttacks:  " << duration.count() << "s" << std::endl;

    return 0;
}