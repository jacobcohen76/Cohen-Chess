#ifndef COHEN_CHESS_TYPES_PIECE_HPP_INCLUDED
#define COHEN_CHESS_TYPES_PIECE_HPP_INCLUDED

#include <types/color.hpp>

#include <cstdint>

namespace cohen_chess
{
    typedef uint8_t PieceType, Piece;

    enum : PieceType
    {
        kPieceTypeNone  = 0,
        kPawn           = 1,
        kKnight         = 2,
        kBishop         = 3,
        kRook           = 4,
        kQueen          = 5,
        kKing           = 6,
        kPieceTypeAll   = 7,
        kPieceTypeNB    = 8,
    };

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

    constexpr Piece MakePiece(PieceType type, Color side)
    {
        return type | (side << 3);
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