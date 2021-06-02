#ifndef COHEN_CHESS_UTIL_BIT_UTIL_HPP_INCLUDED
#define COHEN_CHESS_UTIL_BIT_UTIL_HPP_INCLUDED

#include <array>
#include <bit>
#include <concepts>
#include <cassert>
#include <cstdint>

namespace cohen_chess
{
    namespace bit_util
    {
        constexpr std::array<uint8_t, 65536> kPopCountTable = []()
        {
            std::array<uint8_t, 65536> pop_count_table = {};
            for (size_t i = 0; i < 65536; ++i)
            {
                uint8_t count = 0;
                uint64_t x = i;
                while (x)
                {
                    ++count;
                    x &= x - 1;
                }
                pop_count_table[i] = count;
            }
            return pop_count_table;
        }();

        constexpr std::array<int, 64> kDeBruijnIndex64 =
        {
             0, 47,  1, 56, 48, 27,  2, 60,
            57, 49, 41, 37, 28, 16,  3, 61,
            54, 58, 35, 52, 50, 42, 21, 44,
            38, 32, 29, 23, 17, 11,  4, 62,
            46, 55, 26, 59, 40, 36, 15, 53,
            34, 51, 20, 43, 31, 22, 10, 45,
            25, 39, 14, 33, 19, 30,  9, 24,
            13, 18,  8, 12,  7,  6,  5, 63,
        };
    }

    template <std::integral T>
    constexpr size_t kNumBits = sizeof(T) * 8;

    template <std::integral T>
    constexpr T RotateLeft(T x, int r) noexcept
    {
        if ((r %= kNumBits<T>) > 0)
        {
            return (x << +r) | (x >> ((kNumBits<T> - r) % kNumBits<T>));
        }
        else
        {
            return (x >> -r) | (x << ((kNumBits<T> + r) % kNumBits<T>));
        }
    }

    template <std::integral T>
    constexpr T RotateRight(T x, int r) noexcept
    {
        if (r %= kNumBits<T>)
        {
            return (x >> +r) | (x << ((kNumBits<T> - r) % kNumBits<T>));
        }
        else
        {
            return (x << -r) | (x >> ((kNumBits<T> + r) % kNumBits<T>));
        }
    }

    /**
     * Performs a forward bit scan on an integral type.
     * https://www.chessprogramming.org/BitScan#With_separated_LS1B
     * 
     * @author Kim Walisch
     * @param x integral to scan
     * @precondition x != 0
     * @return index (0..63) of least significant one bit
     */
    template <std::integral T>
    constexpr int DeBruijnBitScanForward(T x) noexcept
    {
        assert(x != 0);
        constexpr uint64_t kDebruijn64 = 0x03F79D71B4CB0A89;
        return bit_util::kDeBruijnIndex64[(x ^ (x - 1)) * kDebruijn64 >> 58];
    }

    /**
     * Perofrms a reverse bit scan on an integral type.
     * https://www.chessprogramming.org/BitScan#De_Bruijn_Multiplication_2
     * 
     * @author Kim Wallisch, Mark Dickinson
     * @param x integral to scan
     * @precondition x != 0
     * @return index (0..63) of most significant one bit
     */
    template <std::integral T>
    constexpr int DeBruijnBitScanReverse(T x) noexcept
    {
        assert(x != 0);
        constexpr uint64_t kDebruijn64 = 0x03F79D71B4CB0A89;
        x |= x >> 1, x |= x >> 2, x |= x >> 4;
        if constexpr (kNumBits<uint16_t> <= kNumBits<T>)
            x |= x >>  8;
        if constexpr (kNumBits<uint32_t> <= kNumBits<T>)
            x |= x >> 16;
        if constexpr (kNumBits<uint64_t> <= kNumBits<T>)
            x |= x >> 32;
        return bit_util::kDeBruijnIndex64[(x * kDebruijn64) >> 58];
    }

    template <std::integral T>
    constexpr int PopCountLSB(T x) noexcept
    {
        int count = 0;
        while (x)
        {
            ++count;
            x &= x - 1;
        }
        return count;
    }

    template <std::integral T>
    constexpr int PopCountLookup(T x) noexcept
    {
        if constexpr (kNumBits<T> <= kNumBits<uint16_t>)
        {
            return bit_util::kPopCountTable[x & 0xFFFF];
        }
        else if constexpr (kNumBits<T> <= kNumBits<uint32_t>)
        {
            return bit_util::kPopCountTable[(x >>  0) & 0xFFFF] +
                   bit_util::kPopCountTable[(x >> 16) & 0xFFFF];
        }
        else
        {
            return bit_util::kPopCountTable[(x >>  0) & 0xFFFF] +
                   bit_util::kPopCountTable[(x >> 16) & 0xFFFF] +
                   bit_util::kPopCountTable[(x >> 32) & 0xFFFF] +
                   bit_util::kPopCountTable[(x >> 48) & 0xFFFF];
        }
    }

    template <std::integral T>
    constexpr int PopCountBuiltin(T x) noexcept
    {
        if constexpr(kNumBits<T> <= kNumBits<unsigned int>)
        {
            return __builtin_popcount(x);
        }
        else if constexpr(kNumBits<T> <= kNumBits<unsigned long>)
        {
            return __builtin_popcountl(x);
        }
        else
        {
            return __builtin_popcountll(x);
        }
    }

    template <typename... Args>
    auto PopCount(Args&&... args)
    {
        return PopCountBuiltin(std::forward<Args>(args)...);
    }
}

#endif