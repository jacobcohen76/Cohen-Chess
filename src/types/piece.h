#ifndef COHEN_CHESS_TYPES_PIECE_H_INCLUDED
#define COHEN_CHESS_TYPES_PIECE_H_INCLUDED

#include "color.h"
#include "piece_type.h"

#include <cstdint>

namespace cohen_chess
{
    typedef uint8_t Piece;

    enum : Piece
    {
        kWhitePawn   = (kWhite << 3) | kPawn,
        kWhiteKnight = (kWhite << 3) | kKnight,
        kWhiteBishop = (kWhite << 3) | kBishop,
        kWhiteRook   = (kWhite << 3) | kRook,
        kWhiteQueen  = (kWhite << 3) | kQueen,
        kWhiteKing   = (kWhite << 3) | kKing,
        kWhiteAll    = (kWhite << 3) | kPieceTypeAll,

        kBlackPawn   = (kBlack << 3) | kPawn,
        kBlackKnight = (kBlack << 3) | kKnight,
        kBlackBishop = (kBlack << 3) | kBishop,
        kBlackRook   = (kBlack << 3) | kRook,
        kBlackQueen  = (kBlack << 3) | kQueen,
        kBlackKing   = (kBlack << 3) | kKing,
        kBlackAll    = (kBlack << 3) | kPieceTypeAll,

        kPieceNone   = (kWhite << 3) | kPieceTypeNone,
        kOccupancy   = (kBlack << 3) | kPieceTypeNone,

        kPieceNB     = 16,
    };

    constexpr Piece MakePiece(Color side, PieceType type)
    {
        return (side << 3) | type;
    }

    constexpr PieceType PieceTypeOf(Piece pc)
    {
        return pc & kPieceTypeAll;
    }

    constexpr Piece FlipPieceColor(Piece pc)
    {
        return pc ^ kOccupancy;
    }

    constexpr Piece PieceAllColor(Piece pc)
    {
        return pc | kPieceTypeAll;
    }
}

#endif