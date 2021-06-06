#ifndef COHEN_CHESS_TYPE_PIECE_HPP_INCLUDED
#define COHEN_CHESS_TYPE_PIECE_HPP_INCLUDED

#include <cstdint>

#include <type/color.hpp>

namespace cohen_chess::type::piece
{
    using PieceType = int8_t;

    enum PieceTypeConstant : PieceType
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

    using Piece = int8_t;

    enum PieceConstant : Piece
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

    constexpr Piece MakePiece(PieceType type, Color side) noexcept
    {
        return type | (side << 3);
    }

    constexpr PieceType PieceTypeOf(Piece pc) noexcept
    {
        return pc & kPieceTypeAll;
    }

    constexpr Piece FlipPieceColor(Piece pc) noexcept
    {
        return pc ^ kOccupancy;
    }

    constexpr Piece PieceAllColor(Piece pc) noexcept
    {
        return pc | kPieceTypeAll;
    }
}

namespace cohen_chess
{
    using type::piece::PieceType;

    using type::piece::kPieceTypeNone;
    using type::piece::kPawn;
    using type::piece::kKnight;
    using type::piece::kBishop;
    using type::piece::kRook;
    using type::piece::kQueen;
    using type::piece::kKing;
    using type::piece::kPieceTypeAll;
    using type::piece::kPieceTypeNB;

    using type::piece::Piece;

    using type::piece::kWhitePawn;
    using type::piece::kWhiteKnight;
    using type::piece::kWhiteBishop;
    using type::piece::kWhiteRook;
    using type::piece::kWhiteQueen;
    using type::piece::kWhiteKing;
    using type::piece::kWhiteAll;
    using type::piece::kBlackPawn;
    using type::piece::kBlackKnight;
    using type::piece::kBlackBishop;
    using type::piece::kBlackRook;
    using type::piece::kBlackQueen;
    using type::piece::kBlackKing;
    using type::piece::kBlackAll;
    using type::piece::kPieceNone;
    using type::piece::kOccupancy;
    using type::piece::kPieceNB;

    using type::piece::MakePiece;
    using type::piece::PieceTypeOf;
    using type::piece::FlipPieceColor;
    using type::piece::PieceAllColor;
}

#endif