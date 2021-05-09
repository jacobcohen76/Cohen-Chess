#ifndef COHEN_CHESS_ALGEBRAIC_NOTATION_H_INCLUDED
#define COHEN_CHESS_ALGEBRAIC_NOTATION_H_INCLUDED

#include "../types/color.h"
#include "../types/file.h"
#include "../types/piece.h"
#include "../types/rank.h"
#include "../types/square.h"

#include <array>
#include <cassert>
#include <string>

namespace cohen_chess
{
    constexpr char ColorChar(Color color)
    {
        return color ? 'b' : 'w';
    }

    constexpr bool IsColorChar(char ch)
    {
        return ch == ColorChar(kWhite) || ch == ColorChar(kBlack);
    }

    constexpr Color CharToColor(char ch)
    {
        return ch == ColorChar(kBlack);
    }

    constexpr char RankChar(Rank rank)
    {
        return rank + '1';
    }

    constexpr bool IsRankChar(char ch)
    {
        return RankChar(kRank1) <= ch && ch <= RankChar(kRank8);
    }

    constexpr char CharToRank(char ch)
    {
        return ch - RankChar(kRank1);
    }

    constexpr char FileChar(File file)
    {
        return file + 'a';
    }

    constexpr bool IsFileChar(char ch)
    {
        return FileChar(kFileA) <= ch && ch <= FileChar(kFileH);
    }

    constexpr char CharToFile(char ch)
    {
        return ch - FileChar(kFileA);
    }

    constexpr std::array<char, kPieceTypeNB> kPieceTypeCharacters =
    {
        '?', 'p', 'n', 'b', 'r', 'q', 'k', '?'
    };

    constexpr char PieceTypeChar(PieceType piece_type)
    {
        return kPieceTypeCharacters[piece_type];
    }

    constexpr bool IsPieceTypeChar(char ch)
    {
        switch (ch)
        {
            case PieceTypeChar(kPawn):
            case PieceTypeChar(kKnight):
            case PieceTypeChar(kBishop):
            case PieceTypeChar(kRook):
            case PieceTypeChar(kQueen):
            case PieceTypeChar(kKing):
                return true;
            default:
                return false;
        }
    }

    constexpr PieceType CharToPieceType(char ch)
    {
        switch (ch)
        {
            case PieceTypeChar(kPawn):      return kPawn;
            case PieceTypeChar(kKnight):    return kKnight;
            case PieceTypeChar(kBishop):    return kBishop;
            case PieceTypeChar(kRook):      return kRook;
            case PieceTypeChar(kQueen):     return kQueen;
            case PieceTypeChar(kKing):      return kKing;
            default:                        return kPieceTypeNone;
        }
    }

    constexpr std::array<char, kPieceNB> kPieceCharacters =
    {
        '.', 'P', 'N', 'B', 'R', 'Q', 'K', '?',
        '1', 'p', 'n', 'b', 'r', 'q', 'k', '?',
    };

    constexpr char PieceChar(Piece piece)
    {
        return kPieceCharacters[piece];
    }

    constexpr bool IsPieceChar(char ch)
    {
        switch (ch)
        {
            case PieceChar(kWhitePawn):
            case PieceChar(kWhiteKnight):
            case PieceChar(kWhiteBishop):
            case PieceChar(kWhiteRook):
            case PieceChar(kWhiteQueen):
            case PieceChar(kWhiteKing):
            case PieceChar(kBlackPawn):
            case PieceChar(kBlackKnight):
            case PieceChar(kBlackBishop):
            case PieceChar(kBlackRook):
            case PieceChar(kBlackQueen):
            case PieceChar(kBlackKing):
                return true;
            default:
                return false;
        }
    }

    constexpr Piece CharToPiece(char ch)
    {
        switch (ch)
        {
            case PieceChar(kWhitePawn):     return kWhitePawn;
            case PieceChar(kWhiteKnight):   return kWhiteKnight;
            case PieceChar(kWhiteBishop):   return kWhiteBishop;
            case PieceChar(kWhiteRook):     return kWhiteRook;
            case PieceChar(kWhiteQueen):    return kWhiteQueen;
            case PieceChar(kWhiteKing):     return kWhiteKing;
            case PieceChar(kBlackPawn):     return kBlackPawn;
            case PieceChar(kBlackKnight):   return kBlackKnight;
            case PieceChar(kBlackBishop):   return kBlackBishop;
            case PieceChar(kBlackRook):     return kBlackRook;
            case PieceChar(kBlackQueen):    return kBlackQueen;
            case PieceChar(kBlackKing):     return kBlackKing;
            default:                        return kPieceNone;
        }
    }

    constexpr Square CoordinateToSquare(std::string_view coord)
    {
        if(coord[0] == '-')
        {
            return kSquareNone;
        }
        else
        {
            return MakeSquare(CharToRank(coord[1]), CharToFile(coord[0]));
        }
    }

    constexpr bool IsCoordinateString(std::string_view view)
    {
        return view[0] == '-' || (IsFileChar(view[0]) && IsRankChar(view[1]));
    }

    inline std::string CoordinateString(Square sq)
    {
        if(IsNormalSquare(sq))
        {
            return std::string{ FileChar(FileOf(sq)), RankChar(RankOf(sq)) };
        }
        else
        {
            return std::string('-', 1);
        }
    }
}

#endif