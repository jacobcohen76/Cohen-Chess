#include "initializer.h"

#include "../hash/zobrist.h"
#include "../types/bitboard.h"
#include "../types/direction.h"

namespace cohen_chess
{
    void Init()
    {
        direction::Init();
        bitboard::Init();
    }
}