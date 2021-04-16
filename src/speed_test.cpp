#include "types.h"

#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>

using namespace cohen_chess;

void run_test(size_t no_iterations)
{
    std::cout << "Running Array Test:     no_iterations=" << no_iterations << std::endl;
    std::chrono::steady_clock::time_point start, end;
    std::chrono::duration<double> elapsed_seconds;
    std::default_random_engine generator;
    std::uniform_int_distribution distribution(0, 63);

    start = std::chrono::steady_clock::now();
    for (size_t i = 0; i < no_iterations; ++i)
    {
        Bitboard bb = LookupSquareBB(Square(distribution(generator)));
    }
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "LookupSquareBB:         elapsed_seconds=" << elapsed_seconds.count() << "s" << std::endl;

    start = std::chrono::steady_clock::now();
    for (size_t i = 0; i < no_iterations; ++i)
    {
        Bitboard bb = ComputeSquareBB(Square(distribution(generator)));
    }
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "ComputeSquareBB:        elapsed_seconds=" << elapsed_seconds.count() << "s" << std::endl;
}


int main(int argc, char* argv[])
{
    for (size_t i = 1; i < argc; ++i)
    {
        run_test(std::stoull(argv[i]));
    }
    return 0;
}