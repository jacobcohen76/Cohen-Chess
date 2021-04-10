#ifndef COHEN_CHESS_TYPES_CASTLING_RIGHTS_H_INCLUDED
#define COHEN_CHESS_TYPES_CASTLING_RIGHTS_H_INCLUDED

#include "square.h"

#include <cstdint>

namespace cohen_chess
{
    typedef uint8_t CastlingRights;

    enum : CastlingRights
    {
        kCastlingNone   = 0x0,
        kCastlingAll    = 0xF,

        kWhiteOO        = 0x1,
        kWhiteOOO       = 0x2,
        kCastlingWhite  = kWhiteOO | kWhiteOOO,

        kBlackOO        = 0x4,
        kBlackOOO       = 0x8,
        kCastlingBlack  = kBlackOO | kBlackOOO,

        kQueenSide      = kWhiteOO  | kBlackOO,
        kKingSide       = kWhiteOOO | kBlackOOO,

        kCastlingNB     = 16,
    };
}

#endif
