#ifndef COHEN_CHESS_IO_ASCII_BOARD_H_INCLUDED
#define COHEN_CHESS_IO_ASCII_BOARD_H_INCLUDED

#include "../engine/board.h"
#include "../types/bitboard.h"
#include "../types/rank.h"
#include "../types/color.h"
#include "../types/file.h"
#include "../types/square.h"

#include <iostream>
#include <cstdint>
#include <string>

namespace cohen_chess
{
    template <Color side = kWhite, char empty = '.', char space = ' '>
    class AsciiBoard
    {
        static_assert(side == kWhite || side == kBlack, "Side must be either kWhite or kBlack");

    public:
        constexpr AsciiBoard() = default;

        constexpr AsciiBoard(Bitboard bb, char ch)
        {
            set_bb(bb, ch);
        }

        constexpr AsciiBoard(const Board& board)
        {
            set_board(board);
        }

        constexpr void set(Square sq, char ch)
        {
            data[index(sq)] = ch;
        }

        constexpr void set_bb(Bitboard bb, char ch)
        {
            while (bb)
            {
                set(PopLSB(bb), ch);
            }
        }

        constexpr void set_board(const Board& board)
        {
            clear();
            for (Square sq = kA1; sq < kSquareNB; ++sq)
            {
                if (board.on(sq))
                {
                    set(sq, PieceChar(board.on(sq)));
                }
            }
        }

        constexpr void clear()
        {
            data = kInitialData;
        }

        constexpr auto begin()
        {
            return std::begin(data);
        }

        constexpr auto begin() const
        {
            return std::begin(data);
        }

        constexpr auto end()
        {
            return std::end(data);
        }

        constexpr auto end() const
        {
            return std::end(data);
        }

    private:
        static constexpr std::array<char, 128> kInitialData =
        {
            empty, space, empty, space, empty, space, empty, space, empty, space, empty, space, empty, space, empty, '\n',
            empty, space, empty, space, empty, space, empty, space, empty, space, empty, space, empty, space, empty, '\n',
            empty, space, empty, space, empty, space, empty, space, empty, space, empty, space, empty, space, empty, '\n',
            empty, space, empty, space, empty, space, empty, space, empty, space, empty, space, empty, space, empty, '\n',
            empty, space, empty, space, empty, space, empty, space, empty, space, empty, space, empty, space, empty, '\n',
            empty, space, empty, space, empty, space, empty, space, empty, space, empty, space, empty, space, empty, '\n',
            empty, space, empty, space, empty, space, empty, space, empty, space, empty, space, empty, space, empty, '\n',
            empty, space, empty, space, empty, space, empty, space, empty, space, empty, space, empty, space, empty, '\n',
        };

        constexpr size_t index(Square sq) const
        {
            Rank rank = RelativeRank(RankOf(sq), side ^ kBlack);
            File file = RelativeFile(FileOf(sq), side);
            return 16 * rank + 2 * file;
        }

        std::array<char, 128> data = kInitialData;
    };

    template <Color side, char empty, char space>
    inline std::ostream& operator <<(std::ostream& os, const AsciiBoard<side, empty, space>& ascii_board)
    {
        return os << std::string_view(std::cbegin(ascii_board), std::cend(ascii_board));
    }
}

#endif