#ifndef COHEN_CHESS_IO_FEN_H_INCLUDED
#define COHEN_CHESS_IO_FEN_H_INCLUDED

#include "../engine/board.h"

#include <regex>

namespace cohen_chess
{
    const std::regex kFenRegex
    {
        "([pnbrqkPNBRKQ1-8]+)"  "(/)"
        "([pnbrqkPNBRKQ1-8]+)"  "(/)"
        "([pnbrqkPNBRKQ1-8]+)"  "(/)"
        "([pnbrqkPNBRKQ1-8]+)"  "(/)"
        "([pnbrqkPNBRKQ1-8]+)"  "(/)"
        "([pnbrqkPNBRKQ1-8]+)"  "(/)"
        "([pnbrqkPNBRKQ1-8]+)"  "(/)"
        "([pnbrqkPNBRKQ1-8]+)"  "(\\s+)"
        "(w|b)"                 "(\\s+)"
        "([KQkq]{1,4}|-)"       "(\\s+)"
        "([a-h][1-8]|-)"        "(\\s+)"
        "(\\d+)"                "(\\s+)"
        "(\\d+)"
    };

    constexpr size_t kFenRegexGroupRank8            =  1;
    constexpr size_t kFenRegexGroupRank7            =  3;
    constexpr size_t kFenRegexGroupRank6            =  5;
    constexpr size_t kFenRegexGroupRank5            =  7;
    constexpr size_t kFenRegexGroupRank4            =  9;
    constexpr size_t kFenRegexGroupRank3            = 11;
    constexpr size_t kFenRegexGroupRank2            = 13;
    constexpr size_t kFenRegexGroupRank1            = 15;
    constexpr size_t kFenRegexGroupSide             = 17;
    constexpr size_t kFenRegexGroupCastlingRights   = 19;
    constexpr size_t kFenRegexGroupEnPassantTarget  = 21;
    constexpr size_t kFenRegexGroupHalfmoveClock    = 23;
    constexpr size_t kFenRegexGroupFullmoveCount    = 25;

    constexpr CastlingRights FenCastlingRightsBit(char ch)
    {
        switch (ch)
        {
            case 'K': return kWhiteOOO;
            case 'Q': return kWhiteOO;
            case 'k': return kBlackOOO;
            case 'q': return kBlackOO;
            default:  return kCastlingNone;
        }
    }

    constexpr CastlingRights FenCastlingRights(std::string_view fen_cr)
    {
        CastlingRights cr = kCastlingNone;
        for (const auto ch : fen_cr)
        {
            cr |= FenCastlingRightsBit(ch);
        }
        return cr;
    }

    constexpr File FenEnPassantTarget(std::string_view fen_ep_target)
    {
        if (fen_ep_target == "-" || fen_ep_target.size() == 0)
        {
            return kFileNB;
        }
        else
        {
            return CharToFile(fen_ep_target[0]);
        }
    }

    constexpr bool SetFenRank(std::string_view fen_rank, Board& board, Rank rank)
    {
        File file = kFileA;
        for (char ch : fen_rank)
        {
            if (IsRankChar(ch))
            {
                file += CharToRank(ch) + 1;
            }
            else if (IsPieceChar(ch))
            {
                board.put(CharToPiece(ch), MakeSquare(rank, file++));
            }
            else
            {
                return false;
            }
        }
        return file == kFileNB;
    }

    inline bool SetFenPosition(std::string_view fen, Board& board)
    {
        std::cmatch match;
        if (std::regex_match(std::begin(fen), std::end(fen), match, kFenRegex))
        {
            board.clear();
            board.state.set_castling_rights(FenCastlingRights(match[kFenRegexGroupCastlingRights].str()));
            board.state.set_ep_file(FenEnPassantTarget(match[kFenRegexGroupEnPassantTarget].str()));
            board.state.set_side(match[kFenRegexGroupSide].str() == "b");
            board.state.halfmove_clock = std::stoi(match[kFenRegexGroupHalfmoveClock]);
            board.state.fullmove_count = std::stoi(match[kFenRegexGroupFullmoveCount]);
            return SetFenRank(match[kFenRegexGroupRank8].str(), board, kRank8) &&
                   SetFenRank(match[kFenRegexGroupRank7].str(), board, kRank7) &&
                   SetFenRank(match[kFenRegexGroupRank6].str(), board, kRank6) &&
                   SetFenRank(match[kFenRegexGroupRank5].str(), board, kRank5) &&
                   SetFenRank(match[kFenRegexGroupRank4].str(), board, kRank4) &&
                   SetFenRank(match[kFenRegexGroupRank3].str(), board, kRank3) &&
                   SetFenRank(match[kFenRegexGroupRank2].str(), board, kRank2) &&
                   SetFenRank(match[kFenRegexGroupRank1].str(), board, kRank1);
        }
        else
        {
            return false;
        }
    }

    inline std::ostream& FormatFenRank(std::ostream& os, const Board& board, Rank rank)
    {
        int empty_count = 0;
        for (File file = kFileA; file < kFileNB; ++file)
        {
            Piece piece = board.on(MakeSquare(rank, file));
            if (piece)
            {
                if (empty_count)
                {
                    os << empty_count;
                    empty_count = 0;
                }
                os << PieceChar(piece);
            }
            else
            {
                ++empty_count;
            }
        }
        return empty_count ? os << empty_count : os;
    }

    inline std::ostream& FormatFenSide(std::ostream& os, Color side)
    {
        return os << ColorChar(side);
    }

    inline std::ostream& FormatFenCastlingRights(std::ostream& os, CastlingRights cr)
    {
        if (cr)
        {
            if (cr & kWhiteOOO)
                os << 'K';
            if (cr & kWhiteOO)
                os << 'Q';
            if (cr & kBlackOOO)
                os << 'k';
            if (cr & kBlackOO)
                os << 'q';
        }
        else
        {
            os << '-';
        }
        return os;
    }

    inline std::ostream& FormatFenEnPassantTarget(std::ostream& os, const BoardState& state)
    {
        if (state.ep_file == kFileNB)
        {
            os << '-';
        }
        else
        {
            os << FileChar(state.ep_file);
            os << RankChar(RelativeRank(kRank3, state.side ^ kBlack));
        }
        return os;
    }

    inline std::ostream& FormatFenPosition(std::ostream& os, const Board& board)
    {
        FormatFenRank(os, board, kRank8) << '/';
        FormatFenRank(os, board, kRank7) << '/';
        FormatFenRank(os, board, kRank6) << '/';
        FormatFenRank(os, board, kRank5) << '/';
        FormatFenRank(os, board, kRank4) << '/';
        FormatFenRank(os, board, kRank3) << '/';
        FormatFenRank(os, board, kRank2) << '/';
        FormatFenRank(os, board, kRank1) << ' ';
        FormatFenSide(os, board.state.side) << ' ';
        FormatFenCastlingRights(os, board.state.castling_rights) << ' ';
        FormatFenEnPassantTarget(os, board.state) << ' ';
        os << board.state.halfmove_clock << ' ';
        os << board.state.fullmove_count;
        return os;
    }
}

#endif