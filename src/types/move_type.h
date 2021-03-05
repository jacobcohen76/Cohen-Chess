#ifndef COHEN_CHESS_TYPES_MOVE_TYPE_H_INCLUDED
#define COHEN_CHESS_TYPES_MOVE_TYPE_H_INCLUDED

#include "piece_type.h"

#include <cstdint>

namespace cohen_chess
{
    enum MoveType : uint16_t
    {
        kQuietMove = 0x0000,
        kPromotion = 0x1000,
        kEnPassant = 0x2000,
        kCastling  = 0x3000,
    };
}

#endif