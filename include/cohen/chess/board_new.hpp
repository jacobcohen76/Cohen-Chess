#ifndef COHEN_CHESS_BOARD_HPP_INCLUDED
#define COHEN_CHESS_BOARD_HPP_INCLUDED

#include <array>
#include <cassert>
#include <cstdint>

#include <cohen/chess/type/bitboard.hpp>
#include <cohen/chess/type/castling.hpp>
#include <cohen/chess/type/piece.hpp>
#include <cohen/chess/type/key.hpp>
#include <cohen/chess/type/move.hpp>
#include <cohen/chess/zobrist.hpp>

namespace cohen::chess::board
{
    struct BoardState
    {
        Key      zobrist_key, pawn_key;
        Bitboard checks;
        uint16_t fullmove_clock;
        uint8_t  halfmove_clock;
        File     ep_file;
        Piece    captured;
        Castling castling;
        Color    side;
    };

    struct Board
    {
        constexpr Piece on(Square) const noexcept;
        constexpr Piece capture(Square) noexcept;

        constexpr bool empty(Square) const noexcept;

        constexpr void put(Piece, Square) noexcept;
        constexpr void remove(Piece, Square) noexcept;
        constexpr void clear() noexcept;

        constexpr void set_side(Color) noexcept;
        constexpr void set_ep_file(File) noexcept;
        constexpr void set_castling(Castling) noexcept;

        constexpr void make(Move) noexcept;
        constexpr void unmake(Move, const BoardState&) noexcept;

        std::array<Bitboard, kPieceNB> bitboards = {};
        std::array<Piece, kSquareNB> pieces = {};
        BoardState state = {};
    };

    constexpr Piece Board::on(Square sq) const noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return pieces[sq];
    }

    constexpr Piece Board::capture(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        assert(on(sq) != kPieceNone);
        Piece piece = on(sq);
        remove(piece, sq);
        return piece;
    }

    constexpr bool Board::empty(Square sq) const noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return on(sq) == kPieceNone;
    }

    constexpr void Board::put(Piece piece, Square sq) noexcept
    {
        assert(kPawn <= PieceTypeOf(piece) && PieceTypeOf(piece) <= kKing);
        assert(kA1 <= sq && sq < kSquareNB);
        assert(empty(sq));
        bitboards[PieceAllColor(piece)] |= SquareBB(sq);
        bitboards[kOccupancy] |= SquareBB(sq);
        bitboards[piece] |= SquareBB(sq);
        pieces[sq] = piece;
        if (PieceTypeOf(piece) == kPawn)
            state.pawn_key ^= ZobristPieceSquareKey(piece, sq);
        state.zobrist_key  ^= ZobristPieceSquareKey(piece, sq);
    }

    constexpr void Board::remove(Piece piece, Square sq) noexcept
    {
        assert(kPawn <= PieceTypeOf(piece) && PieceTypeOf(piece) <= kKing);
        assert(kA1 <= sq && sq < kSquareNB);
        assert(on(sq));
        bitboards[PieceAllColor(piece)] &= ~SquareBB(sq);
        bitboards[kOccupancy] &= ~SquareBB(sq);
        bitboards[piece] &= ~SquareBB(sq);
        pieces[sq] = kPieceNone;
        if (PieceTypeOf(piece) == kPawn)
            state.pawn_key ^= ZobristPieceSquareKey(piece, sq);
        state.zobrist_key  ^= ZobristPieceSquareKey(piece, sq);
    }

    constexpr void Board::clear() noexcept
    {
        bitboards = {}, pieces = {}, state = {};
    }

    constexpr void Board::set_side(Color side) noexcept
    {
        assert(side == kWhite || side == kBlack);
        if (state.side != side)
        {
            state.zobrist_key ^= ZobristSideKey(side);
            state.side = side;
        }
    }

    constexpr void Board::set_ep_file(File ep_file) noexcept
    {
        assert(kFileA <= ep_file && ep_file < kFileNB + 1);
        state.zobrist_key ^= ZobristEnPassantKey(state.ep_file);
        state.zobrist_key ^= ZobristEnPassantKey(ep_file);
        state.ep_file = ep_file;
    }

    constexpr void Board::set_castling(Castling castling) noexcept
    {
        assert(kCastlingNone <= castling && castling < kCastlingNB);
        state.zobrist_key ^= ZobristCastlingKey(state.castling);
        state.zobrist_key ^= ZobristCastlingKey(castling);
        state.castling = castling;
    }

    constexpr void Board::make(Move move) noexcept
    {
        assert(move != kMoveNone && move != kMoveNull);
        // TODO
    }

    constexpr void Board::unmake(Move move, const BoardState& prev_state) noexcept
    {
        assert(move != kMoveNone && move != kMoveNull);
        // TODO
    }
}

#endif