#ifndef COHEN_CHESS_MOVE_GEN_HPP_INCLUDED
#define COHEN_CHESS_MOVE_GEN_HPP_INCLUDED

#include <cohen/chess/type/bitboard.hpp>
#include <cohen/chess/type/move.hpp>
#include <cohen/chess/type/square.hpp>

#include <cohen/chess/attacks.hpp>
#include <cohen/chess/board.hpp>
// #include <cohen/chess/magics.hpp>
#include <cohen/chess/move_list.hpp>

namespace cohen::chess::move_gen
{
    constexpr void FillMoveList(MoveList& move_list,
                                Square    from,
                                Bitboard  to_set,
                                MoveType  type = kQuietMove) noexcept
    {
        while (to_set)
        {
            Square to = PopLSB(to_set);
            move_list.push(MakeMove(from, to, type));
        }
    }

    constexpr void FillMoveList(
        MoveList&                        move_list,
        Bitboard                         from_set,
        Functor<Bitboard(Square)> auto&& gen_fn,
        MoveType                         type = kQuietMove) noexcept
    {
        while (from_set)
        {
            Square   from   = PopLSB(from_set);
            Bitboard to_set = gen_fn(from);
            while (to_set)
            {
                Square to = PopLSB(to_set);
                move_list.push(MakeMove(from, to, type));
            }
        }
    }

    template <Functor<Bitboard(Bitboard, Square)> auto gen_fn>
    constexpr Functor<Bitboard(Square)> auto BindGen(
        Bitboard occ,
        Bitboard mask = kUniverseBB) noexcept
    {
        return [occ, mask](Square sq) -> Bitboard
        {
            return gen_fn(occ, sq) & mask;
        };
    }

    template <Functor<Bitboard(Color, Square)> auto gen_fn>
    constexpr Functor<Bitboard(Square)> auto BindGen(
        Color    side,
        Bitboard mask = kUniverseBB) noexcept
    {
        return [side, mask](Square sq) -> Bitboard
        {
            return gen_fn(side, sq) & mask;
        };
    }

    constexpr void GenMoves(const Board& board, MoveList& move_list) noexcept
    {
        // Color side = board.side();
        // FillMoveList(move_list, board.rooks(side),   BindGen<FancyMagicRookAttacks>(board.occ(), ~board.occ(side)));
        // FillMoveList(move_list, board.bishops(side), BindGen<FancyMagicBishopAttacks>(board.occ(), ~board.occ(side)));
        // FillMoveList(move_list, board.pawns(side),   BindGen<PawnAttacks>(side, board.occ(side ^ kBlack)));
    }
}

namespace cohen::chess
{
    using cohen::chess::move_gen::GenMoves;
}

#endif