#ifndef COHEN_CHESS_MOVE_GEN_HPP_INCLUDED
#define COHEN_CHESS_MOVE_GEN_HPP_INCLUDED

#include <cohen/chess/type/bitboard.hpp>
#include <cohen/chess/type/move.hpp>
#include <cohen/chess/type/square.hpp>

namespace cohen::chess::move_gen
{
    constexpr Move* FillMoves(Move*    moves,
                              Bitboard to_set,
                              Square   from,
                              MoveType type) noexcept
    {
        while (to_set)
        {
            Square to = PopLSB(to_set);
            *moves++  = MakeMove(from, to, type);
        }
        return moves;
    }

    
}

namespace cohen::chess
{
    
}

#endif
