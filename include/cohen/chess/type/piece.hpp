#ifndef COHEN_CHESS_TYPE_PIECE_HPP_INCLUDED
#define COHEN_CHESS_TYPE_PIECE_HPP_INCLUDED

#include <cassert>
#include <cstdint>

#include <cohen/chess/type/color.hpp>

namespace cohen::chess::type::piece
{
    using PieceType = uint8_t;

    enum PieceTypeConstant : PieceType
    {
        kPieceTypeNone = 0,
        kPawn          = 1,
        kKnight        = 2,
        kBishop        = 3,
        kRook          = 4,
        kQueen         = 5,
        kKing          = 6,
        kPieceTypeAll  = 7,
        kPieceTypeNB   = 8,
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

namespace cohen::chess
{
    using cohen::chess::type::piece::PieceType;

    using cohen::chess::type::piece::kPieceTypeNone;
    using cohen::chess::type::piece::kPawn;
    using cohen::chess::type::piece::kKnight;
    using cohen::chess::type::piece::kBishop;
    using cohen::chess::type::piece::kRook;
    using cohen::chess::type::piece::kQueen;
    using cohen::chess::type::piece::kKing;
    using cohen::chess::type::piece::kPieceTypeAll;
    using cohen::chess::type::piece::kPieceTypeNB;

    using cohen::chess::type::piece::Piece;

    using cohen::chess::type::piece::kWhitePawn;
    using cohen::chess::type::piece::kWhiteKnight;
    using cohen::chess::type::piece::kWhiteBishop;
    using cohen::chess::type::piece::kWhiteRook;
    using cohen::chess::type::piece::kWhiteQueen;
    using cohen::chess::type::piece::kWhiteKing;
    using cohen::chess::type::piece::kWhiteAll;
    using cohen::chess::type::piece::kBlackPawn;
    using cohen::chess::type::piece::kBlackKnight;
    using cohen::chess::type::piece::kBlackBishop;
    using cohen::chess::type::piece::kBlackRook;
    using cohen::chess::type::piece::kBlackQueen;
    using cohen::chess::type::piece::kBlackKing;
    using cohen::chess::type::piece::kBlackAll;
    using cohen::chess::type::piece::kPieceNone;
    using cohen::chess::type::piece::kOccupancy;
    using cohen::chess::type::piece::kPieceNB;

    using cohen::chess::type::piece::MakePiece;
    using cohen::chess::type::piece::PieceTypeOf;
    using cohen::chess::type::piece::FlipPieceColor;
    using cohen::chess::type::piece::PieceAllColor;
}

#endif
