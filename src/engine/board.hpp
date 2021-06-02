#ifndef COHEN_CHESS_ENGINE_BOARD_HPP_INCLUDED
#define COHEN_CHESS_ENGINE_BOARD_HPP_INCLUDED

#include <hash/zobrist.hpp>
#include <types/bitboard.hpp>
#include <types/key.hpp>
#include <types/move.hpp>
#include <types/piece.hpp>

namespace cohen_chess
{
    struct BoardState
    {
        constexpr void  set_side(Color);
        constexpr void  set_ep_file(File);
        constexpr void  set_castling_rights(CastlingRights);
        constexpr void  mask_castling_rights(CastlingRights);
        constexpr void  update_castling_rights(Square, Square);

        Key             key, pawn_key;
        Bitboard        checks;
        uint16_t        halfmove_clock;
        uint16_t        fullmove_count;
        Piece           captured;
        File            ep_file;
        CastlingRights  castling_rights;
        Color           side;
    };

    struct Board
    {
        constexpr Piece on(Square) const;
        constexpr void  put(Piece, Square);

        constexpr void  clear();
        constexpr void  make(Move);
        constexpr void  unmake(Move, const BoardState&);

    private:
        constexpr Piece capture(Square);
        constexpr void  emplace(Piece, Square);
        constexpr void  remove(Piece, Square);
        constexpr void  promote(PieceType, Square);
        constexpr void  push(Square, Square);

    public:
        Bitboard        bitboards[kPieceNB];
        Piece           pieces[kSquareNB];
        BoardState      state;
    };

    constexpr void BoardState::set_side(Color color)
    {
        if (side != color)
        {
            key ^= kZobristSideKey;
        }
        side = color;
    }

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

    constexpr Piece Board::on(Square sq) const
    {
        return pieces[sq];
    }

    constexpr void Board::put(Piece pc, Square sq)
    {
        if (on(sq))
        {
            remove(on(sq), sq);
        }
        emplace(pc, sq);
    }

    constexpr void Board::clear()
    {
        std::fill(bitboards, bitboards + kPieceNB, kEmptyBB);
        std::fill(pieces, pieces + kSquareNB, kPieceNone);
        state = {};
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
                    promote(PromotedTo(move), from);
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
        state.key ^= kZobristSideKey;
        ++state.halfmove_clock;
    }

    constexpr void Board::unmake(Move move, const BoardState& prev)
    {
        Square from = FromSquare(move), to = ToSquare(move);
        if (MoveTypeOf(move) == kPromotion)
        {
            promote(kPawn, to);
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

    constexpr Piece Board::capture(Square sq)
    {
        Piece pc = on(sq);
        remove(pc, sq);
        return pc;
    }

    constexpr void Board::emplace(Piece pc, Square sq)
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

    constexpr void Board::promote(PieceType piece_type, Square sq)
    {
        Piece promoted = capture(sq);
        promoted &= kPieceTypeNone;
        promoted |= piece_type;
        put(promoted, sq);
    }

    constexpr void Board::push(Square from, Square to)
    {
        put(capture(from), to);
    }
}

#endif