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
        "([a-h][1-8]|-)"      "(\\s+)"
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
    constexpr size_t kFenRegexGroupColor            = 17;
    constexpr size_t kFenRegexGroupCastlingRights   = 19;
    constexpr size_t kFenRegexGroupEnPassantTarget  = 21;
    constexpr size_t kFenRegexGroupHalfmoveClock    = 23;
    constexpr size_t kFenRegexGroupFullmoveCount    = 25;

    constexpr CastlingRights FenCastlingRightsBit(char ch)
    {
        switch (ch)
        {
            case 'K': return kWhiteOO;
            case 'Q': return kWhiteOOO;
            case 'k': return kBlackOO;
            case 'q': return kBlackOOO;
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
            board.state.set_ep_file(CoordinateToSquare(match[kFenRegexGroupEnPassantTarget].str()));
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
}

#endif