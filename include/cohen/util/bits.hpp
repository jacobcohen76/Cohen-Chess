#ifndef COHEN_UTIL_BITS_HPP_INCLUDED
#define COHEN_UTIL_BITS_HPP_INCLUDED

#include <assert.h>
#include <stdint.h>

#include <array>
#include <bit>
#include <concepts>

namespace cohen::util::bits
{
    template <std::unsigned_integral T> constexpr int PopCount(T) noexcept;
    template <std::unsigned_integral T> constexpr int BitScanForward(T) noexcept;

    template <typename T>
    inline constexpr std::size_t kNumBits = sizeof(T) * 8;

    template <std::unsigned_integral T>
    constexpr T CarryRipple(T x, T mask) noexcept
    {
        return (x - mask) & mask;
    }

    template <std::unsigned_integral T>
    constexpr T Snoob(T x)
    {
        const T smallest = x & -x;
        const T ripple   = x + smallest;
        const T ones     = x ^ ripple;
        return (ones >> 2) / smallest | ripple;
    }

    template <std::unsigned_integral T>
    constexpr T RotateLeft(T x, int s) noexcept
    {
        return std::rotl(x, s);
    }

    template <std::unsigned_integral T>
    constexpr T RotateRight(T x, int s) noexcept
    {
        return std::rotr(x, s);
    }

    template <std::unsigned_integral T>
    constexpr T FlipLSB(T x) noexcept
    {
        return x & (x - 1);
    }

    template <std::unsigned_integral T>
    constexpr int PopLSB(T& x) noexcept
    {
        assert(x != 0);
        const int lsb = BitScanForward(x);
        x = FlipLSB(x);
        return lsb;
    }

    template <std::unsigned_integral T>
    constexpr int BuiltinPopCount(T x) noexcept
    {
        return std::popcount(x);
    }

    template <std::unsigned_integral T>
    constexpr int PopCountLSB(T x) noexcept
    {
        int count = 0;
        while (x)
        {
            ++count, x = FlipLSB(x);
        }
        return count;
    }

    inline constexpr std::array<uint8_t, 65536> kPopCountTable = []()
    {
        std::array<uint8_t, 65536> lookup_table = {};
        for (uint32_t x = 0; x < lookup_table.size(); ++x)
        {
            lookup_table[x] = PopCountLSB(x);
        }
        return lookup_table;
    }();

    template <std::unsigned_integral T>
    constexpr int PopCountLookup(T x) noexcept
    {
        static_assert(kNumBits<T> <= kNumBits<uint64_t>);
        if constexpr (kNumBits<T> <= kNumBits<uint16_t>)
        {
            return kPopCountTable[(x >>  0) & 0xFFFF];
        }
        else if constexpr (kNumBits<T> <= kNumBits<uint32_t>)
        {
            return kPopCountTable[(x >>  0) & 0xFFFF]
                 + kPopCountTable[(x >> 16) & 0xFFFF];
        }
        else
        {
            return kPopCountTable[(x >>  0) & 0xFFFF]
                 + kPopCountTable[(x >> 16) & 0xFFFF]
                 + kPopCountTable[(x >> 32) & 0xFFFF]
                 + kPopCountTable[(x >> 48) & 0xFFFF];
        }
    }

    template <std::unsigned_integral T>
    constexpr int PopCountBitScanForward(T x) noexcept
    {
        assert(x != 0);
        return PopCount((x & -x) - 1);
    }

    template <std::unsigned_integral T>
    constexpr int BuiltinCountTrailingZeroes(T x) noexcept
    {
        assert(x != 0);
        static_assert(kNumBits<T> <= kNumBits<unsigned long long>);
        if constexpr (kNumBits<T> <= kNumBits<unsigned int>)
        {
            return __builtin_ctz(x);
        }
        else if constexpr (kNumBits<T> <= kNumBits<unsigned long>)
        {
            return __builtin_ctzl(x);
        }
        else
        {
            return __builtin_ctzll(x);
        }
    }

    template <std::unsigned_integral T>
    constexpr int BuiltinCountTrailingOnes(T x) noexcept
    {
        assert(x != 0);
        return BuiltinCountTrailingZeroes(~x);
    }

    template <std::unsigned_integral T>
    constexpr int BuiltinBitScanForward(T x) noexcept
    {
        assert(x != 0);
        return BuiltinCountTrailingZeroes(x);
    }

    template <std::unsigned_integral T>
    constexpr int BuiltinCountLeadingZeroes(T x) noexcept
    {
        assert(x != 0);
        static_assert(kNumBits<T> <= kNumBits<unsigned long long>);
        if constexpr (kNumBits<T> <= kNumBits<unsigned int>)
        {
            constexpr auto diff = kNumBits<unsigned int> - kNumBits<T>;
            return __builtin_clz(x) - diff;
        }
        else if constexpr (kNumBits<T> <= kNumBits<unsigned long>)
        {
            constexpr auto diff = kNumBits<unsigned long> - kNumBits<T>;
            return __builtin_clzl(x) - diff;
        }
        else
        {
            constexpr auto diff = kNumBits<unsigned long long> - kNumBits<T>;
            return __builtin_clzll(x) - diff;
        }
    }

