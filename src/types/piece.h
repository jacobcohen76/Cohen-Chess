#ifndef COHEN_CHESS_TYPES_PIECE_H_INCLUDED
#define COHEN_CHESS_TYPES_PIECE_H_INCLUDED

#include "color.h"
#include "piece_type.h"

#include <cstdint>

namespace cohen_chess
{
    enum Piece : uint8_t
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
        return Piece((uint8_t(side) << 3) | uint8_t(type));
    }

    constexpr PieceType TypeOf(Piece pc)
    {
        return PieceType(pc & kPieceTypeAll);
    }

    constexpr Piece FlipColor(Piece pc)
    {
        return Piece(pc ^ kOccupancy);
    }

    constexpr Piece AllColor(Piece pc)
    {
        return Piece(pc | kPieceTypeAll);
    }

    inline Piece& operator++(Piece& op)
    {
        return op = Piece(uint8_t(op) + 1);
    }

    inline Piece& operator--(Piece& op)
    {
        return op = Piece(uint8_t(op) - 1);
    }

    constexpr Piece operator+(Piece op)
    {
        return Piece(+uint8_t(op));
    }

    constexpr Piece operator-(Piece op)
    {
        return Piece(-uint8_t(op));
    }

    constexpr Piece operator~(Piece op)
    {
        return Piece(~uint8_t(op));
    }

    template<typename Integral>
    constexpr Piece operator<<(Piece op1, Integral op2)
    {
        return Piece(uint8_t(op1) << op2);
    }

    template<typename Integral>
    constexpr Piece operator>>(Piece op1, Integral op2)
    {
        return Piece(uint8_t(op1) >> op2);
    }

    constexpr Piece operator&(Piece op1, Piece op2)
    {
        return Piece(uint8_t(op1) & uint8_t(op2));
    }

    constexpr Piece operator^(Piece op1, Piece op2)
    {
        return Piece(uint8_t(op1) ^ uint8_t(op2));
    }

    constexpr Piece operator|(Piece op1, Piece op2)
    {
        return Piece(uint8_t(op1) ^ uint8_t(op2));
    }

    template<typename Integral>
    inline Piece& operator+=(Piece& lhs, Integral rhs)
    {
        return lhs = Piece(uint8_t(lhs) + rhs);
    }

    template<typename Integral>
    inline Piece& operator-=(Piece& lhs, Integral rhs)
    {
        return lhs = Piece(uint8_t(lhs) - rhs);
    }

    template<typename Integral>
    inline Piece& operator*=(Piece& lhs, Integral rhs)
    {
        return lhs = Piece(uint8_t(lhs) * rhs);
    }

    template<typename Integral>
    inline Piece& operator/=(Piece& lhs, Integral rhs)
    {
        return lhs = Piece(uint8_t(lhs) / rhs);
    }

    template<typename Integral>
    inline Piece& operator%=(Piece& lhs, Integral rhs)
    {
        return lhs = Piece(uint8_t(lhs) % rhs);
    }

    template<typename Integral>
    inline Piece& operator<<=(Piece& lhs, Integral rhs)
    {
        return lhs = Piece(uint8_t(lhs) << rhs);
    }

    template<typename Integral>
    inline Piece& operator>>=(Piece& lhs, Integral rhs)
    {
        return lhs = Piece(uint8_t(lhs) >> rhs);
    }

    template<typename Integral>
    inline Piece& operator&=(Piece& lhs, Integral rhs)
    {
        return lhs = Piece(uint8_t(lhs) & rhs);
    }

    template<typename Integral>
    inline Piece& operator^=(Piece& lhs, Integral rhs)
    {
        return lhs = Piece(uint8_t(lhs) ^ rhs);
    }

    template<typename Integral>
    inline Piece& operator|=(Piece& lhs, Integral rhs)
    {
        return lhs = Piece(uint8_t(lhs) | rhs);
    }
}

#endif