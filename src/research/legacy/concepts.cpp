#include <array>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <iostream>
#include <limits>
#include <string>
#include <type_traits>

/**
 * Performs a bitwise circular shift left on an unsigned integral type.
 * 
 * @param x The unsigned integral to circular shift left.
 * @param r The shift amount.
 * @return The bitwise circular shift left of x.
 */
template <std::integral T>
constexpr T RotateLeft(T x, int r)
{
    constexpr int kNumBits = std::numeric_limits<T>::digits;
    if ((r %= kNumBits) == 0)
    {
        return x;
    }
    else if (r > 0)
    {
        return (x << +r) | (x >> ((kNumBits - r) % kNumBits));
    }
    else
    {
        return (x >> -r) | (x << ((kNumBits + r) % kNumBits));
    }
}

int main(int argc, char* argv[])
{
    std::cout << RotateLeft(0xFFFFFFFFFFFFFFFFull, 0) << std::endl;
    return 0;
}