#ifndef COHEN_CHESS_IO_FEN_HPP_INCLUDED
#define COHEN_CHESS_IO_FEN_HPP_INCLUDED

#include <iostream>
#include <sstream>

#include <cohen/chess/io/algebraic_notation.hpp>
#include <cohen/chess/io/parse.hpp>
#include <cohen/chess/type/file.hpp>
#include <cohen/chess/type/rank.hpp>
#include <cohen/chess/type/square.hpp>
#include <cohen/chess/board.hpp>

namespace cohen::chess::io::fen
{
    inline std::istream& SetFenPiecePlacement(std::istream& is, Board& board)
    {
        int token;
        Rank rank = kRank8;
        File file = kFileA;
        while (token = is.get(), rank != kRank1 || file != kFileNB)
        {
            if (IsPieceChar(token))
            {
                board.put(CharToPiece(token), MakeSquare(rank, file++));
            }
            else if ('1' <= token && token <= '8')
            {
                file += token - '0';
            }
            else if (token == '/')
            {
                if (file < kFileNB)
                    throw ParseError("illegal state reached");
                --rank, file = kFileA;
            }
            else throw ParseError("unrecognized token");
        }
        return is;
    }

    inline std::istream& SetFenSideToMove(std::istream& is, Board& board)
    {
        std::string token;
        if (is >> token, token != "w" && token != "b")
            throw ParseError("unrecognized token");
        board.set_side(token == "b");
        return is;
    }

    constexpr Castling StandardFenCastlingBit(char token) noexcept
    {
        switch (token)
        {
            case 'K': return kWhiteOO;
            case 'Q': return kWhiteOOO;
            case 'k': return kBlackOO;
            case 'q': return kBlackOOO;
            default:  return kCastlingNone;
        }
    }

    inline std::istream& SetFenCastling(std::istream& is, Board& board)
    {
        int token;
        Castling castling = kCastlingNone;
        while (token = is.get(), not std::isspace(token) && token != '-')
        {
            Castling bit = StandardFenCastlingBit(token);
            if (bit == kCastlingNone)
                throw ParseError("unrecognized token");
            if (castling & bit)
                throw ParseError("duplicate castling bit");
            castling |= bit;
        }
        if (token == '-' && castling)
            throw ParseError("illegal state reached");
        board.set_castling(castling);
        return is;
    }

    inline std::istream& SetFenEnPassantTarget(std::istream& is, Board& board)
    {
        std::string token;
        if (is >> token, not IsCoordinateString(token))
            throw ParseError("unexpected token");
        board.set_ep_file(token == "-" ? kFileNB : CharToFile(token[0]));
        return is;
    }

    inline std::istream& SetFenFullmoveClock(std::istream& is, Board& board)
    {
        uint16_t fullmove_clock;
        if (is >> fullmove_clock, is.fail())
            throw ParseError("unexpected token");
        board.set_fullmove_clock(fullmove_clock);
        return is;
    }

    inline std::istream& SetFenHalfmoveClock(std::istream& is, Board& board)
    {
        uint16_t halfmove_clock;
        if (is >> halfmove_clock, is.fail())
            throw ParseError("unexpected token");
        board.set_halfmove_clock(halfmove_clock);
        return is;
    }

    inline std::istream& SetFenPosition(std::istream& is, Board& board)
    {
        board.clear();
        SetFenPiecePlacement(is, board) >> std::ws;
        SetFenSideToMove(is, board) >> std::ws;
        SetFenCastling(is, board) >> std::ws;
        SetFenEnPassantTarget(is, board) >> std::ws;
        SetFenFullmoveClock(is, board) >> std::ws;
        SetFenHalfmoveClock(is, board) >> std::ws;
        return is;
    }

    inline void SetFenPosition(const std::string& str, Board& board)
    {
        std::istringstream iss{str};
        SetFenPosition(iss, board);
    }

    inline void SetFenPosition(std::string&& str, Board& board)
    {
        std::istringstream iss{str};
        SetFenPosition(iss, board);
    }

    inline std::ostream& FormatFenPiecePlacement(std::ostream& os, const Board& board)
    {
        for (Rank rank = kRank8; rank > -1; --rank)
        {
            int empty_count = 0;
            for (File file = kFileA; file < kFileNB; ++file)
            {
                Square sq = MakeSquare(rank, file);
                if (board.on(sq))
                {
                    if (empty_count)
                    {
                        os << empty_count;
                        empty_count = 0;
                    }
                    os << PieceChar(board.on(sq));
                }
                else ++empty_count;
            }
            if (empty_count)
                os << empty_count;
            if (rank > kRank1)
                os << '/';
        }
        return os;
    }

    inline std::ostream& FormatFenSideToMove(std::ostream& os, const Board& board)
    {
        return os << ColorChar(board.side());
    }

    inline std::ostream& FormatFenCastling(std::ostream& os, const Board& board)
    {
        if (board.castling())
        {
            if (board.castling() & kWhiteOOO) os << 'K';
            if (board.castling() & kWhiteOO)  os << 'Q';
            if (board.castling() & kBlackOOO) os << 'k';
            if (board.castling() & kBlackOO)  os << 'q';
        }
        else
        {
            os << '-';
        }
        return os;
    }

    inline std::ostream& FormatFenEnPassantTarget(std::ostream& os, const Board& board)
    {
        return os << CoordinateString(board.ep_target());
    }

    inline std::ostream& FormatFenPosition(std::ostream& os, const Board& board)
    {
        FormatFenPiecePlacement(os, board) << ' ';
        FormatFenSideToMove(os, board) << ' ';
        FormatFenCastling(os, board) << ' ';
        FormatFenEnPassantTarget(os, board) << ' ';
        return os << board.fullmove_clock() << ' ' << int(board.halfmove_clock());
    }

    inline std::string FormatFenPosition(const Board& board)
    {
        std::ostringstream oss;
        FormatFenPosition(oss, board);
        return oss.str();
    }

    inline Board ParseFen(std::string fen_str)
    {
        Board board = {};

        return board;
    }

    inline std::string FenString(Board board)
    {

        return "";
    }
}

namespace cohen::chess
{
    using cohen::chess::io::fen::SetFenPosition;
    using cohen::chess::io::fen::FormatFenPosition;
    using cohen::chess::io::fen::ParseFen;
    using cohen::chess::io::fen::FenString;
}

#endif
