#ifndef COHEN_CHESS_ALGEBRAIC_NOTATION_HPP_INCLUDED
#define COHEN_CHESS_ALGEBRAIC_NOTATION_HPP_INCLUDED

#include <array>
#include <cassert>
#include <string>

#include <cohen/chess/type/color.hpp>
#include <cohen/chess/type/file.hpp>
#include <cohen/chess/type/piece.hpp>
#include <cohen/chess/type/rank.hpp>
#include <cohen/chess/type/square.hpp>

namespace cohen::chess::io::algebraic_notation
{
    constexpr char ColorChar(Color side) noexcept
    {
        assert(side == kWhite || side == kBlack);
        return side == kWhite ? 'w' : 'b';
    }

    constexpr bool IsColorChar(char token) noexcept
    {
        return token == ColorChar(kWhite) || token == ColorChar(kBlack);
    }

    constexpr Color CharToColor(char token) noexcept
    {
        assert(IsColorChar(token));
        return token == ColorChar(kBlack);
    }

    constexpr char RankChar(Rank rank) noexcept
    {
        assert(kRank1 <= rank && rank < kRankNB);
        return rank + '1';
    }

    constexpr bool IsRankChar(char token) noexcept
    {
        return RankChar(kRank1) <= token && token <= RankChar(kRank8);
    }

    constexpr Rank CharToRank(char token) noexcept
    {
        assert(IsRankChar(token));
        return token - RankChar(kRank1);
    }

    constexpr char FileChar(File file) noexcept
    {
        assert(kFileA <= file && file < kFileNB);
        return file + 'a';
    }

    constexpr bool IsFileChar(char token) noexcept
    {
        return FileChar(kFileA) <= token && token <= FileChar(kFileH);
    }

    constexpr File CharToFile(char token) noexcept
    {
        assert(IsFileChar(token));
        return token - FileChar(kFileA);
    }

    constexpr std::array<char, kPieceTypeNB> kPieceTypeTokens =
    {
        '.', 'p', 'n', 'b', 'r', 'q', 'k', '*'
    };

    constexpr char PieceTypeChar(PieceType type) noexcept
    {
        assert(kPieceTypeNone <= type && type < kPieceTypeNB);
        return kPieceTypeTokens[type];
    }

    constexpr bool IsPieceTypeChar(char token) noexcept
    {
        return token == PieceTypeChar(kPieceTypeNone) ||
               token == PieceTypeChar(kPawn)          ||
               token == PieceTypeChar(kKnight)        ||
               token == PieceTypeChar(kBishop)        ||
               token == PieceTypeChar(kRook)          ||
               token == PieceTypeChar(kQueen)         ||
               token == PieceTypeChar(kKing)          ||
               token == PieceTypeChar(kPieceTypeAll);
    }

    constexpr PieceType CharToPieceType(char token) noexcept
    {
        assert(IsPieceTypeChar(token));
        switch (token)
        {
            case PieceTypeChar(kPieceTypeNone): return kPieceTypeNone;
            case PieceTypeChar(kPawn):          return kPawn;
            case PieceTypeChar(kKnight):        return kKnight;
            case PieceTypeChar(kBishop):        return kBishop;
            case PieceTypeChar(kRook):          return kRook;
            case PieceTypeChar(kQueen):         return kQueen;
            case PieceTypeChar(kKing):          return kKing;
            case PieceTypeChar(kPieceTypeAll):  return kPieceTypeAll;
            default:                            return kPieceTypeNB;
        }
    }

    constexpr std::array<char, kPieceNB> kPieceTokens =
    {
        '.', 'P', 'N', 'B', 'R', 'Q', 'K', '*',
        '1', 'p', 'n', 'b', 'r', 'q', 'k', '#',
    };

    constexpr char PieceChar(Piece pc) noexcept
    {
        assert(kPieceNone <= pc && pc < kPieceNB);
        return kPieceTokens[pc];
    }

