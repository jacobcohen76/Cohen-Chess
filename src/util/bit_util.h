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

    template <typename T>
    constexpr T FlipLSB(T x)
    {
        return x & (x - 1);
    }

    template <typename T>
    constexpr int PopCountLSB(T x)
    {
        int pop_count = 0;
        while(x)
        {
            ++pop_count;
            x &= x - 1
        }
        return pop_count;
    }

    template <typename T>
    inline int PopCountLookup(T x)
    {
        int pop_count = 0;
        while(x)
        {
            pop_count += bit_util::kU16PopCountTable[x & 0xFFFF];
            x = (x & ~0xFFFF) >> 16;
        }
        return pop_count;
    }

    template <>
    inline int PopCountLookup<uint8_t>(uint8_t x)
    {
        return bit_util::kU16PopCountTable[x];
    }

    template <>
    inline int PopCountLookup<uint16_t>(uint16_t x)
    {
        return bit_util::kU16PopCountTable[x];
    }

    template <>
    inline int PopCountLookup<uint32_t>(uint32_t x)
    {
        return  bit_util::kU16PopCountTable[(x >>  0) & 0xFFFF] +
                bit_util::kU16PopCountTable[(x >> 16) & 0xFFFF];
    }

    template <>
    inline int PopCountLookup<uint64_t>(uint64_t x)
    {
        return  bit_util::kU16PopCountTable[(x >>  0) & 0xFFFF] +
                bit_util::kU16PopCountTable[(x >> 16) & 0xFFFF] +
                bit_util::kU16PopCountTable[(x >> 32) & 0xFFFF] +
                bit_util::kU16PopCountTable[(x >> 48) & 0xFFFF];
    }
};

#endif