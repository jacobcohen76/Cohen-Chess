#ifndef COHEN_CHESS_ENGINE_BOARD_H_INCLUDED
#define COHEN_CHESS_ENGINE_BOARD_H_INCLUDED

#include "../hash/zobrist.h"
#include "../types/bitboard.h"
#include "../types/color.h"
#include "../types/direction.h"
#include "../types/key.h"
#include "../types/move_type.h"
#include "../types/move.h"
#include "../types/piece.h"
#include "../types/square.h"
#include "../util/string_util.h"
#include "state_info.h"

#include <cstdint>
#include <string>

namespace cohen_chess
{
    struct Board
    {
        Board();

        void        put(Piece, Square);
        void        remove(Piece, Square);
        void        move(Square, Square);
        void        move(Piece, Square, Square);

        void        make(Move);
        void        unmake(Move, StateInfo&);

        Piece       on(Square) const;
        Piece       capture(Square);

        Bitboard    bitset(Piece) const;

        Bitboard    piece_bitboards[kPieceNB];
        Piece       piece_on_square[kSquareNB];
        StateInfo   info;
        Color       side;
    };

    inline Board::Board() : piece_bitboards(), piece_on_square(), info(), side()
    {
        
    }

    inline void Board::put(Piece pc, Square sq)
    {
        Bitboard sq_bb = SquareBB(sq);
        piece_bitboards[pc] |= sq_bb;
        piece_bitboards[PieceAllColor(pc)] |= sq_bb;
        piece_bitboards[kOccupancy] |= sq_bb;
        piece_on_square[sq] = pc;
        info.zkey ^= ZobristKey(pc, sq);
        if(PieceTypeOf(pc) == kPawn)
        {
            info.pawn_key ^= ZobristKey(pc, sq);
        }
    }

    inline void Board::remove(Piece pc, Square sq)
    {
        Bitboard not_sq_bb = ~SquareBB(sq);
        piece_bitboards[pc] &= not_sq_bb;
        piece_bitboards[PieceAllColor(pc)] &= not_sq_bb;
        piece_bitboards[kOccupancy] &= not_sq_bb;
        piece_on_square[sq] = kPieceNone;
        info.zkey ^= ZobristKey(pc, sq);
        if(PieceTypeOf(pc) == kPawn)
        {
            info.pawn_key ^= ZobristKey(pc, sq);
        }
    }

    inline void Board::move(Square from, Square to)
    {
        put(capture(from), to);
    }

    inline void Board::move(Piece pc, Square from, Square to)
    {
        remove(pc, from);
        put(pc, to);
    }

    inline void Board::make(Move move)
    {
        //if moving from or to a1 flip WhiteOO
        //if moving from or to h1 flip WhiteOOO
        //if moving from or to a8 flip BlackOO
        //if moving from or to h8 flip BlackOOO
        //if moving King remove the current sides castling rights
        // MoveType mv_type = MoveTypeOf(move);
        // Square from = FromSquare(move), to = ToSquare(move);
        // Piece on_from = on(from), on_to = on(to);
        // if(PieceTypeOf(on_from) == kPawn)
        // {
        //     if(to - from == 2 * kNorth || to - from == 2 * kSouth)
        //     {
        //         info.ep_target = to + (side ? kNorth : kSouth);
        //     }
        //     else
        //     {
        //         if(mv_type == kEnPassant)
        //         {
        //             info.captured = this->capture(info.ep_target);
        //         }
        //         else if(mv_type == kPromotion)
        //         {
        //             put(MakePiece(side, PromotedTo(move)), to);
        //         }
        //         info.ep_target = kSquareNone;
        //     }
        //     info.halfmove_clock = 0;
        // }
        // else
        // {
        //     info.ep_target = kSquareNone;
        // }
        // this->move(on_from, from, to);
    }

    inline Piece Board::on(Square sq) const
    {
        return piece_on_square[sq];
    }

    inline Piece Board::capture(Square sq)
    {
        Piece pc = piece_on_square[sq];
        remove(pc, sq);
        return pc;
    }

    inline Bitboard Board::bitset(Piece pc) const
    {
        return piece_bitboards[pc];
    }
}

#endif
