#ifndef COHEN_CHESS_IO_ASCII_BOARD_HPP_INCLUDED
#define COHEN_CHESS_IO_ASCII_BOARD_HPP_INCLUDED

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>

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
        constexpr AsciiBoard(Bitboard, char, Color) noexcept;
        constexpr AsciiBoard(const Board&, Color) noexcept;

        constexpr AsciiBoard& set(Square, char) noexcept;
        constexpr AsciiBoard& set_all(Bitboard, char) noexcept;
        constexpr AsciiBoard& set_state(const Board&) noexcept;
        constexpr AsciiBoard& clear() noexcept;
        constexpr AsciiBoard& flip() noexcept;

        constexpr char& operator[](Square) noexcept;
        constexpr const char& operator[](Square) const noexcept;

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

        constexpr void fill(Bitboard, char) noexcept;
        constexpr void swap(AsciiBoard&) noexcept;

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

        std::array<char, 128> data = kInitialData;
        Color side = kWhite;
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
        data  = flipped;
        side ^= kBlack;
        return *this;
    }

    constexpr char& AsciiBoard::operator[](Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return data[index(sq, side)];
    }

    constexpr const char& AsciiBoard::operator[](Square sq) const noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return data[index(sq, side)];
    }

    constexpr char* AsciiBoard::begin() noexcept
    {
        return data.begin();
    }

    constexpr const char* AsciiBoard::begin() const noexcept
    {
        return data.begin();
    }

    constexpr const char* AsciiBoard::cbegin() const noexcept
    {
        return data.cbegin();
    }

    constexpr char* AsciiBoard::end() noexcept
    {
        return data.end();
    }

    constexpr const char* AsciiBoard::end() const noexcept
    {
        return data.end();
    }

    constexpr const char* AsciiBoard::cend() const noexcept
    {
        return data.cend();
    }

    constexpr std::reverse_iterator<char*> AsciiBoard::rbegin() noexcept
    {
        return data.rbegin();
    }

    constexpr std::reverse_iterator<const char*> AsciiBoard::rbegin() const noexcept
    {
        return data.rbegin();
    }

    constexpr std::reverse_iterator<const char*> AsciiBoard::crbegin() const noexcept
    {
        return data.crbegin();
    }

    constexpr std::reverse_iterator<char*> AsciiBoard::rend() noexcept
    {
        return data.rend();
    }

    constexpr std::reverse_iterator<const char*> AsciiBoard::rend() const noexcept
    {
        return data.rend();
    }

    constexpr std::reverse_iterator<const char*> AsciiBoard::crend() const noexcept
    {
        return data.crend();
    }

    constexpr bool AsciiBoard::empty() const noexcept
    {
        return data.empty();
    }

    constexpr size_t AsciiBoard::size() const noexcept
    {
        return data.size();
    }

    constexpr size_t AsciiBoard::max_size() const noexcept
    {
        return data.max_size();
    }

    constexpr void AsciiBoard::fill(Bitboard bitset, char value = '1') noexcept
    {
        while (bitset)
        {
            data[index(PopLSB(bitset), side)] = value;
        }
    }

    constexpr void AsciiBoard::swap(AsciiBoard& other) noexcept
    {
        std::swap(data, other.data);
        std::swap(side, other.side);
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
