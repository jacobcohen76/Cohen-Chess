#ifndef COHEN_ENGINE_BOARD_HPP_INCLUDED
#define COHEN_ENGINE_BOARD_HPP_INCLUDED

#include <array>
#include <cassert>
#include <cstdint>

#include <cohen/chess/bitboard.hpp>
#include <cohen/chess/zobrist.hpp>
#include <cohen/chess/type/key.hpp>
#include <cohen/chess/type/move.hpp>
#include <cohen/chess/type/piece.hpp>
#include <cohen/chess/type/square.hpp>

namespace cohen::chess::board
{
    struct BoardState
    {
        Key      zobrist_key, pawn_key;
        Bitboard checks;
        uint16_t fullmove_clock;
        uint8_t  halfmove_clock;
        Square   ep_file;
        Piece    captured;
        Castling castling;
        Color    side;
    };

    class Board
    {
    public:
        constexpr Piece on(Square) const noexcept;

        constexpr void put(Piece, Square) noexcept;
        constexpr void remove(Piece, Square) noexcept;
        constexpr void clear() noexcept;

        constexpr void set_side(Color) noexcept;
        constexpr void set_ep_file(File) noexcept;
        constexpr void set_castling(Castling) noexcept;

        constexpr void make(Move) noexcept;
        constexpr void unmake(Move, const BoardState&) noexcept;

    private:
        constexpr Piece capture(Square) noexcept;

        constexpr void push(Square, Square) noexcept;
        constexpr void promote(PieceType, Square) noexcept;
        constexpr void mask_castling(Castling) noexcept;
        constexpr void update_castling(Square) noexcept;

    public:
        std::array<Bitboard, kPieceNB> bitboards = {};
        std::array<Piece, kSquareNB> pieces = {};
        BoardState state = {};
    };

    constexpr Piece Board::on(Square sq) const noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return pieces[sq];
    }

    constexpr void Board::put(Piece pc, Square sq) noexcept
    {
        assert(kPieceNone <= pc && pc < kPieceNB);
        assert(kA1 <= sq && sq < kSquareNB);
        assert(on(sq) == kPieceNone);
        bitboards[pc] |= SquareBB(sq);
        bitboards[PieceAllColor(pc)] |= SquareBB(sq);
        bitboards[kOccupancy] |= SquareBB(sq);
        pieces[sq] = pc;
        state.zobrist_key ^= ZobristPieceSquareKey(pc, sq);
        if (PieceTypeOf(pc) == kPawn)
        {
            state.pawn_key ^= ZobristPieceSquareKey(pc, sq);
        }
    }

    constexpr void Board::remove(Piece pc, Square sq) noexcept
    {
        assert(kPieceNone <= pc && pc < kPieceNB);
        assert(kA1 <= sq && sq < kSquareNB);
        assert(on(sq) == pc);
        bitboards[pc] &= ~SquareBB(sq);
        bitboards[PieceAllColor(pc)] &= ~SquareBB(sq);
        bitboards[kOccupancy] &= ~SquareBB(sq);
        pieces[sq] = kPieceNone;
        state.zobrist_key ^= ZobristPieceSquareKey(pc, sq);
        if (PieceTypeOf(pc) == kPawn)
        {
            state.pawn_key ^= ZobristPieceSquareKey(pc, sq);
        }
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
            state.side ^= kBlack;
        }
    }

    constexpr void Board::set_ep_file(File ep_file) noexcept
    {
        assert(kFileA <= ep_file && ep_file < kFileNB + 1);
        state.zobrist_key ^= ZobristEnPassantKey(FileOf(state.ep_file));
        state.zobrist_key ^= ZobristEnPassantKey(FileOf(ep_file));
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

    constexpr Piece Board::capture(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        Piece  pc = on(sq);
        remove(pc, sq);
        return pc;
    }

    constexpr void Board::push(Square from, Square to) noexcept
    {
        assert(kA1 <= from && from < kSquareNB);
        assert(kA1 <= to   &&   to < kSquareNB);
        put(capture(from), to);
    }

    constexpr void Board::promote(PieceType type, Square sq) noexcept
    {
        assert(kPieceTypeNone <= type && type < kPieceTypeNB);
        assert(kA1 <= sq && sq < kSquareNB);
        put((capture(sq) & kPieceTypeNone) | type, sq);
    }

    constexpr void Board::mask_castling(Castling mask) noexcept
    {
        set_castling(state.castling & mask);
    }

    constexpr void Board::update_castling(Square sq) noexcept
    {
        if (sq == kA1) mask_castling(~kWhiteOO);
        if (sq == kH1) mask_castling(~kWhiteOOO);
        if (sq == kA8) mask_castling(~kBlackOO);
        if (sq == kH8) mask_castling(~kBlackOOO);
    }
}

namespace cohen::chess
{
    using cohen::chess::board::BoardState;
    using cohen::chess::board::Board;
}

#endif
