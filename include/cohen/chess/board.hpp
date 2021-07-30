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
        constexpr Bitboard bitboard(Piece) const noexcept;

        constexpr Bitboard pawn() const noexcept;
        constexpr Bitboard knight() const noexcept;
        constexpr Bitboard bishop() const noexcept;
        constexpr Bitboard rook() const noexcept;
        constexpr Bitboard queen() const noexcept;
        constexpr Bitboard king() const noexcept;
        constexpr Bitboard occ() const noexcept;

        constexpr Bitboard pawn(Color) const noexcept;
        constexpr Bitboard knight(Color) const noexcept;
        constexpr Bitboard bishop(Color) const noexcept;
        constexpr Bitboard rook(Color) const noexcept;
        constexpr Bitboard queen(Color) const noexcept;
        constexpr Bitboard king(Color) const noexcept;
        constexpr Bitboard occ(Color) const noexcept;

        constexpr Piece on(Square) const noexcept;
        constexpr bool empty(Square) const noexcept;

        constexpr Key zobrist_key() const noexcept;
        constexpr Key pawn_key() const noexcept;
        constexpr Bitboard checks() const noexcept;
        constexpr uint16_t fullmove_clock() const noexcept;
        constexpr uint8_t halfmove_clock() const noexcept;
        constexpr File ep_file() const noexcept;
        constexpr Piece captured() const noexcept;
        constexpr Castling castling() const noexcept;
        constexpr Color side() const noexcept;
        constexpr Square ep_target() const noexcept;

        constexpr void put(Piece, Square) noexcept;
        constexpr void remove(Piece, Square) noexcept;
        constexpr void clear() noexcept;

        constexpr Piece capture(Square) noexcept;
        constexpr void push(Square, Square) noexcept;

        constexpr void make(Move) noexcept;
        constexpr void unmake(Move, const BoardState&) noexcept;

        constexpr void set_state(BoardState) noexcept;

        constexpr void set_side(Color) noexcept;
        constexpr void set_ep_file(File) noexcept;
        constexpr void set_castling(Castling) noexcept;
        constexpr void set_fullmove_clock(uint16_t) noexcept;
        constexpr void set_halfmove_clock(uint8_t) noexcept;

        std::array<Bitboard, kPieceNB> bitboards = {};
        std::array<Piece, kSquareNB> pieces = {};
        BoardState state = {};
    };

    constexpr Bitboard Board::bitboard(Piece piece) const noexcept
    {
        assert(kPieceNone <= piece && piece < kPieceNB);
        return bitboards[piece];
    }

    constexpr Bitboard Board::pawn() const noexcept
    {
        return bitboards[kWhitePawn]
             | bitboards[kBlackPawn];
    }

    constexpr Bitboard Board::knight() const noexcept
    {
        return bitboards[kWhiteKnight]
             | bitboards[kBlackKnight];
    }

    constexpr Bitboard Board::bishop() const noexcept
    {
        return bitboards[kWhiteBishop]
             | bitboards[kBlackBishop];
    }

    constexpr Bitboard Board::rook() const noexcept
    {
        return bitboards[kWhiteRook]
             | bitboards[kBlackRook];
    }

    constexpr Bitboard Board::queen() const noexcept
    {
        return bitboards[kWhiteQueen]
             | bitboards[kBlackQueen];
    }

    constexpr Bitboard Board::king() const noexcept
    {
        return bitboards[kWhiteKing]
             | bitboards[kBlackKing];
    }

    constexpr Bitboard Board::occ() const noexcept
    {
        return bitboards[kOccupancy];
    }

    constexpr Bitboard Board::pawn(Color side) const noexcept
    {
        assert(side == kWhite || side == kBlack);
        return bitboards[MakePiece(side, kPawn)];
    }

    constexpr Bitboard Board::knight(Color side) const noexcept
    {
        assert(side == kWhite || side == kBlack);
        return bitboards[MakePiece(side, kKnight)];
    }

    constexpr Bitboard Board::bishop(Color side) const noexcept
    {
        assert(side == kWhite || side == kBlack);
        return bitboards[MakePiece(side, kBishop)];
    }

    constexpr Bitboard Board::rook(Color side) const noexcept
    {
        assert(side == kWhite || side == kBlack);
        return bitboards[MakePiece(side, kRook)];
    }

    constexpr Bitboard Board::queen(Color side) const noexcept
    {
        assert(side == kWhite || side == kBlack);
        return bitboards[MakePiece(side, kQueen)];
    }

    constexpr Bitboard Board::king(Color side) const noexcept
    {
        assert(side == kWhite || side == kBlack);
        return bitboards[MakePiece(side, kKing)];
    }

    constexpr Bitboard Board::occ(Color side) const noexcept
    {
        assert(side == kWhite || side == kBlack);
        return bitboards[MakePiece(side, kPieceTypeAll)];
    }

    constexpr Piece Board::on(Square sq) const noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return pieces[sq];
    }

    constexpr bool Board::empty(Square sq) const noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return on(sq) == kPieceNone;
    }

    constexpr Key Board::zobrist_key() const noexcept
    {
        return state.zobrist_key;
    }

    constexpr Key Board::pawn_key() const noexcept
    {
        return state.pawn_key;
    }

    constexpr Bitboard Board::checks() const noexcept
    {
        return state.checks;
    }

    constexpr uint16_t Board::fullmove_clock() const noexcept
    {
        return state.fullmove_clock;
    }

    constexpr uint8_t Board::halfmove_clock() const noexcept
    {
        return state.halfmove_clock;
    }

    constexpr File Board::ep_file() const noexcept
    {
        return state.ep_file;
    }

    constexpr Piece Board::captured() const noexcept
    {
        return state.captured;
    }

    constexpr Castling Board::castling() const noexcept
    {
        return state.castling;
    }

    constexpr Color Board::side() const noexcept
    {
        return state.side;
    }

    constexpr Square Board::ep_target() const noexcept
    {
        return state.ep_file == kFileNB ? kSquareNB
            : EnPassantTarget(state.ep_file, state.side);
    }

    constexpr void Board::put(Piece piece, Square sq) noexcept
    {
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
        assert(kA1 <= sq && sq < kSquareNB);
        assert(piece == on(sq));
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

    constexpr Piece Board::capture(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        assert(on(sq));
        Piece piece = on(sq);
        remove(piece, sq);
        return piece;
    }

    constexpr void Board::push(Square from, Square to) noexcept
    {
        assert(kA1 <= from && from < kSquareNB);
        assert(kA1 <= to   &&   to < kSquareNB);
        assert(on(from) && empty(to));
        put(capture(from), to);
    }

    constexpr void Board::make(Move move) noexcept
    {
        assert(move != kMoveNone && move != kMoveNull);
        // Square from = FromSquare(move), to = ToSquare(move);
        // TODO
    }

    constexpr void Board::unmake(Move move, const BoardState& prev_state) noexcept
    {
        assert(move != kMoveNone && move != kMoveNull);
        // Square from = FromSquare(move), to = ToSquare(move);
        // TODO
        state = prev_state;
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

    constexpr void Board::set_fullmove_clock(uint16_t fullmove_clock) noexcept
    {
        state.fullmove_clock = fullmove_clock;
    }

    constexpr void Board::set_halfmove_clock(uint8_t halfmove_clock) noexcept
    {
        state.halfmove_clock = halfmove_clock;
    }
}

namespace cohen::chess
{
    using cohen::chess::board::BoardState;
    using cohen::chess::board::Board;
}

#endif
