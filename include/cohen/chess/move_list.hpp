#ifndef COHEN_CHESS_MOVE_LIST_HPP_INCLUDED
#define COHEN_CHESS_MOVE_LIST_HPP_INCLUDED

#include <cohen/chess/type/move.hpp>

namespace cohen::chess::move_list
{
    struct MoveList
    {
        Move moves[256];
    };
}

#endif
