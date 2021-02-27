#ifndef COHEN_CHESS_HASH_ZOBRIST_H_INCLUDED
#define COHEN_CHESS_HASH_ZOBRIST_H_INCLUDED

#include "../types/castling_rights.h"
#include "../types/file.h"
#include "../types/key.h"
#include "../types/piece.h"
#include "../types/square.h"

#include <cstdint>

namespace cohen_chess
{
    namespace zobrist
    {
        extern Key   kPieceOnSquareKeys[kPieceNB][kSquareNB];
        extern Key  kCastlingRightsKeys[kCastlingNB];
        extern Key kEnPassantFileTarget[kFileNB];

        void InitPieceOnSquareKeys(uint64_t (*)());
        void InitCastlingRightsKeys(uint64_t (*)());
        void InitEnPassantFileTargetKeys(uint64_t (*)());
    };

    inline Key ZobristKey(Piece pc, Square sq)
    {
        return zobrist::kPieceOnSquareKeys[pc][sq];
    }

    inline Key ZobristKey(CastlingRights cr)
    {
        return zobrist::kCastlingRightsKeys[cr];
    }

    inline Key ZobristKey(File f)
    {
        return zobrist::kEnPassantFileTarget[f];
    }
};

#endif