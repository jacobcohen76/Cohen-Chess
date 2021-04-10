#ifndef COHEN_CHESS_IO_BIT_IO_H_INCLUDED
#define COHEN_CHESS_IO_BIT_IO_H_INCLUDED

#include <cstdint>
#include <string>

namespace cohen_chess
{
    namespace io
    {
        template <bool lowercase = false>
        constexpr char HexCharacter(uint64_t nibble)
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
}

#endif