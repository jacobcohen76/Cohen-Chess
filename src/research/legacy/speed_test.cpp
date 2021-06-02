#include <array>
#include <chrono>
#include <cstdint>
#include <iostream>

typedef uint64_t Bitboard;

enum Anti : int8_t
{
    kAnti1  =  0,
    kAnti2  =  1,
    kAnti3  =  2,
    kAnti4  =  3,
    kAnti5  =  4,
    kAnti6  =  5,
    kAnti7  =  6,
    kAnti8  =  7,
    kAnti9  =  8,
    kAntiA  =  9,
    kAntiB  = 10,
    kAntiC  = 11,
    kAntiD  = 12,
    kAntiE  = 13,
    kAntiF  = 14,
    kAntiNB = 15,
};

constexpr Bitboard AntiBB_Array_Constexpr(Anti anti)
{
    constexpr std::array<Bitboard, kAntiNB> kAntiBitboards =
    {
        0x0000000000000001,
        0x0000000000000102,
        0x0000000000010204,
        0x0000000001020408,
        0x0000000102040810,
        0x0000010204081020,
        0x0001020408102040,
        0x0102040810204080,
        0x0204081020408000,
        0x0408102040800000,
        0x0810204080000000,
        0x1020408000000000,
        0x2040800000000000,
        0x4080000000000000,
        0x8000000000000000,
    };
    return kAntiBitboards[anti];
}

constexpr Bitboard AntiBB_Constexpr(Anti anti)
{
    return (Bitboard[kAntiNB])
    {
        0x0000000000000001,
        0x0000000000000102,
        0x0000000000010204,
        0x0000000001020408,
        0x0000000102040810,
        0x0000010204081020,
        0x0001020408102040,
        0x0102040810204080,
        0x0204081020408000,
        0x0408102040800000,
        0x0810204080000000,
        0x1020408000000000,
        0x2040800000000000,
        0x4080000000000000,
        0x8000000000000000,
    }[anti];
}

inline Bitboard AntiBB_Inline(Anti anti)
{
    static const Bitboard kAntiBitboards[kAntiNB]
    {
        0x0000000000000001,
        0x0000000000000102,
        0x0000000000010204,
        0x0000000001020408,
        0x0000000102040810,
        0x0000010204081020,
        0x0001020408102040,
        0x0102040810204080,
        0x0204081020408000,
        0x0408102040800000,
        0x0810204080000000,
        0x1020408000000000,
        0x2040800000000000,
        0x4080000000000000,
        0x8000000000000000,
    };
    return kAntiBitboards[anti];
}

Bitboard AntiBB_Function(Anti anti)
{
    static const Bitboard kAntiBitboards[kAntiNB]
    {
        0x0000000000000001,
        0x0000000000000102,
        0x0000000000010204,
        0x0000000001020408,
        0x0000000102040810,
        0x0000010204081020,
        0x0001020408102040,
        0x0102040810204080,
        0x0204081020408000,
        0x0408102040800000,
        0x0810204080000000,
        0x1020408000000000,
        0x2040800000000000,
        0x4080000000000000,
        0x8000000000000000,
    };
    return kAntiBitboards[anti];
}

void run_test(size_t no_iterations)
{
    std::cout << "Running Array Test:     no_iterations=" << no_iterations << std::endl;
    std::chrono::steady_clock::time_point start, end;
    std::chrono::duration<double> elapsed_seconds;

    start = std::chrono::steady_clock::now();
    for (size_t i = 0; i < no_iterations; ++i)
    {
        Bitboard bb = AntiBB_Array_Constexpr(Anti(i % kAntiNB));
    }
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "AntiBB_Array_Constexpr: elapsed_seconds=" << elapsed_seconds.count() << "s" << std::endl;

    start = std::chrono::steady_clock::now();
    for (size_t i = 0; i < no_iterations; ++i)
    {
        Bitboard bb = AntiBB_Constexpr(Anti(i % kAntiNB));
    }
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "AntiBB_Constexpr:       elapsed_seconds=" << elapsed_seconds.count() << "s" << std::endl;

    start = std::chrono::steady_clock::now();
    for (size_t i = 0; i < no_iterations; ++i)
    {
        Bitboard bb = AntiBB_Inline(Anti(i % kAntiNB));
    }
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "AntiBB_Inline:          elapsed_seconds=" << elapsed_seconds.count() << "s" << std::endl;

    start = std::chrono::steady_clock::now();
    for (size_t i = 0; i < no_iterations; ++i)
    {
        Bitboard bb = AntiBB_Inline(Anti(i % kAntiNB));
    }
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "AntiBB_Function:        elapsed_seconds=" << elapsed_seconds.count() << "s" << std::endl;
    std::cout << std::endl;
}

int main(int argc, char* argv[])
{
    for (size_t i = 1; i < argc; ++i)
    {
        run_test(std::stoull(argv[i]));
    }
    return 0;
}
