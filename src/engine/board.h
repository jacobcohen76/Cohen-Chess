#ifndef COHEN_CHESS_ENGINE_BOARD_H_INCLUDED
#define COHEN_CHESS_ENGINE_BOARD_H_INCLUDED

#include "../hash/zobrist.h"

#include "../types/bitboard.h"
#include "../types/key.h"
#include "../types/move.h"
#include "../types/piece.h"

namespace cohen_chess
{
    struct BoardState
    {
        Key             key, pawn_key;
        Bitboard        checks;
        uint16_t        halfmove_clock;
        uint16_t        fullmove_count;
        Piece           captured;
        File            ep_file;
        CastlingRights  castling_rights;
        Color           side;

        constexpr void set_ep_file(File);
        constexpr void set_castling_rights(CastlingRights);
        constexpr void mask_castling_rights(CastlingRights);
        constexpr void update_castling_rights(Square, Square);
    };

    struct Board
    {
        Bitboard        bitboards[kPieceNB];
        Piece           pieces[kSquareNB];
        BoardState      state;

        constexpr void make(Move);
        constexpr void unmake(Move, const BoardState&);

        constexpr void clear();

        constexpr void put(Piece, Square);
        constexpr void push(Square, Square);
        constexpr void promote(Piece, Square);
        constexpr void remove(Piece, Square);
        constexpr void remove(Square);

        constexpr Piece capture(Square);
        constexpr Piece on(Square) const;
    };

    constexpr void BoardState::set_ep_file(File file)
    {
        key ^= ZobristEnPassantKey(ep_file);
        key ^= ZobristEnPassantKey(file);
        ep_file = file;
    }

    constexpr void BoardState::set_castling_rights(CastlingRights cr)
    {
        key ^= ZobristCastlingKey(castling_rights);
        key ^= ZobristCastlingKey(cr);
        castling_rights = cr;
    }

    constexpr void BoardState::mask_castling_rights(CastlingRights mask)
    {
        set_castling_rights(castling_rights & mask);
    }

    constexpr void BoardState::update_castling_rights(Square from, Square to)
    {
        if (from == kA1 || to == kA1)
            mask_castling_rights(~kWhiteOO);
        if (from == kH1 || to == kH1)
            mask_castling_rights(~kWhiteOOO);
        if (from == kA8 || to == kA8)
            mask_castling_rights(~kBlackOO);
        if (from == kH8 || to == kH8)
            mask_castling_rights(~kBlackOOO);
    }

    constexpr void Board::make(Move move)
    {
        Square from = FromSquare(move), to = ToSquare(move);
        if (on(to))
        {
            state.captured = capture(to);
            state.halfmove_clock = -1;
        }
        if (PieceTypeOf(on(from)) == kPawn)
        {
            if (SquareRankDistance(from, to) == 2)
            {
                state.set_ep_file(FileOf(from));
            }
            else
            {
                if (MoveTypeOf(move) == kPromotion)
                {
                    promote(MakePiece(PromotedTo(move), state.side), from);
                }
                else if (MoveTypeOf(move) == kEnPassant)
                {
                    capture(MakeSquare(RankOf(to), state.ep_file));
                }
                state.set_ep_file(kFileNB);
            }
            state.halfmove_clock = -1;
        }
        else
        {
            if (PieceTypeOf(on(from)) == kKing)
            {
                if (MoveTypeOf(move) == kCastling)
                {
                    if (from > to)
                    {
                        push(RelativeSquareRank(kA1, state.side), RelativeSquareRank(kD1, state.side));
                    }
                    else
                    {
                        push(RelativeSquareRank(kH1, state.side), RelativeSquareRank(kF1, state.side));
                    }
                }
                state.mask_castling_rights(~CastlingRightsSide(state.side));
            }
            state.set_ep_file(kFileNB);
        }
        push(from, to);
        state.update_castling_rights(from, to);
        state.side ^= kBlack;
        state.key ^= kZobristBlackKey;
        ++state.halfmove_clock;
    }

    constexpr void Board::unmake(Move move, const BoardState& prev)
    {
        Square from = FromSquare(move), to = ToSquare(move);
        if (MoveTypeOf(move) == kPromotion)
        {
            promote(MakePiece(kPawn, prev.side), to);
        }
        else if (MoveTypeOf(move) == kEnPassant)
        {
            put(MakePiece(kPawn, prev.side ^ kBlack), MakeSquare(RankOf(to), prev.ep_file));
        }
        else if (MoveTypeOf(move) == kCastling)
        {
            if (from > to)
            {
                push(RelativeSquareRank(kD1, prev.side), RelativeSquareRank(kA1, prev.side));
            }
            else
            {
                push(RelativeSquareRank(kF1, prev.side), RelativeSquareRank(kH1, prev.side));
            }
        }
        push(to, from);
        put(prev.captured, to);
        state = prev;
    }

    constexpr void Board::clear()
    {
        std::fill(bitboards, bitboards + kPieceNB, kEmptyBB);
        std::fill(pieces, pieces + kSquareNB, kPieceNone);
        state = {};
    }

    constexpr void Board::put(Piece pc, Square sq)
    {
        bitboards[pc] |= SquareBB(sq);
        bitboards[PieceAllColor(pc)] |= SquareBB(sq);
        bitboards[kOccupancy] |= SquareBB(sq);
        pieces[sq] = pc;
        state.key ^= ZobristPieceSquareKey(pc, sq);
        if (PieceTypeOf(pc) == kPawn)
        {
            state.pawn_key ^= ZobristPieceSquareKey(pc, sq);
        }
    }

    constexpr void Board::push(Square from, Square to)
    {
        put(capture(from), to);
    }

    constexpr void Board::promote(Piece pc, Square sq)
    {
        remove(sq);
        put(pc, sq);
    }

    constexpr void Board::remove(Piece pc, Square sq)
    {
        bitboards[pc] &= ~SquareBB(sq);
        bitboards[PieceAllColor(pc)] &= ~SquareBB(sq);
        bitboards[kOccupancy] &= ~SquareBB(sq);
        pieces[sq] = kPieceNone;
        state.key ^= ZobristPieceSquareKey(pc, sq);
        if (PieceTypeOf(pc) == kPawn)
        {
            state.pawn_key ^= ZobristPieceSquareKey(pc, sq);
        }
    }

    constexpr void Board::remove(Square sq)
    {
        remove(on(sq), sq);
    }

    constexpr Piece Board::capture(Square sq)
    {
        Piece pc = on(sq);
        remove(pc, sq);
        return pc;
    }

    constexpr Piece Board::on(Square sq) const
    {
        return pieces[sq];
    }
}

#endif