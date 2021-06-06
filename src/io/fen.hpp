#ifndef COHEN_CHESS_IO_FEN_HPP_INCLUDED
#define COHEN_CHESS_IO_FEN_HPP_INCLUDED

#include <engine/board.hpp>
#include <io/algebraic_notation.hpp>

#include <iostream>
#include <sstream>
#include <string_view>
#include <string>

namespace cohen_chess
{
    const std::string kFenStartingPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    inline std::istream& SetFenPosition(std::istream& is, Board& board)
    {
        std::string token;
        is >> token;
        Square sq = kA8;
        for (const char ch : token)
        {
            if ('1' <= ch && ch <= '8')
            {
                sq += ch - '0';
            }
            else if (IsPieceChar(ch))
            {
                board.put(CharToPiece(ch), sq++);
            }
            else if (ch == '/')
            {
                sq += kSouthSouth;
            }
        }
        is >> token;
        board.state.set_side(token == "b");
        is >> token;
        Castling cr = kCastlingNone;
        for (const char ch : token)
        {
            switch (ch)
            {
                case 'K': cr |= kWhiteOOO; break;
                case 'Q': cr |= kWhiteOO;  break;
                case 'k': cr |= kBlackOOO; break;
                case 'q': cr |= kBlackOO;  break;
            }
        }
        board.state.set_castling_rights(cr);
        is >> token;
        if (token != "-" && token.size())
        {
            board.state.set_ep_file(CharToFile(token[0]));
        }
        else
        {
            board.state.set_ep_file(kFileNB);
        }
        is >> board.state.halfmove_clock >> board.state.fullmove_count;
        return is;
    }

    inline void SetFenPosition(const std::string& fen_str, Board& board)
    {
        std::istringstream iss(fen_str);
        SetFenPosition(iss, board);
    }

    inline void SetFenPosition(const char* fen_cstr, Board& board)
    {
        std::istringstream iss(fen_cstr);
        SetFenPosition(iss, board);
    }

    inline std::istream& operator>>(std::istream& is, Board& board)
    {
        return SetFenPosition(is, board);
    }

    inline std::ostream& FormatFenPosition(std::ostream& os, const Board& board)
    {
        for (Square sq = kA8; sq >= kA1; sq += kSouthSouth)
        {
            int empty_count = 0;
            for (File file = kFileA; file < kFileNB; ++file, ++sq)
            {
                if (board.on(sq))
                {
                    if (empty_count)
                    {
                        os << empty_count;
                        empty_count = 0;
                    }
                    os << PieceChar(board.on(sq));
                }
                else
                {
                    ++empty_count;
                }
            }
            if (empty_count)
            {
                os << empty_count;
            }
            os << ((sq > kA2) ? '/' : ' ');
        }
        os << (board.state.side ? 'b' : 'w') << ' ';
        if (board.state.castling_rights)
        {
            if (board.state.castling_rights & kWhiteOOO)
                os << 'K';
            if (board.state.castling_rights & kWhiteOO)
                os << 'Q';
            if (board.state.castling_rights & kBlackOOO)
                os << 'k';
            if (board.state.castling_rights & kBlackOO)
                os << 'q';
        }
        else
        {
            os << '-';
        }
        os << ' ';
        if (board.state.ep_file < kFileNB)
        {
            os << FileChar(board.state.ep_file);
            os << RankChar(RelativeRank(kRank3, board.state.side ^ kBlack));
        }
        else
        {
            os << '-';
        }
        os << ' ' << board.state.halfmove_clock << ' ' << board.state.fullmove_count;
        return os;
    }

    inline std::string FormatFenPosition(const Board& board)
    {
        std::ostringstream oss;
        FormatFenPosition(oss, board);
        return oss.str();
    }

    inline std::ostream& operator<<(std::ostream& os, const Board& board)
    {
        return FormatFenPosition(os, board);
    }
}

#endif