    template <std::unsigned_integral T>
    constexpr int BuiltinCountLeadingOnes(T x) noexcept
    {
        assert(x != 0);
        return BuiltinCountLeadingZeroes(~x);
    }

    template <std::unsigned_integral T>
    constexpr int BuiltinBitScanReverse(T x) noexcept
    {
        assert(x != 0);
        return BuiltinCountLeadingZeroes(x) ^ (kNumBits<T> - 1);
    }

    inline constexpr uint64_t kDebruijn64 = 0x03F79D71B4CB0A89;

    inline constexpr std::array<int, 64> kDeBruijnIndex64 =
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

    /**
     * Performs a forward bit scan on an integral type.
     * https://www.chessprogramming.org/BitScan#With_separated_LS1B
     * 
     * @author Kim Walisch
     * @param x integral to scan
     * @precondition x != 0
     * @return index (0..63) of least significant one bit
     */
    template <std::unsigned_integral T>
    constexpr int DeBruijnBitScanForward(T x) noexcept
    {
        assert(x != 0);
        return kDeBruijnIndex64[(x ^ (x - 1)) * kDebruijn64 >> 58];
    }

    template <std::unsigned_integral T>
    constexpr int DeBruijnCountTrailingZeroes(T x) noexcept
    {
        assert(x != 0);
        return DeBruijnBitScanForward(x);
    }

    template <std::unsigned_integral T>
    constexpr int DeBruijnCountTrailingOnes(T x) noexcept
    {
        assert(~x != 0);
        return DeBruijnCountTrailingZeroes(~x);
    }

    /**
     * Performs a reverse bit scan on an integral type.
     * https://www.chessprogramming.org/BitScan#De_Bruijn_Multiplication_2
     * 
     * @author Kim Wallisch, Mark Dickinson
     * @param x integral to scan
     * @precondition x != 0
     * @return index (0..63) of most significant one bit
     */
    template <std::unsigned_integral T>
    constexpr int DeBruijnBitScanReverse(T x) noexcept
    {
        assert(x != 0);
        static_assert(kNumBits<T> <= kNumBits<uint64_t>);
        x |= x >> 1, x |= x >> 2, x |= x >> 4;
        if constexpr (kNumBits<uint16_t> <= kNumBits<T>)
            x |= x >>  8;
        if constexpr (kNumBits<uint32_t> <= kNumBits<T>)
            x |= x >> 16;
        if constexpr (kNumBits<uint64_t> <= kNumBits<T>)
            x |= x >> 32;
        return kDeBruijnIndex64[(x * kDebruijn64) >> 58];
    }

    template <std::unsigned_integral T>
    constexpr int DeBruijnCountLeadingZeroes(T x) noexcept
    {
        assert(x != 0);
        return DeBruijnBitScanReverse(x) ^ (kNumBits<T> - 1);
    }

    template <std::unsigned_integral T>
    constexpr int DeBruijnCountLeadingOnes(T x) noexcept
    {
        assert(~x != 0);
        return DeBruijnCountLeadingZeroes(~x);
    }

    template <std::unsigned_integral T>
    constexpr int PopCount(T x) noexcept
    {
        return BuiltinPopCount(x);
    }

    template <std::unsigned_integral T>
    constexpr int CountTrailingZeroes(T x) noexcept
    {
        return BuiltinCountTrailingZeroes(x);
    }

    template <std::unsigned_integral T>
    constexpr int CountTrailingOnes(T x) noexcept
    {
        return BuiltinCountTrailingOnes(x);
    }

    template <std::unsigned_integral T>
    constexpr int BitScanForward(T x) noexcept
    {
        return BuiltinBitScanForward(x);
    }

    template <std::unsigned_integral T>
    constexpr int CountLeadingZeroes(T x) noexcept
    {
        return BuiltinCountLeadingZeroes(x);
    }

    template <std::unsigned_integral T>
    constexpr int CountLeadingOnes(T x) noexcept
    {
        return BuiltinCountLeadingOnes(x);
    }

    template <std::unsigned_integral T>
    constexpr int BitScanReverse(T x) noexcept
    {
        return BuiltinBitScanReverse(x);
    }
}

namespace cohen
{
    using cohen::util::bits::kNumBits;

    using cohen::util::bits::CarryRipple;
    using cohen::util::bits::Snoob;
    using cohen::util::bits::RotateLeft;
    using cohen::util::bits::RotateRight;
    using cohen::util::bits::FlipLSB;
    using cohen::util::bits::PopLSB;
    using cohen::util::bits::PopCount;
    using cohen::util::bits::CountTrailingZeroes;
    using cohen::util::bits::CountTrailingOnes;
    using cohen::util::bits::BitScanForward;
    using cohen::util::bits::CountLeadingZeroes;
    using cohen::util::bits::CountLeadingOnes;
    using cohen::util::bits::BitScanReverse;
}

#endif
