#ifndef COHEN_CHESS_MOVE_GEN_HPP_INCLUDED
#define COHEN_CHESS_MOVE_GEN_HPP_INCLUDED

#include <cohen/chess/type/bitboard.hpp>
#include <cohen/chess/type/move.hpp>
#include <cohen/chess/type/square.hpp>
#include <cohen/chess/board.hpp>
#include <cohen/chess/move_list.hpp>

namespace cohen::chess::move_gen
{
    constexpr void FillMoveList(MoveList& move_list,
                                Bitboard  to_set,
                                Square    from,
                                MoveType  type) noexcept
    {
        while (to_set)
        {
            Square to = PopLSB(to_set);
            move_list.push(MakeMove(from, to, type));
        }
    }

    constexpr void GenMoves(const Board& board, MoveList& move_list) noexcept
    {
        
    }
}

namespace cohen::chess
{
    
}

#endif
