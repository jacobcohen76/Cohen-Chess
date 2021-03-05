#ifndef COHEN_CHESS_IO_ASCII_BOARD_H_INCLUDED
#define COHEN_CHESS_IO_ASCII_BOARD_H_INCLUDED

#include "../engine/board.h"
#include "../types/bitboard.h"
#include "../types/rank.h"
#include "../types/color.h"
#include "../types/file.h"
#include "../types/square.h"

#include <cstdint>
#include <string>

#include <iostream>

namespace cohen_chess
{  
    namespace io
    {
        template<Color side = kWhite>
        std::string AsciiBoard(Bitboard bb, const char* occ_chars = ".1")
        {
            std::string ascii_board(127, ' ');
            size_t i = -1;
            for(Rank r = kRank8; r >= kRank1; --r)
            {
                for(File f = kFileA; f <= kFileH; ++f)
                {
                    Square sq = RelativeSquare(side, MakeSquare(r, f));
                    ascii_board[++i] = occ_chars[(bb >> sq) & 1];
                    if(f < kFileH)
                    {
                        ascii_board[++i] = ' ';
                    }
                }
                if(r > kRank1)
                {
                    ascii_board[++i] = '\n';
                }
            }
            return ascii_board;
        }

        template<Color side = kWhite>
        std::string AsciiBoard(const Board& board, const char* piece_chars = ".PNBRQKC1pnbrqkc")
        {
            std::string ascii_board(127, ' ');
            size_t i = -1;
            for(Rank r = kRank8; r >= kRank1; --r)
            {
                for(File f = kFileA; f <= kFileH; ++f)
                {
                    Square sq = RelativeSquare(side, MakeSquare(r, f));
                    ascii_board[++i] = piece_chars[board.on(sq)];
                    if(f < kFileH)
                    {
                        ascii_board[++i] = ' ';
                    }
                }
                if(r > kRank1)
                {
                    ascii_board[++i] = '\n';
                }
            }
            return ascii_board;
        }
    };
}

#endif