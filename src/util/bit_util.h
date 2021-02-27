#ifndef COHEN_CHESS_UTIL_BIT_UTIL_H_INCLUDED
#define COHEN_CHESS_UTIL_BIT_UTIL_H_INCLUDED

#include <cstdint>
#include <string>

namespace cohen_chess
{
    namespace util
    {
        static constexpr const uint8_t kBytePopCounts[256] =
        {
            0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
            1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
            1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
            2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
            1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
            2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
            2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
            3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
            1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
            2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
            2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
            3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
            2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
            3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
            3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
            4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
        };

        constexpr int PopCountLookup_Byte(uint8_t byte)
        {
            return  kBytePopCounts[byte];
        }

        constexpr int PopCountLookup_U16(uint16_t u16)
        {
            return  kBytePopCounts[(u16 >> 0) & 0xFF] +
                    kBytePopCounts[(u16 >> 8) & 0xFF];
        }

        constexpr int PopCountLookup_U32(uint32_t u32)
        {
            return  kBytePopCounts[(u32 >>  0) & 0xFF] +
                    kBytePopCounts[(u32 >>  8) & 0xFF] +
                    kBytePopCounts[(u32 >> 16) & 0xFF] +
                    kBytePopCounts[(u32 >> 24) & 0xFF];
        }

        constexpr int PopCountLookup_U64(uint64_t u64)
        {
            return  kBytePopCounts[(u64 >>  0) & 0xFF] +
                    kBytePopCounts[(u64 >>  8) & 0xFF] +
                    kBytePopCounts[(u64 >> 16) & 0xFF] +
                    kBytePopCounts[(u64 >> 24) & 0xFF] +
                    kBytePopCounts[(u64 >> 32) & 0xFF] +
                    kBytePopCounts[(u64 >> 40) & 0xFF] +
                    kBytePopCounts[(u64 >> 48) & 0xFF] +
                    kBytePopCounts[(u64 >> 56) & 0xFF];
        }

        constexpr int PopCountLSB_Byte(uint8_t byte)
        {
            int pop_count = 0;
            while(byte)
            {
                ++pop_count;
                byte &= byte ^ -byte;
            }
            return pop_count;
        }

        constexpr int PopCountLSB_U16(uint16_t u16)
        {
            int pop_count = 0;
            while(u16)
            {
                ++pop_count;
                u16 &= u16 ^ -u16;
            }
            return pop_count;
        }

        constexpr int PopCountLSB_U32(uint32_t u32)
        {
            int pop_count = 0;
            while(u32)
            {
                ++pop_count;
                u32 &= u32 ^ -u32;
            }
            return pop_count;
        }

        constexpr int PopCountLSB_U64(uint64_t u64)
        {
            int pop_count = 0;
            while(u64)
            {
                ++pop_count;
                u64 &= u64 ^ -u64;
            }
            return pop_count;
        }

        template <size_t no_bits>
        inline std::string BinaryString(uint64_t raw_bits)
        {
            std::string binary_string(no_bits, '0');
            for(size_t i = 0; i < no_bits; ++i)
            {
                if((raw_bits >> i) & 1)
                {
                    binary_string[no_bits - i - 1] = '1';
                }
            }
            return binary_string;
        }
    };
};

#endif