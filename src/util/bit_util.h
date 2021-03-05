#ifndef COHEN_CHESS_UTIL_BIT_UTIL_H_INCLUDED
#define COHEN_CHESS_UTIL_BIT_UTIL_H_INCLUDED

#include <cstdint>
#include <string>

namespace cohen_chess
{
    namespace bit_util
    {
        extern uint8_t kU16PopCountTable[65536];

        void InitPopCountTable(uint8_t[], size_t);
    };

    template<typename T>
    inline int PopCountLookup(T x)
    {
        int pop_count = 0;
        while(x)
        {
            pop_count += bit_util::kU16PopCountTable[x & 0xFFFF];
            x >>= 16;
        }
        return pop_count;
    }

    template <>
    inline int PopCountLookup<uint8_t>(uint8_t x)
    {
        return  bit_util::kU16PopCountTable[x];
    }

    template <>
    inline int PopCountLookup<uint16_t>(uint16_t x)
    {
        return  bit_util::kU16PopCountTable[x];
    }

    template<>
    inline int PopCountLookup<uint32_t>(uint32_t x)
    {
        return  bit_util::kU16PopCountTable[(x >>  0) & 0xFFFF] +
                bit_util::kU16PopCountTable[(x >> 16) & 0xFFFF];
    }

    template<>
    inline int PopCountLookup<uint64_t>(uint64_t x)
    {
        return  bit_util::kU16PopCountTable[(x >>  0) & 0xFFFF] +
                bit_util::kU16PopCountTable[(x >> 16) & 0xFFFF] +
                bit_util::kU16PopCountTable[(x >> 32) & 0xFFFF] +
                bit_util::kU16PopCountTable[(x >> 48) & 0xFFFF];
    }

    template<typename T>
    constexpr int PopCountLSB(T x)
    {
        int pop_count = 0;
        while(x)
        {
            ++pop_count;
            x &= x ^ -x;
        }
        return pop_count;
    }

    template<typename T>
    constexpr T FlipLSB(T x)
    {
        return x & (x ^ -x);
    }

    template<bool lowercase = false>
    constexpr char HexChar(uint64_t nibble)
    {
        switch(nibble & 0xF)
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

    template<size_t no_digits = 16, bool lowercase = false>
    inline std::string HexString(uint64_t raw_bits)
    {
        std::string hex_string(no_digits, '0');
        size_t i = 0;
        while(raw_bits)
        {
            hex_string[no_digits - i - 1] = HexChar<lowercase>(raw_bits);
            raw_bits >>= 4;
            i += 1;
        }
        return hex_string;
    }

    template<size_t no_bits = 64>
    inline std::string BinaryString(uint64_t raw_bits)
    {
        std::string binary_string(no_bits, '0');
        size_t i = 0;
        while(raw_bits)
        {
            binary_string[no_bits - i - 1] = (raw_bits & 1) + '1';
            raw_bits >>= 1;
            i += 1;
        }
        return binary_string;
    }
};

#endif