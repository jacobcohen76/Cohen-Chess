#ifndef COHEN_CHESS_MOVE_GEN_HPP_INCLUDED
#define COHEN_CHESS_MOVE_GEN_HPP_INCLUDED

#include <cohen/chess/type/bitboard.hpp>
#include <cohen/chess/type/move.hpp>
#include <cohen/chess/type/square.hpp>

#include <cohen/chess/attacks.hpp>
#include <cohen/chess/board.hpp>
#include <cohen/chess/magics.hpp>
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
        Functor<Bitboard(Square)> auto&& to_fn,
        MoveType                         type = kQuietMove) noexcept
    {
        while (from_set)
        {
            Square   from   = PopLSB(from_set);
            Bitboard to_set =  to_fn(from);
            while (to_set)
            {
                Square to = PopLSB(to_set);
                move_list.push(MakeMove(from, to, type));
            }
        }
    }

    template <Functor<Bitboard(Bitboard, Square)> auto moves_fn>
    constexpr Functor<Bitboard(Square)> auto SlidingMoves(const Board& board) noexcept
    {
        return [&board](Square sq) -> Bitboard
        {
            return moves_fn(board.occ(), sq);
        };
    }

    constexpr void GenMoves(const Board& board, MoveList& move_list) noexcept
    {
        Color side = board.side();
        // FillMoveList(move_list, board.rook(side), [&](Square sq)
        // {
        //     return BlackMagicRookAttacks(board.occ(), sq) & ~board.occ(side);
        // });
        FillMoveList(move_list, board.rook(side),   SlidingMoves<BlackMagicRookAttacks>(board));
        FillMoveList(move_list, board.bishop(side), SlidingMoves<BlackMagicBishopAttacks>(board));
    }
}

namespace cohen::chess
{
    using cohen::chess::move_gen::GenMoves;
}

#endif
