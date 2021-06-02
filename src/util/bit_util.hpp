#ifndef COHEN_CHESS_UTIL_BIT_UTIL_HPP_INCLUDED
#define COHEN_CHESS_UTIL_BIT_UTIL_HPP_INCLUDED

#include <array>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <limits>
#include <string>
#include <type_traits>

namespace cohen_chess
{
    template <typename T>
    constexpr size_t NumBits(T x)
    {
        return sizeof(x) * 8;
    }

    template <typename T>
    constexpr size_t NumBits()
    {
        return sizeof(T) * 8;
    }

    /**
     * Performs a bitwise circular shift left on an integral type.
     * 
     * @param x The integral to circular shift left.
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

    /**
     * Performs a bitwise cicular shift right on an integral type.
     * 
     * @param x The integral to circular shift right.
     * @param r The shift amount.
     * @return The bitwise circular shift right of x.
     */
    template <std::integral T>
    constexpr T RotateRight(T x, int r)
    {
        constexpr int kNumBits = std::numeric_limits<T>::digits + std::numeric_limits<T>::is_signed;
        if ((r %= kNumBits) == 0)
        {
            return x;
        }
        else if (r > 0)
        {
            return (x >> +r) | (x << ((kNumBits - r) % kNumBits));
        }
        else
        {
            return (x << -r) | (x >> ((kNumBits + r) % kNumBits));
        }
    }

    template <std::integral T>
    constexpr int BuiltinCountTrailingZeroes(T x)
    {
        constexpr int kNumBitsULL = std::numeric_limits<unsigned long long>::digits;
        constexpr int kNumBitsUL = std::numeric_limits<unsigned long>::digits;
        constexpr int kNumBitsU = std::numeric_limits<unsigned>::digits;
        constexpr int kNumBits = std::numeric_limits<T>::digits + std::numeric_limits<T>::is_signed;
        if (x == 0)
        {
            return kNumBits;
        }
        else if constexpr (kNumBits <= kNumBitsU)
        {
            return __builtin_ctz(x);
        }
        else if constexpr (kNumBits <= kNumBitsUL)
        {
            return __builtin_ctzl(x);
        }
        else if constexpr (kNumBits <= kNumBitsULL)
        {
            return __builtin_ctzll(x);
        }
        else
        {
            static_assert(kNumBits <= kNumBitsULL, "Maximum supported integer size is 64-bit");
        }
    }

    template <std::integral T>
    constexpr int CountTrailingZeroes(T x)
    {
        return BuiltinCountTrailingZeroes(x);
    }

    template <std::integral T>
    constexpr int BuiltinCountLeadingZeroes(T x)
    {
        constexpr int kNumBitsULL = std::numeric_limits<unsigned long long>::digits;
        constexpr int kNumBitsUL = std::numeric_limits<unsigned long>::digits;
        constexpr int kNumBitsU = std::numeric_limits<unsigned>::digits;
        constexpr int kNumBits = std::numeric_limits<T>::digits + std::numeric_limits<T>::is_signed;
        if (x == 0)
        {
            return kNumBits;
        }
        else if constexpr (kNumBits <= kNumBitsU)
        {
            constexpr int kDiff = kNumBitsU - kNumBits;
            return __builtin_clz(x) - kDiff;
        }
        else if constexpr (kNumBits <= kNumBitsUL)
        {
            constexpr int kDiff = kNumBitsUL - kNumBits;
            return __builtin_clzl(x) - kDiff;
        }
        else if constexpr (kNumBits <= kNumBitsULL)
        {
            constexpr int kDiff = kNumBitsULL - kNumBits;
            return __builtin_clzll(x) - kDiff;
        }
        else
        {
            static_assert(kNumBits <= kNumBitsULL, "Maximum supported integer size is 64-bit");
        }
    }

    template <std::integral T>
    constexpr int CountLeadingZeroes(T x)
    {
        return BuiltinCountLeadingZeroes(x);
    }

    template <std::integral T>
    constexpr int BuiltinCountTrailingOnes(T x)
    {
        return BuiltinCountTrailingZeroes(~x);
    }

    template <std::integral T>
    constexpr int CountTrailingOnes(T x)
    {
        return BuiltinCountTrailingOnes(x);
    }

    template <std::integral T>
    constexpr int BuiltinCountLeadingOnes(T x)
    {
        return BuiltinCountLeadingZeroes(~x);
    }

    template <std::integral T>
    constexpr int CountLeadingOnes(T x)
    {
        return BuiltinCountLeadingOnes(x);
    }

    template <std::integral T>
    constexpr int BuiltinBitScanForward(T x)
    {
        return BuiltinCountTrailingZeroes(x);
    }

    template <std::integral T>
    constexpr int BitScanForward(T x)
    {
        return BuiltinBitScanForward(x);
    }

    template <std::integral T>
    constexpr int BuiltinBitScanReverse(T x)
    {
        constexpr int kNumBits = std::numeric_limits<T>::digits + std::numeric_limits<T>::is_signed;
        if (x == 0)
        {
            return kNumBits;
        }
        else
        {
            return kNumBits - 1 - BuiltinCountLeadingZeroes(x);
        }
    }

    template <std::integral T>
    constexpr int BitScanReverse(T x)
    {
        return BuiltinBitScanReverse(x);
    }

