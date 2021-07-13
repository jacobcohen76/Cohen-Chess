#ifndef COHEN_CHESS_MOVE_GEN_HPP_INCLUDED
#define COHEN_CHESS_MOVE_GEN_HPP_INCLUDED

namespace cohen::chess::move_gen
{
    template <MoveType type>
    constexpr void GenMoves(Square from, Bitboard to_set) noexcept
    {
        while (to_set)
        {
            Square to = PopLSB(to_set);
            *move_list++ = MakeMove(type, from, to);
        }
    }
}

namespace cohen::chess
{
    
}

#endif
