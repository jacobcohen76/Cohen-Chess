#include "initializer.h"

#include "bit_util.h"
#include "../hash/zobrist.h"
#include "../types/bitboard.h"
#include "../types/direction.h"

namespace cohen_chess
{
    void Init()
    {
        bit_util::Init();
        direction::Init();
        bitboard::Init();
    }
}