#ifndef COHEN_CHESS_TYPE_PIECE_HPP_INCLUDED
#define COHEN_CHESS_TYPE_PIECE_HPP_INCLUDED

#include <cassert>
#include <cstdint>

#include <type/color.hpp>

namespace cohen_chess::type::piece
{
    using PieceType = uint8_t;

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

    using Piece = uint8_t;

    enum PieceConstant : Piece
    {
        kPieceNone   = (kWhite << 3) | kPieceTypeNone,

        kWhitePawn   = (kWhite << 3) | kPawn,
        kWhiteKnight = (kWhite << 3) | kKnight,
        kWhiteBishop = (kWhite << 3) | kBishop,
        kWhiteRook   = (kWhite << 3) | kRook,
        kWhiteQueen  = (kWhite << 3) | kQueen,
        kWhiteKing   = (kWhite << 3) | kKing,
        kWhiteAll    = (kWhite << 3) | kPieceTypeAll,

        kOccupancy   = (kBlack << 3) | kPieceTypeNone,

        kBlackPawn   = (kBlack << 3) | kPawn,
        kBlackKnight = (kBlack << 3) | kKnight,
        kBlackBishop = (kBlack << 3) | kBishop,
        kBlackRook   = (kBlack << 3) | kRook,
        kBlackQueen  = (kBlack << 3) | kQueen,
        kBlackKing   = (kBlack << 3) | kKing,
        kBlackAll    = (kBlack << 3) | kPieceTypeAll,

        kPieceNB     = 16,
    };

    constexpr Piece MakePiece(Color side, PieceType type) noexcept
    {
        assert(side == kWhite || side == kBlack);
        assert(kPieceTypeNone <= type && type < kPieceTypeNB);
        return (side << 3) | type;
    }

    constexpr PieceType PieceTypeOf(Piece pc) noexcept
    {
        assert(kPieceNone <= pc && pc < kPieceNB);
        return pc & 0b0111;
    }

    constexpr Piece FlipPieceColor(Piece pc) noexcept
    {
        assert(kPieceNone <= pc && pc < kPieceNB);
        return pc ^ 0b1000;
    }

    constexpr Piece PieceAllColor(Piece pc) noexcept
    {
        assert(kPieceNone <= pc && pc < kPieceNB);
        return pc | 0b0111;
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
