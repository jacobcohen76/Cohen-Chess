#ifndef COHEN_CHESS_IO_ASCII_BOARD_HPP_INCLUDED
#define COHEN_CHESS_IO_ASCII_BOARD_HPP_INCLUDED

#include <engine/board.hpp>
#include <type/bitboard.hpp>
#include <type/rank.hpp>
#include <type/color.hpp>
#include <type/file.hpp>
#include <type/square.hpp>

#include <iostream>
#include <cstdint>
#include <string>

namespace cohen_chess::io::ascii_board
{
    class AsciiBoard
    {
    public:
        constexpr AsciiBoard() = default;
        constexpr AsciiBoard(Bitboard, char, Color);
        constexpr AsciiBoard(const Board&, Color);

        constexpr AsciiBoard& set(Square, char);
        constexpr AsciiBoard& set_all(Bitboard, char);
        constexpr AsciiBoard& set_state(const Board&);
        constexpr AsciiBoard& clear();
        constexpr AsciiBoard& flip();

        constexpr char* begin();
        constexpr char* end();

        constexpr const char* begin() const;
        constexpr const char* end() const;

    private:
        static constexpr std::array<char, 128> kInitialData =
        {
            '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', '\n',
            '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', '\n',
            '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', '\n',
            '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', '\n',
            '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', '\n',
            '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', '\n',
            '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', '\n',
            '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', '\n',
        };

        static constexpr size_t index(Square sq, Color side)
        {
            Rank rank = RelativeRank(RankOf(sq), side ^ kBlack);
            File file = RelativeFile(FileOf(sq), side);
            return 16 * rank + 2 * file;
        }

        Color side = kWhite;
        std::array<char, 128> data = kInitialData;
    };

    constexpr AsciiBoard::AsciiBoard(Bitboard bb, char ch = '1', Color side = kWhite) :
        side(side)
    {
        set_all(bb, ch);
    }

    constexpr AsciiBoard::AsciiBoard(const Board& board, Color side = kWhite) :
        side(side)
    {
        set_state(board);
    }

    constexpr AsciiBoard& AsciiBoard::set(Square sq, char ch)
    {
        data[index(sq, side)] = ch;
        return *this;
    }

    constexpr AsciiBoard& AsciiBoard::set_all(Bitboard bb, char ch)
    {
        while (bb)
        {
            set(PopLSB(bb), ch);
        }
        return *this;
    }

    constexpr AsciiBoard& AsciiBoard::set_state(const Board& board)
    {
        data = kInitialData;
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            if (board.on(sq))
            {
                set(sq, PieceChar(board.on(sq)));
            }
        }
        return *this;
    }

    constexpr AsciiBoard& AsciiBoard::clear()
    {
        data = kInitialData;
        return *this;
    }

    constexpr AsciiBoard& AsciiBoard::flip()
    {
        auto flipped = kInitialData;
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            flipped[index(sq, side ^ kBlack)] = data[index(sq, side)];
        }
        side ^= kBlack;
        data = flipped;
        return *this;
    }

    constexpr char* AsciiBoard::begin()
    {
        return std::begin(data);
    }

    constexpr char* AsciiBoard::end()
    {
        return std::end(data);
    }

    constexpr const char* AsciiBoard::begin() const
    {
        return std::begin(data);
    }

    constexpr const char* AsciiBoard::end() const
    {
        return std::end(data);
    }

    inline std::ostream& operator<<(std::ostream& os, const AsciiBoard& ascii_board)
    {
        return os << std::string_view(std::begin(ascii_board), std::end(ascii_board));
    }
}

namespace cohen_chess
{
    using io::ascii_board::AsciiBoard;
}

#endif