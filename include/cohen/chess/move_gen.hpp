#ifndef COHEN_CHESS_MOVE_GEN_HPP_INCLUDED
#define COHEN_CHESS_MOVE_GEN_HPP_INCLUDED

namespace cohen::chess::move_gen
{
    template <MoveType type>
    constexpr Move* GenMoves(Move* move_list, Bitboard to_set, Square from) noexcept
    {
        while (to_set)
        {
            Square to = PopLSB(to_set);
            *move_list++ = MakeMove(from, to, type);
        }
        return move_list;
    }

    
}

namespace cohen::chess
{
    
}

#endif
