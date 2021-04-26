#ifndef COHEN_CHESS_IO_FEN_H_INCLUDED
#define COHEN_CHESS_IO_FEN_H_INCLUDED

#include "../engine/board.h"

namespace cohen_chess
{
    namespace fen
    {
        constexpr CastlingRights CastlingRightsBit(char ch)
        {
            switch (ch)
            {
                case 'K': return kWhiteOO;
                case 'Q': return kWhiteOOO;
                case 'k': return kBlackOO;
                case 'q': return kBlackOOO;
                default:  return kCastlingNone;
            }
        } 

    }

    constexpr void LoadFEN(std::string_view fen, Board& board)
    {
        auto itr = fen.begin();
        while (itr < fen.end())
        {

        }
    }

    constexpr CastlingRights CastlingRightsFEN(std::string_view cr_fen)
    {
        CastlingRights cr = kCastlingNone;
        for (const auto ch : cr_fen)
        {
            switch (ch)
            {
                case 'K': cr |= kWhiteOO;   break;
                case 'Q': cr |= kWhiteOOO;  break;
                case '-': return kCastlingNone;
            }
        }
    }
}

#endif