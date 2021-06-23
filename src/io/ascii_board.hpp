#ifndef COHEN_CHESS_IO_ASCII_BOARD_HPP_INCLUDED
#define COHEN_CHESS_IO_ASCII_BOARD_HPP_INCLUDED

#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <string>

#include <engine/board.hpp>
#include <type/bitboard.hpp>
#include <type/rank.hpp>
#include <type/color.hpp>
#include <type/file.hpp>
#include <type/square.hpp>

namespace cohen_chess::io::ascii_board
{
    class AsciiBoard
    {
    public:
        constexpr AsciiBoard() noexcept = default;
        constexpr AsciiBoard(Bitboard, char, Color) noexcept;
        constexpr AsciiBoard(const Board&, Color) noexcept;

        constexpr AsciiBoard& set(Square, char) noexcept;
        constexpr AsciiBoard& set_all(Bitboard, char) noexcept;
        constexpr AsciiBoard& set_state(const Board&) noexcept;
        constexpr AsciiBoard& clear() noexcept;
        constexpr AsciiBoard& flip() noexcept;

        constexpr char* begin() noexcept;
        constexpr char* end() noexcept;

        constexpr const char* begin() const noexcept;
        constexpr const char* end() const noexcept;

        constexpr size_t size() const noexcept;

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

        static constexpr size_t index(Square sq, Color side) noexcept
        {
            Rank rank = RelativeRank(RankOf(sq), side ^ kBlack);
            File file = RelativeFile(FileOf(sq), side);
            return 16 * rank + 2 * file;
        }

        Color side = kWhite;
        std::array<char, 128> data = kInitialData;
    };

    constexpr AsciiBoard::AsciiBoard(Bitboard bb, char ch = '1', Color side = kWhite) noexcept :
        side(side)
    {
        set_all(bb, ch);
    }

    constexpr AsciiBoard::AsciiBoard(const Board& board, Color side = kWhite) noexcept :
        side(side)
    {
        set_state(board);
    }

    constexpr AsciiBoard& AsciiBoard::set(Square sq, char ch = '1') noexcept
    {
        data[index(sq, side)] = ch;
        return *this;
    }

    constexpr AsciiBoard& AsciiBoard::set_all(Bitboard bb, char ch = '1') noexcept
    {
        while (bb)
        {
            set(PopLSB(bb), ch);
        }
        return *this;
    }

    constexpr AsciiBoard& AsciiBoard::set_state(const Board& board) noexcept
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

    constexpr AsciiBoard& AsciiBoard::clear() noexcept
    {
        data = kInitialData;
        return *this;
    }

    constexpr AsciiBoard& AsciiBoard::flip() noexcept
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

    constexpr char* AsciiBoard::begin() noexcept
    {
        return std::begin(data);
    }

    constexpr char* AsciiBoard::end() noexcept
    {
        return std::end(data);
    }

    constexpr const char* AsciiBoard::begin() const noexcept
    {
        return std::begin(data);
    }

    constexpr const char* AsciiBoard::end() const noexcept
    {
        return std::end(data);
    }

    constexpr size_t AsciiBoard::size() const noexcept
    {
        return data.size();
    }

    inline std::ostream& operator<<(std::ostream& os, const AsciiBoard& ascii_board)
    {
        return os.write(ascii_board.begin(), ascii_board.size());
    }
}

namespace cohen_chess
{
    using io::ascii_board::AsciiBoard;
}

#endif