    constexpr bool IsPieceChar(char token) noexcept
    {
        return token == PieceChar(kPieceNone)   ||
               token == PieceChar(kWhitePawn)   ||
               token == PieceChar(kWhiteKnight) ||
               token == PieceChar(kWhiteBishop) ||
               token == PieceChar(kWhiteRook)   ||
               token == PieceChar(kWhiteQueen)  ||
               token == PieceChar(kWhiteKing)   ||
               token == PieceChar(kWhiteAll)    ||
               token == PieceChar(kOccupancy)   ||
               token == PieceChar(kBlackPawn)   ||
               token == PieceChar(kBlackKnight) ||
               token == PieceChar(kBlackBishop) ||
               token == PieceChar(kBlackRook)   ||
               token == PieceChar(kBlackQueen)  ||
               token == PieceChar(kBlackKing)   ||
               token == PieceChar(kBlackAll);
    }

    constexpr Piece CharToPiece(char token) noexcept
    {
        assert(IsPieceChar(token));
        switch (token)
        {
            case PieceChar(kPieceNone):   return kPieceNone;
            case PieceChar(kWhitePawn):   return kWhitePawn;
            case PieceChar(kWhiteKnight): return kWhiteKnight;
            case PieceChar(kWhiteBishop): return kWhiteBishop;
            case PieceChar(kWhiteRook):   return kWhiteRook;
            case PieceChar(kWhiteQueen):  return kWhiteQueen;
            case PieceChar(kWhiteKing):   return kWhiteKing;
            case PieceChar(kWhiteAll):    return kWhiteAll;
            case PieceChar(kOccupancy):   return kOccupancy;
            case PieceChar(kBlackPawn):   return kBlackPawn;
            case PieceChar(kBlackKnight): return kBlackKnight;
            case PieceChar(kBlackBishop): return kBlackBishop;
            case PieceChar(kBlackRook):   return kBlackRook;
            case PieceChar(kBlackQueen):  return kBlackQueen;
            case PieceChar(kBlackKing):   return kBlackKing;
            case PieceChar(kBlackAll):    return kBlackAll;
            default:                      return kPieceNB;
        }
    }

    inline std::string CoordinateString(Square sq)
    {
        if (kA1 <= sq && sq < kSquareNB)
        {
            return std::string
            {
                FileChar(FileOf(sq)),
                RankChar(RankOf(sq)),
            };
        }
        else
        {
            return "-";
        }
    }

    inline bool IsCoordinateString(std::string coord)
    {
        return (coord.size() == 2 && IsFileChar(coord[0]) && IsRankChar(coord[1])) || coord == "-";
    }

    inline Square CoordinateToSquare(std::string coord)
    {
        if (coord == "-")
        {
            return kSquareNone;
        }
        else
        {
            Rank rank = CharToRank(coord[1]);
            File file = CharToFile(coord[0]);
            return MakeSquare(rank, file);
        }
    }
}

namespace cohen::chess
{
    using cohen::chess::io::algebraic_notation::ColorChar;
    using cohen::chess::io::algebraic_notation::IsColorChar;
    using cohen::chess::io::algebraic_notation::CharToColor;

    using cohen::chess::io::algebraic_notation::RankChar;
    using cohen::chess::io::algebraic_notation::IsRankChar;
    using cohen::chess::io::algebraic_notation::CharToRank;

    using cohen::chess::io::algebraic_notation::FileChar;
    using cohen::chess::io::algebraic_notation::IsFileChar;
    using cohen::chess::io::algebraic_notation::CharToFile;

    using cohen::chess::io::algebraic_notation::PieceTypeChar;
    using cohen::chess::io::algebraic_notation::IsPieceTypeChar;
    using cohen::chess::io::algebraic_notation::CharToPieceType;

    using cohen::chess::io::algebraic_notation::PieceChar;
    using cohen::chess::io::algebraic_notation::IsPieceChar;
    using cohen::chess::io::algebraic_notation::CharToPiece;

    using cohen::chess::io::algebraic_notation::CoordinateString;
    using cohen::chess::io::algebraic_notation::IsCoordinateString;
    using cohen::chess::io::algebraic_notation::CoordinateToSquare;
}

#endif
