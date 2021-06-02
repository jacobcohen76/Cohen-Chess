#include <bitset>
#include <concepts>
#include <cstdint>
#include <iostream>

template <std::integral T>
constexpr int DeBruijnBitScanForward(T x)
{
    constexpr uint64_t kDebruijnForward64 = 0;
    return 64;
}

int main(int argc, char* argv[])
{
    uint64_t x = 1488;
    std::cout << std::bitset<sizeof(x) * 8>(x) << ", (x)" << std::endl;
    std::cout << std::bitset<sizeof(x) * 8>(x & -x) << ", (x & -x)" << std::endl;
    std::cout << std::bitset<sizeof(x) * 8>(x ^ -x) << ", (x ^ -x)" << std::endl;
    std::cout << std::bitset<sizeof(x) * 8>(x & (x - 1)) << ", (x & (x - 1))" << std::endl;
    std::cout << std::bitset<sizeof(x) * 8>(x ^ (x - 1)) << ", (x ^ (x - 1))" << std::endl;
    return 0;
}
