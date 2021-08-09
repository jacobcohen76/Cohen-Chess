#ifndef COHEN_CHESS_IO_ASCII_BOARD_HPP_INCLUDED
#define COHEN_CHESS_IO_ASCII_BOARD_HPP_INCLUDED

#include <array>
#include <cassert>
#include <iostream>

#include <cohen/chess/io/algebraic_notation.hpp>
#include <cohen/chess/type/bitboard.hpp>
#include <cohen/chess/type/color.hpp>
#include <cohen/chess/type/file.hpp>
#include <cohen/chess/type/rank.hpp>
#include <cohen/chess/type/square.hpp>
#include <cohen/chess/board.hpp>

namespace cohen::chess::io::ascii_board
{
    class AsciiBoard
    {
    public:
        constexpr AsciiBoard() noexcept = default;
        constexpr explicit AsciiBoard(Color) noexcept;
        constexpr explicit AsciiBoard(Bitboard, char, Color) noexcept;
        constexpr explicit AsciiBoard(Board, Color) noexcept;

        constexpr char& operator[](Square) noexcept;
        constexpr const char& operator[](Square) const noexcept;

        constexpr char* data() noexcept;
        constexpr const char* data() const noexcept;

        constexpr char* begin() noexcept;
        constexpr const char* begin() const noexcept;
        constexpr const char* cbegin() const noexcept;

        constexpr char* end() noexcept;
        constexpr const char* end() const noexcept;
        constexpr const char* cend() const noexcept;

        constexpr std::reverse_iterator<char*> rbegin() noexcept;
        constexpr std::reverse_iterator<const char*> rbegin() const noexcept;
        constexpr std::reverse_iterator<const char*> crbegin() const noexcept;

        constexpr std::reverse_iterator<char*> rend() noexcept;
        constexpr std::reverse_iterator<const char*> rend() const noexcept;
        constexpr std::reverse_iterator<const char*> crend() const noexcept;

        constexpr bool empty() const noexcept;
        constexpr size_t size() const noexcept;
        constexpr size_t max_size() const noexcept;
        constexpr Color side() const noexcept;

        constexpr void clear() noexcept;
        constexpr void fill(Bitboard, char) noexcept;
        constexpr void fill(Board) noexcept;
        constexpr void flip() noexcept;

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

        static constexpr size_t index(Color side, Square sq) noexcept
        {
            assert(side == kWhite || side == kBlack);
            assert(kA1 <= sq && sq < kSquareNB);
            Rank rank = RelativeRank(side ^ kBlack, RankOf(sq));
            File file = RelativeFile(side, FileOf(sq));
            return 16 * rank + 2 * file;
        }

        std::array<char, 128> char_data = kInitialData;
        Color curr_side = kWhite;
    };

    constexpr AsciiBoard::AsciiBoard(Color side) noexcept
        : curr_side{side} {}

    constexpr AsciiBoard::AsciiBoard(Bitboard bitset,
                                     char     value = '1',
                                     Color    side  = kWhite) noexcept
        : curr_side{side}
    {
        fill(bitset, value);
    }

    constexpr AsciiBoard::AsciiBoard(Board board,
                                     Color side = kWhite) noexcept
        : curr_side{side}
    {
        fill(board);
    }

    constexpr char& AsciiBoard::operator[](Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return char_data[index(curr_side, sq)];
    }

    constexpr const char& AsciiBoard::operator[](Square sq) const noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return char_data[index(curr_side, sq)];
    }

    constexpr char* AsciiBoard::data() noexcept
    {
        return std::data(char_data);
    }

    constexpr const char* AsciiBoard::data() const noexcept
    {
        return std::data(char_data);
    }

    constexpr char* AsciiBoard::begin() noexcept
    {
        return std::begin(char_data);
    }

    constexpr const char* AsciiBoard::begin() const noexcept
    {
        return std::begin(char_data);
    }

    constexpr const char* AsciiBoard::cbegin() const noexcept
    {
        return std::cbegin(char_data);
    }

    constexpr char* AsciiBoard::end() noexcept
    {
        return std::end(char_data);
    }

    constexpr const char* AsciiBoard::end() const noexcept
    {
        return std::end(char_data);
    }

    constexpr const char* AsciiBoard::cend() const noexcept
    {
        return std::cend(char_data);
    }

    constexpr std::reverse_iterator<char*> AsciiBoard::rbegin() noexcept
    {
        return std::rbegin(char_data);
    }

    constexpr std::reverse_iterator<const char*> AsciiBoard::rbegin() const noexcept
    {
        return std::rbegin(char_data);
    }

    constexpr std::reverse_iterator<const char*> AsciiBoard::crbegin() const noexcept
    {
        return std::crbegin(char_data);
    }

    constexpr std::reverse_iterator<char*> AsciiBoard::rend() noexcept
    {
        return std::rend(char_data);
    }

    constexpr std::reverse_iterator<const char*> AsciiBoard::rend() const noexcept
    {
        return std::rend(char_data);
    }

    constexpr std::reverse_iterator<const char*> AsciiBoard::crend() const noexcept
    {
        return std::crend(char_data);
    }

    constexpr bool AsciiBoard::empty() const noexcept
    {
        return char_data == kInitialData;
    }

    constexpr size_t AsciiBoard::size() const noexcept
    {
        return std::size(char_data);
    }

    constexpr size_t AsciiBoard::max_size() const noexcept
    {
        return char_data.max_size();
    }

    constexpr Color AsciiBoard::side() const noexcept
    {
        return curr_side;
    }

    constexpr void AsciiBoard::clear() noexcept
    {
        char_data = kInitialData;
    }

    constexpr void AsciiBoard::fill(Bitboard bitset, char value = '1') noexcept
    {
        while (bitset)
        {
            char_data[index(curr_side, PopLSB(bitset))] = value;
        }
    }

    constexpr void AsciiBoard::fill(Board board) noexcept
    {
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            if (board.on(sq))
            {
                char_data[index(curr_side, sq)] = PieceChar(board.on(sq));
            }
        }
    }

    constexpr void AsciiBoard::flip() noexcept
    {
        auto flipped = kInitialData;
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            flipped[index(curr_side ^ kBlack, sq)] = char_data[index(curr_side, sq)];
        }
        char_data  = flipped;
        curr_side ^= kBlack;
    }

    inline std::ostream& operator<<(std::ostream& os, const AsciiBoard& ascii_board)
    {
        return os.write(std::begin(ascii_board), std::size(ascii_board));
    }
}

namespace cohen::chess
{
    using cohen::chess::io::ascii_board::AsciiBoard;
}

#endif