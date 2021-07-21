#ifndef COHEN_CHESS_IO_ASCII_BOARD_HPP_INCLUDED
#define COHEN_CHESS_IO_ASCII_BOARD_HPP_INCLUDED

#include <array>
#include <cassert>
#include <iostream>

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
        constexpr explicit AsciiBoard(const Board&, Color) noexcept;
        constexpr explicit AsciiBoard(Bitboard, char, Color) noexcept;

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
        constexpr void fill(const Board&) noexcept;
        constexpr void fill(Bitboard, char) noexcept;
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

        static constexpr size_t index(Square sq, Color side) noexcept
        {
            Rank rank = RelativeRank(RankOf(sq), side ^ kBlack);
            File file = RelativeFile(FileOf(sq), side);
            return 16 * rank + 2 * file;
        }

        std::array<char, 128> data_ = kInitialData;
        Color side_ = kWhite;
    };

    constexpr AsciiBoard::AsciiBoard(Color side) noexcept
        : side_{side} {};

    constexpr AsciiBoard::AsciiBoard(const Board& board,
                                     Color        side = kWhite) noexcept
        : side_{side}
    {
        fill(board);
    }

    constexpr AsciiBoard::AsciiBoard(Bitboard bitset,
                                     char     value = '1',
                                     Color    side  = kWhite) noexcept
        : side_{side}
    {
        fill(bitset, value);
    }

    constexpr char& AsciiBoard::operator[](Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return data_[index(sq, side_)];
    }

    constexpr const char& AsciiBoard::operator[](Square sq) const noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return data_[index(sq, side_)];
    }

    constexpr char* AsciiBoard::data() noexcept
    {
        return data_.data();
    }

    constexpr const char* AsciiBoard::data() const noexcept
    {
        return data_.data();
    }

    constexpr char* AsciiBoard::begin() noexcept
    {
        return data_.begin();
    }

    constexpr const char* AsciiBoard::begin() const noexcept
    {
        return data_.begin();
    }

    constexpr const char* AsciiBoard::cbegin() const noexcept
    {
        return data_.cbegin();
    }

    constexpr char* AsciiBoard::end() noexcept
    {
        return data_.end();
    }

    constexpr const char* AsciiBoard::end() const noexcept
    {
        return data_.end();
    }

    constexpr const char* AsciiBoard::cend() const noexcept
    {
        return data_.cend();
    }

    constexpr std::reverse_iterator<char*> AsciiBoard::rbegin() noexcept
    {
        return data_.rbegin();
    }

    constexpr std::reverse_iterator<const char*> AsciiBoard::rbegin() const noexcept
    {
        return data_.rbegin();
    }

    constexpr std::reverse_iterator<const char*> AsciiBoard::crbegin() const noexcept
    {
        return data_.crbegin();
    }

    constexpr std::reverse_iterator<char*> AsciiBoard::rend() noexcept
    {
        return data_.rend();
    }

    constexpr std::reverse_iterator<const char*> AsciiBoard::rend() const noexcept
    {
        return data_.rend();
    }

    constexpr std::reverse_iterator<const char*> AsciiBoard::crend() const noexcept
    {
        return data_.crend();
    }

    constexpr bool AsciiBoard::empty() const noexcept
    {
        return data_ == kInitialData;
    }

    constexpr size_t AsciiBoard::size() const noexcept
    {
        return data_.size();
    }

    constexpr size_t AsciiBoard::max_size() const noexcept
    {
        return data_.max_size();
    }

    constexpr Color AsciiBoard::side() const noexcept
    {
        return side_;
    }

    constexpr void AsciiBoard::clear() noexcept
    {
        data_ = kInitialData;
    }

    constexpr void AsciiBoard::fill(const Board& board) noexcept
    {
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            if (board.on(sq))
            {
                data_[index(sq, side_)] = PieceChar(board.on(sq));
            }
        }
    }

    constexpr void AsciiBoard::fill(Bitboard bitset, char value = '1') noexcept
    {
        while (bitset)
        {
            data_[index(PopLSB(bitset), side_)] = value;
        }
    }

    constexpr void AsciiBoard::flip() noexcept
    {
        std::array<char, 128> flipped = kInitialData;
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            flipped[index(sq, side_ ^ kBlack)] = data_[index(sq, side_)];
        }
        data_  = flipped;
        side_ ^= kBlack;
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
