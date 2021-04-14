#include <bit>
#include <bitset>
#include <cstdint>
#include <iostream>
#include <type_traits>


template <typename T>
constexpr std::enable_if<std::is_unsigned<T>::value, T>::type RotateLeft(T x, int r)
{
    constexpr int no_bits = std::numeric_limits<T>::digits;
    if ((r %= no_bits) == 0)
    {
        return x;
    }
    else if (r > 0)
    {
        return (x << +r) | (x >> ((no_bits - r) % no_bits));
    }
    else
    {
        return (x >> -r) | (x << ((no_bits + r) % no_bits));
    }
}

template <typename T>
constexpr std::enable_if<std::is_unsigned<T>::value, T>::type RotateRight(T x, int r)
{
    constexpr int no_bits = std::numeric_limits<T>::digits;
    if ((r %= no_bits) == 0)
    {
        return x;
    }
    else if (r > 0)
    {
        return (x >> +r) | (x << ((no_bits - r) % no_bits));
    }
    else
    {
        return (x << -r) | (x >> ((no_bits + r) % no_bits));
    }
}


int main(int argc, char* argv[])
{
    uint8_t x = 0x32;
    for (int r = 0; r <= 8; ++r)
    {
        std::cout << std::bitset<8>(RotateLeft(x, r)) << std::endl;
    }
    return 0;
}