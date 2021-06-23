#ifndef COHEN_CHESS_IO_FEN_HPP_INCLUDED
#define COHEN_CHESS_IO_FEN_HPP_INCLUDED

#include <iostream>

#include <engine/board.hpp>
#include <io/algebraic_notation.hpp>
#include <io/parse.hpp>
#include <type/file.hpp>
#include <type/rank.hpp>
#include <type/square.hpp>

namespace cohen_chess::io::fen
{
    inline std::istream& SetFenPiecePlacement(std::istream& is, Board& board)
    {
        int token;
        Rank rank = kRank8;
        File file = kFileA;
        while (token = is.get(), rank > -1)
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
        while (token = is.get(), !std::isspace(token) && token != '-')
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
        if (is >> token, !IsCoordinateString(token))
            throw ParseError("unexpected token");
        board.set_ep_file(token == "-" ? kFileNB : CharToFile(token[0]));
        return is;
    }

    inline std::istream& SetFenPosition(std::istream& is, Board& board)
    {
        board.clear();
        SetFenPiecePlacement(is, board) >> std::ws;
        SetFenSideToMove(is, board) >> std::ws;
        SetFenEnPassantTarget(is, board) >> std::ws;
        SetFenCastling(is, board) >> std::ws;
        is >> board.state.fullmove_clock >> std::ws;
        is >> board.state.halfmove_clock >> std::ws;
        return is;
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
        return os << ColorChar(board.state.side);
    }

    inline std::ostream& FormatFenCastling(std::ostream& os, const Board& board)
    {
        if (board.state.castling)
        {
            if (board.state.castling & kWhiteOOO)
                os << 'K';
            if (board.state.castling & kWhiteOO)
                os << 'Q';
            if (board.state.castling & kBlackOOO)
                os << 'k';
            if (board.state.castling & kBlackOO)
                os << 'q';
        }
        else
        {
            os << '-';
        }
        return os;
    }

    inline std::ostream& FormatFenEnPassantTarget(std::ostream& os, const Board& board)
    {
        // TODO
        return os;
    }

    inline std::ostream& FormatFenPosition(std::ostream& os, const Board& board)
    {
        FormatFenPiecePlacement(os, board) << ' ';
        FormatFenSideToMove(os, board) << ' ';
        FormatFenCastling(os, board) << ' ';
        FormatFenEnPassantTarget(os, board) << ' ';
    }
}

namespace cohen_chess
{
    using io::fen::SetFenPosition;
}

#endif
