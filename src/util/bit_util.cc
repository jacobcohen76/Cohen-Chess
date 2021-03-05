#include "bit_util.h"

#include <cstdint>

namespace cohen_chess
{
    namespace bit_util
    {
        uint8_t kU16PopCountTable[65536];

        void InitPopCountTable(uint8_t pop_count_table[], size_t table_size)
        {
            for(size_t i = 0; i < table_size; ++i)
            {
                pop_count_table[i] = PopCountLSB(i);
            }
        }
    };
};