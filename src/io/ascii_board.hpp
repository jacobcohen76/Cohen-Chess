#ifndef COHEN_CHESS_IO_ASCII_BOARD_HPP_INCLUDED
#define COHEN_CHESS_IO_ASCII_BOARD_HPP_INCLUDED

#include <engine/board.hpp>
#include <types/bitboard.hpp>
#include <types/rank.hpp>
#include <types/color.hpp>
#include <types/file.hpp>
#include <types/square.hpp>

#include <iostream>
#include <cstdint>
#include <string>

namespace cohen_chess
{
    class AsciiBoard
    {
    public:
        constexpr AsciiBoard() = default;
        constexpr AsciiBoard(Color);
        constexpr AsciiBoard(Bitboard, char, Color);
        constexpr AsciiBoard(const Board&, Color);

        constexpr void set(Square, char);
        constexpr void set_all(Bitboard, char);
        constexpr void set_state(const Board&);
        constexpr void clear();
        constexpr void flip();

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

        static constexpr size_t index(Square, Color);

        Color side = kWhite;
        std::array<char, 128> data = kInitialData;
    };

    constexpr AsciiBoard::AsciiBoard(Color side) :
        side(side) {}

    constexpr AsciiBoard::AsciiBoard(Bitboard bb, char ch, Color side = kWhite) :
        side(side)
    {
        set_all(bb, ch);
    }

    constexpr AsciiBoard::AsciiBoard(const Board& board, Color side = kWhite) :
        side(side)
    {
        set_state(board);
    }

    constexpr void AsciiBoard::set(Square sq, char ch)
    {
        data[index(sq, side)] = ch;
    }

    constexpr void AsciiBoard::set_all(Bitboard bb, char ch)
    {
        while (bb)
        {
            set(PopLSB(bb), ch);
        }
    }

    constexpr void AsciiBoard::set_state(const Board& board)
    {
        data = kInitialData;
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            if (board.on(sq))
            {
                set(sq, PieceChar(board.on(sq)));
            }
        }
    }

    constexpr void AsciiBoard::clear()
    {
        data = kInitialData;
    }

    constexpr void AsciiBoard::flip()
    {
        auto flipped = kInitialData;
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            flipped[index(sq, side ^ kBlack)] = data[index(sq, side)];
        }
        side ^= kBlack;
        data = flipped;
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

    constexpr size_t AsciiBoard::index(Square sq, Color side)
    {
        Rank rank = RelativeRank(RankOf(sq), side ^ kBlack);
        File file = RelativeFile(FileOf(sq), side);
        return 16 * rank + 2 * file;
    }

    inline std::ostream& operator <<(std::ostream& os, const AsciiBoard& ascii_board)
    {
        return os << std::string_view(std::begin(ascii_board), std::end(ascii_board));
    }
}

#endif