    template <std::integral T>
    constexpr int PopCountLSB(T x)
    {
        int count = 0;
        while (x)
        {
            ++count;
            x &= x - 1;
        }
        return count;
    }

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

    template <std::integral T>
    constexpr int PopCountLookup(T x)
    {
        constexpr int kNumBits64 = std::numeric_limits<uint64_t>::digits;
        constexpr int kNumBits32 = std::numeric_limits<uint32_t>::digits;
        constexpr int kNumBits16 = std::numeric_limits<uint16_t>::digits;
        constexpr int kNumBits = std::numeric_limits<T>::digits + std::numeric_limits<T>::is_signed;
        if (x == 0)
        {
            return 0;
        }
        else if constexpr (kNumBits <= kNumBits16)
        {
            return kPopCountTable[x & 0xFFFF];
        }
        else if constexpr (kNumBits <= kNumBits32)
        {
            return kPopCountTable[(x >>  0) & 0xFFFF] +
                   kPopCountTable[(x >> 16) & 0xFFFF];
        }
        else if constexpr (kNumBits <= kNumBits64)
        {
            return kPopCountTable[(x >>  0) & 0xFFFF] +
                   kPopCountTable[(x >> 16) & 0xFFFF] +
                   kPopCountTable[(x >> 32) & 0xFFFF] +
                   kPopCountTable[(x >> 48) & 0xFFFF];
        }
        else
        {
            static_assert(kNumBits <= kNumBits64, "Maximum supported integer size is 64-bit");
        }
    }

    template <std::integral T>
    constexpr int PopCountBuiltin(T x)
    {
        constexpr int kNumBitsULL = std::numeric_limits<unsigned long long>::digits;
        constexpr int kNumBitsUL = std::numeric_limits<unsigned long>::digits;
        constexpr int kNumBitsU = std::numeric_limits<unsigned>::digits;
        constexpr int kNumBits = std::numeric_limits<T>::digits;
        if (x == 0)
        {
            return 0;
        }
        else if constexpr (kNumBits <= kNumBitsU)
        {
            return __builtin_popcount(x);
        }
        else if constexpr (kNumBits <= kNumBitsUL)
        {
            return __builtin_popcountl(x);
        }
        else if constexpr (kNumBits <= kNumBitsULL)
        {
            return __builtin_popcountll(x);
        }
        else
        {
            static_assert(kNumBits <= kNumBitsULL, "Maximum supported integer size is 64-bit");
        }
    }

    template <std::integral T>
    constexpr int PopCount(T x)
    {
        return PopCountBuiltin(x);
    }

    /**
     * Flips the least significant bit of an integral.
     * 
     * @param x The integral to flip the least signficant bit of.
     * @return The value of x with its least significant bit flipped.
     */
    template <std::integral T>
    constexpr T FlipLSB(T x)
    {
        return x & (x - 1);
    }

    /**
     * Gets the bit-index of the least significant bit and flips it.
     * 
     * @param x The integral to pop the least significant bit of.
     * @return The bit-index of the least significant bit.
     */
    template <std::integral T>
    constexpr int PopLSB(T& x)
    {
        int lsb = BitScanForward(x);
        x = FlipLSB(x);
        return lsb;
    }

    /**
     * Gets the bit-index of the most significant bit and flips it.
     * 
     * @param x The integral to pop the most significant bit of.
     * @return The bit-index of the most significant bit.
     */
    template <std::integral T>
    constexpr int PopMSB(T& x)
    {
        int msb = BitScanReverse(x);
        x ^= T(1) << msb;
        return msb;
    }

    template <std::integral T, bool lowercase = false>
    constexpr char HexCharacter(T nibble)
    {
        switch(nibble)
        {
            case 0x0:   return '0';
            case 0x1:   return '1';
            case 0x2:   return '2';
            case 0x3:   return '3';
            case 0x4:   return '4';
            case 0x5:   return '5';
            case 0x6:   return '6';
            case 0x7:   return '7';
            case 0x8:   return '8';
            case 0x9:   return '9';
            case 0xA:   return 'A' + lowercase * 0x20;
            case 0xB:   return 'B' + lowercase * 0x20;
            case 0xC:   return 'C' + lowercase * 0x20;
            case 0xD:   return 'D' + lowercase * 0x20;
            case 0xE:   return 'E' + lowercase * 0x20;
            case 0xF:   return 'F' + lowercase * 0x20;
            default:    return '?';
        }
    }

    template <std::integral T, size_t no_digits = (std::numeric_limits<T>::digits + std::numeric_limits<T>::is_signed) / 4, bool lowercase = false>
    inline std::string HexString(T raw_bits)
    {
        std::string hex_string(no_digits, '0');
        size_t i = -1;
        while (raw_bits)
        {
            hex_string[no_digits - ++i - 1] = HexCharacter<T, lowercase>(raw_bits & 0xF);
            raw_bits = (raw_bits & ~0xF) >> 4;
        }
        return hex_string;
    }

    template <std::integral T, size_t no_bits = std::numeric_limits<T>::digits + std::numeric_limits<T>::is_signed>
    inline std::string BinaryString(T raw_bits)
    {
        std::string binary_string(no_bits, '0');
        size_t i = -1;
        while (raw_bits)
        {
            binary_string[no_bits - ++i - 1] = (raw_bits & 1) + '0';
            raw_bits = (raw_bits & ~0x1) >> 1;
        }
        return binary_string;
    }
}

#endif