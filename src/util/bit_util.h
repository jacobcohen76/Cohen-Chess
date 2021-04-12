#ifndef COHEN_CHESS_UTIL_BIT_UTIL_H_INCLUDED
#define COHEN_CHESS_UTIL_BIT_UTIL_H_INCLUDED

#include <cassert>
#include <cstdint>
#include <string>
#include <type_traits>

namespace cohen_chess
{
    namespace bit_util
    {
        extern uint8_t kU16PopCountTable[65536];

        void InitPopCountTable(uint8_t[], size_t);
        void Init();
    };

    template <typename T>
    constexpr std::enable_if<std::is_integral<T>::value>::type FlipLSB(T x)
    {
        return x & (x - 1);
    }

    template <typename T>
    constexpr std::enable_if<std::is_integral<T>::value>::type RotateLeft(T x, int r)
    {
        if constexpr (std::numeric_limits<T>::is_signed)
        {
            if (x < 0)
            {

            }
            else
            {
                
            }
        }
        else
        {

        }
    }

    template <typename T>
    constexpr std::enable_if<std::is_integral<T>::value>::type RotateRight(T x, int r)
    {
        if constexpr (std::numeric_limits<T>::is_signed)
        {
            if (x < 0)
            {

            }
            else
            {
                
            }
        }
        else
        {

        }
    }

    /**
     * Returns the bit-index of the least significant 1 bit (LS1B).
     * 
     * Multiplying by a power of 2 (the isolated LS1B) acts like a left shift
     * by it's exponent. Thus, by multiplying a 64-bit De Bruijn Sequence with
     * a with an integer's isolated LS1B, the product will have a unique 6-bit
     * subsequence in the most significant bits. The bit-index of the LS1B
     * is then obtained by looking up this subsequence in an arry.
     * https://www.chessprogramming.org/BitScan#De_Bruijn_Multiplication
     * 
     * De Brujin constants generated using seed '1776' on the following program:
     * https://www.chessprogramming.org/De_Bruijn_Sequence_Generator
     * @author Gerd Isenberg
     * 
     * @param x the integer to scan
     * @return index (0..63) of least significant 1-bit
     * @throws assert x != 0
     */
    inline int DeBruijnBitScanForward(uint64_t x)
    {
        static constexpr uint64_t kDebruijn64 = 0x0218A3AB27B9B4BF;
        static const int kBitIndexTable[64] =
        {
             0,  1,  2,  7,  3, 13,  8, 19,
             4, 32, 14, 54,  9, 45, 20, 35,
             5, 17, 52, 33, 15, 25, 27, 55,
            10, 29, 49, 46, 41, 21, 36, 57,
            63,  6, 12, 18, 31, 53, 44, 34,
            16, 51, 24, 26, 28, 48, 40, 56,
            62, 11, 30, 43, 50, 23, 47, 39,
            61, 42, 22, 38, 60, 37, 59, 58,
        };
        assert(x != 0);
        return kBitIndexTable[((x & -x) * kDebruijn64) >> 58];
    }

    inline int BuiltinBitScanForward(uint64_t x)
    {
        assert(x != 0);
        return __builtin_ctzll(x);
    }

    inline int BitScanForward(uint64_t x)
    {
        return BuiltinBitScanForward(x);
    }

    /**
     * https://www.chessprogramming.org/BitScan#De_Bruijn_Multiplication_2
     * 
     * @author Kim Walisch, Mark Dickinson
     * @param x the integer to scan
     * @return index(0..63) of most significant 1-bit
     * @throws assert x != 0
     */
    inline int DeBruijnBitScanReverse(uint64_t x)
    {
        static constexpr uint64_t kDebruijn64 = 0x03F79D71B4CB0A89;
        static const int kBitIndexTable[64] =
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
        assert(x != 0);
        x |= x >>  1;
        x |= x >>  2;
        x |= x >>  4;
        x |= x >>  8;
        x |= x >> 16;
        x |= x >> 32;
        return kBitIndexTable[(x * kDebruijn64) >> 58];
    }

    inline int BuiltinBitScanReverse(uint64_t x)
    {
        assert(x != 0);
        return 63 - __builtin_clzll(x);
    }

    inline int BitScanReverse(uint64_t x)
    {
        return BuiltinBitScanReverse(x);
    }

    inline int PopCountLSB(uint64_t x)
    {
        int count = 0;
        while(x)
        {
            ++count;
            x &= x - 1;
        }
        return count;
    }

    inline int PopCountLookup(uint64_t x)
    {
        return bit_util::kU16PopCountTable[(x >>  0) & 0xFFFF] +
               bit_util::kU16PopCountTable[(x >> 16) & 0xFFFF] +
               bit_util::kU16PopCountTable[(x >> 32) & 0xFFFF] +
               bit_util::kU16PopCountTable[(x >> 48) & 0xFFFF];
    }

    inline int PopCountBuiltin(uint64_t x)
    {
        return __builtin_popcountll(x);
    }

    inline int PopCount(uint64_t x)
    {
        return PopCountBuiltin(x);
    }

    template <bool lowercase = false>
    inline char HexCharacter(uint64_t nibble)
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

    template <size_t no_digits = 16, bool lowercase = false>
    inline std::string HexString(uint64_t raw_bits)
    {
        std::string hex_string(no_digits, '0');
        size_t i = -1;
        while(raw_bits)
        {
            hex_string[no_digits - ++i - 1] = HexCharacter<lowercase>(raw_bits & 0xF);
            raw_bits = (raw_bits & ~0xF) >> 4;
        }
        return hex_string;
    }

    template <size_t no_bits = 64>
    inline std::string BinaryString(uint64_t raw_bits)
    {
        std::string binary_string(no_bits, '0');
        size_t i = -1;
        while(raw_bits)
        {
            binary_string[no_bits - ++i - 1] = (raw_bits & 1) + '0';
            raw_bits = (raw_bits & ~0x1) >> 1;
        }
        return binary_string;
    }
}

#endif