#ifndef COHEN_CHESS_ENGINE_STATE_INFO_H_INCLUDED
#define COHEN_CHESS_ENGINE_STATE_INFO_H_INCLUDED

#include "../types/castling_rights.h"
#include "../types/key.h"
#include "../types/square.h"

#include <cstdint>

namespace cohen_chess
{
    struct StateInfo
    {
        Key             zkey, pawn_key;
        uint16_t        halfmove_clock, plies_from_null;
        CastlingRights  castling_rights;
        Square          ep_target;
        Piece           captured;
        bool            in_check;

        StateInfo();
    };

    inline StateInfo::StateInfo()
    {
        zkey            = kKeyZero;
        pawn_key        = kKeyZero;
        halfmove_clock  = 0;
        plies_from_null = 0;
        ep_target       = kSquareNone;
        captured        = kPieceNone;
        in_check        = false;
    }
};

#endif
