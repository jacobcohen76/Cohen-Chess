#ifndef COHEN_CHESS_IO_ALGEBRAIC_NOTATION_H_INCLUDED
#define COHEN_CHESS_IO_ALGEBRAIC_NOTATION_H_INCLUDED

#include "../types/color.h"
#include "../types/file.h"
#include "../types/rank.h"
#include "../types/piece_type.h"
#include "../types/piece.h"
#include "../types/square.h"

#include <string>

namespace cohen_chess
{
    constexpr char ColorChar(Color c)
    {
        return c * ('w' - 'b') + 'b';
    }

    constexpr char FileChar(File f)
    {
        return f + 'a';
    }

    constexpr char RankChar(Rank r)
    {
        return r + '1';
    }

    constexpr char PieceTypeChar(PieceType pc_type)
    {
        return (char[kPieceTypeNB]) 
        {
            '?', //kTypeNone
            'p', //kTypePawn
            'n', //kTypeKnight
            'b', //kTypeBishop
            'r', //kTypeRook
            'q', //kTypeQueen
            'k', //kTypeKing
            '?', //kTypeAll
        }[pc_type];
    }

    constexpr char PieceChar(Piece pc)
    {
        return (char[kPieceNB]) 
        {
            '.', //kPieceNone
            'P', //kWhitePawn
            'N', //kWhiteKnight
            'B', //kWhiteBishop
            'R', //kWhiteRook
            'Q', //kWhiteQueen
            'K', //kWhiteKing
            '?', //kWhiteAll
            '1', //kOccupancy
            'p', //kBlackPawn
            'n', //kBlackKnight
            'b', //kBlackBishop
            'r', //kBlackRook
            'q', //kBlackQueen
            'k', //kBlackKing
            '?', //kBlackAll
        }[pc];
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

    constexpr Color CharToColor(char ch)
    {
        return Color(ch == ColorChar(kBlack));
    }

    constexpr File CharToFile(char ch)
    {
        return File(ch - FileChar(kFileA));
    }

    constexpr Rank CharToRank(char ch)
    {
        return Rank(ch - RankChar(kRank1));
    }

    inline Square CoordinateToSquare(std::string coord)
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

    constexpr PieceType CharToPieceType(char ch)
    {
        switch(ch)
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

    constexpr Piece CharToPiece(char ch)
    {
        switch(ch)
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

    constexpr bool IsColorChar(char ch)
    {
        return ch == ColorChar(kWhite) || ch == ColorChar(kBlack);
    }

    constexpr bool IsFileChar(char ch)
    {
        return FileChar(kFileA) <= ch && ch <= FileChar(kFileB);
    }

    constexpr bool IsRankChar(char ch)
    {
        return RankChar(kRank1) <= ch && ch <= RankChar(kRank8);
    }

    constexpr bool IsPieceTypeChar(char ch)
    {
        switch(ch)
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

    constexpr bool IsPieceChar(char ch)
    {
        switch(ch)
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

    inline bool IsCoordinateString(std::string str)
    {
        return str[0] == '-' || (IsFileChar(str[0]) && IsRankChar(str[1]));
    }
}

#endif