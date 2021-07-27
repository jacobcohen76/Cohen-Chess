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
                                Bitboard  to_set) noexcept
    {
        while (to_set)
        {
            Square to = PopLSB(to_set);
            move_list.push(MakeMove(from, to));
        }
    }

    constexpr void FillMoveList(
        MoveList&                        move_list,
        Bitboard                         from_set,
        Functor<Bitboard(Square)> auto&& to_fn) noexcept
    {
        while (from_set)
        {
            Square   from   = PopLSB(from_set);
            Bitboard to_set =  to_fn(from);
            while (to_set)
            {
                Square to = PopLSB(to_set);
                move_list.push(MakeMove(from, to));
            }
        }
    }

    constexpr void GenInSingleCheckMoves(const Board& board, MoveList& moves) noexcept
    {

    }

    constexpr void GenInDoubleCheckMoves(const Board& board,
                                         MoveList&    moves) noexcept
    {
        
    }

    constexpr void GenMoves(const Board& board, MoveList& move_list) noexcept
    {
        if (board.checks())
        {
            if (FlipLSB(board.checks()))
                GenInDoubleCheckMoves(board, move_list);
            else
                GenInSingleCheckMoves(board, move_list);
        }
        else
        {
            FillMoveList(move_list, board.rook(kWhite), [&board](Square sq)
            {
                return BlackMagicRookAttacks(board.occ(), sq) & ~board.occ();
            });
        }
    }
}

namespace cohen::chess
{
    using cohen::chess::move_gen::GenMoves;
}

#endif
