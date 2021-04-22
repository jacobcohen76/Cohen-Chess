#ifndef COHEN_CHESS_ENGINE_BOARD_H_INCLUDED
#define COHEN_CHESS_ENGINE_BOARD_H_INCLUDED

#include "../hash/zobrist.h"

#include "../types/bitboard.h"
#include "../types/key.h"
#include "../types/move.h"
#include "../types/piece.h"

namespace cohen_chess
{
    struct StateInfo
    {
        Key             key, pawn_key;
        uint16_t        halfmove_clock;
        Piece           captured;
        bool            check;
    };

    struct Board
    {
        Bitboard        bitboard[kPieceNB];
        Piece           piece[kSquareNB];
        StateInfo       info;

        constexpr void put(Piece, Square);
        constexpr void remove(Piece, Square);
        constexpr void move(Square, Square);

        constexpr Piece on(Square) const;
        constexpr Piece capture(Square);

        constexpr void make(Move);
        constexpr void unmake(Move, const StateInfo&);
    };

    constexpr void Board::put(Piece pc, Square sq)
    {
        bitboard[pc] |= SquareBB(sq);
        bitboard[PieceAllColor(pc)] |= SquareBB(sq);
        bitboard[kOccupancy] |= SquareBB(sq);
        piece[sq] = pc;
        info.key ^= ZobristPieceSquareKey(pc, sq);
        if (PieceTypeOf(pc) == kPawn)
        {
            info.pawn_key ^= ZobristPieceSquareKey(pc, sq);
        }
    }

    constexpr void Board::remove(Piece pc, Square sq)
    {
        bitboard[pc] &= ~SquareBB(sq);
        bitboard[PieceAllColor(pc)] &= ~SquareBB(sq);
        bitboard[kOccupancy] &= ~SquareBB(sq);
        piece[sq] = kPieceNone;
        info.key ^= ZobristPieceSquareKey(pc, sq);
        if (PieceTypeOf(pc) == kPawn)
        {
            info.pawn_key ^= ZobristPieceSquareKey(pc, sq);
        }
    }

    constexpr void Board::move(Square from, Square to)
    {
        put(capture(from), to);
    }

    constexpr Piece Board::on(Square sq) const
    {
        return piece[sq];
    }

    constexpr Piece Board::capture(Square sq)
    {
        Piece pc = piece[sq];
        remove(pc, sq);
        return pc;
    }

    constexpr void Board::make(Move move)
    {

    }

    constexpr void Board::unmake(Move move, const StateInfo& prev)
    {
        

        info = prev;        
    }
}

#endif