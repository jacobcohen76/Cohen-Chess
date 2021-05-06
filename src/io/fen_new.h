#ifndef COHEN_CHESS_IO_FEN_H_INCLUDED
#define COHEN_CHESS_IO_FEN_H_INCLUDED

#include "../engine/board.h"

#include <string_view>

namespace cohen_chess
{
    constexpr CastlingRights FenCastlingRightsBit(char ch)
    {
        switch (ch)
        {
            case 'K': return kWhiteOOO;
            case 'Q': return kWhiteOO;
            case 'k': return kBlackOOO;
            case 'q': return kBlackOO;
            default:  return kCastlingNone;
        }
    }

    constexpr CastlingRights FenCastlingRights(std::string_view fen_cr)
    {
        CastlingRights cr = kCastlingNone;
        for (const auto ch : fen_cr)
        {
            cr |= FenCastlingRightsBit(ch);
        }
        return cr;
    }
    
    constexpr bool SetFenPosition(std::string_view fen, const Board& board)
    {
        
        return true;
    }
}

#endif