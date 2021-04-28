#ifndef COHEN_CHESS_IO_ASCII_BOARD_H_INCLUDED
#define COHEN_CHESS_IO_ASCII_BOARD_H_INCLUDED

#include "../io/algebraic_notation.h"

#include "../types/bitboard.h"
#include "../types/color.h"

#include <concepts>
#include <cstdint>
#include <string>
#include <string_view>

#include <iostream>

namespace cohen_chess
{
    namespace ascii_board
    {
        enum AsciiBoardFlag
        {
            kFlagsNone  = 0x00,
            kFileNorth  = 0x01,
            kFileSouth  = 0x02,
            kRankEast   = 0x04,
            kRankWest   = 0x08,
            kNoSpace    = 0x10,
        };

        static constexpr auto kSpace    = ' ';
        static constexpr auto kNewLine  = '\n';
        static constexpr size_t kNumRanks = 8;
        static constexpr size_t kNumFiles = 8;

        constexpr size_t RankSize(int flags)
        {
            return kNumRanks + !!(flags & kFileNorth) + !!(flags & kFileSouth);
        }

        constexpr size_t FileSize(int flags)
        {
            return (kNumFiles + !!(flags & kRankEast) + !!(flags & kRankWest)) << 1;
        }
        
        constexpr size_t BoardSize(int flags)
        {
            return RankSize(flags) * FileSize(flags);
        }

        template <int flags>
        constexpr size_t RankIndex(Rank rank)
        {
            return FileSize(flags) * (rank + !!(flags & kFileNorth));
        }

        template <int flags>
        constexpr size_t FileIndex(File file)
        {
            return (file + !!(flags & kRankWest)) << 1;
        }

        template <int flags>
        constexpr size_t SquareIndex(Square sq)
        {
            return RankIndex<flags>(RankOf(sq)) + FileIndex<flags>(FileOf(sq));
        }

        template <int flags = kFlagsNone>
        inline std::string EmptyAsciiBoard(char empty_char)
        {
            std::string ascii_board(BoardSize(flags), 0);
            size_t i = -1;
            if constexpr (flags & kFileNorth)
            {
                if constexpr (flags & kRankWest)
                {
                    ascii_board[++i] = kSpace;
                    ascii_board[++i] = kSpace;
                }
                for (File file = kFileA; file < kFileNB; ++file)
                {
                    ascii_board[++i] = FileChar(file);
                    ascii_board[++i] = kSpace;
                }
                if constexpr (flags & kRankEast)
                {
                    ascii_board[++i] = kSpace;
                }
                ascii_board[i] = kNewLine;
            }
            for (Rank rank = kRank1; rank < kRankNB; ++rank)
            {
                std::cout << ascii_board << std::endl;
                if constexpr (flags & kRankWest)
                {
                    ascii_board[++i] = RankChar(rank);
                    ascii_board[++i] = kSpace;
                }
                for (File file = kFileA; file < kFileNB; ++file)
                {
                    ascii_board[++i] = empty_char;
                    ascii_board[++i] = kSpace;
                    std::cout << ascii_board << std::endl;
                    std::cout << int(file) << std::endl;
                }
                if constexpr (flags & kRankWest)
                {
                    ascii_board[++i] = RankChar(rank);
                }
                ascii_board[++i] = kNewLine;
            }
            if constexpr (flags & kFileSouth)
            {
                if constexpr (flags & kRankWest)
                {
                    ascii_board[++i] = kSpace;
                    ascii_board[++i] = kSpace;
                }
                for (File file = kFileA; file < kFileNB; ++file)
                {
                    ascii_board[++i] = FileChar(file);
                    ascii_board[++i] = kSpace;
                }
                if constexpr (flags & kRankEast)
                {
                    ascii_board[++i] = kSpace;
                }
                ascii_board[i] = kNewLine;
            }
            return ascii_board;
        }
    }
};

#endif