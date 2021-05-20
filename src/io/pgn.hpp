#ifndef COHEN_CHESS_IO_PGN_HPP_INCLUDED
#define COHEN_CHESS_IO_PGN_HPP_INCLUDED

#include <engine/game_log.hpp>
#include <io/parse.hpp>

#include <iostream>
#include <locale>

namespace cohen_chess
{
    const std::array<std::string, 7> kSevenTagRoster =
    {
        "Event",
        "Site",
        "Date",
        "Round",
        "White",
        "Black",
        "Result",
    };

    inline bool IsPgnResult(const std::string& token)
    {
        return token == "1-0" || token == "0-1" || token == "1/2-1/2" || token == "*";
    }

    inline std::istream& ParseImportPgnTagPair(std::istream& is, GameLog& log)
    {
        std::string key, value;
        if (is >> std::ws, is.get() != '[')
            return is.setstate(std::ios::failbit), is;
        is >> std::ws >> key;
        if (is >> std::ws, is.get() != '"')
            return is.setstate(std::ios::failbit), is;
        std::getline(is, value, '"');
        if (is >> std::ws, is.get() != ']')
            return is.setstate(std::ios::failbit), is;
        log[key] = value;
        return is;
    }

    inline std::istream& ParseExportPgnTagPair(std::istream& is, GameLog& log)
    {
        std::string key, value;
        if (is.get() != '[')
            return is.setstate(std::ios::failbit), is;
        is >> key;
        if (is.get() != ' ')
            return is.setstate(std::ios::failbit), is;
        if (is.get() != '"')
            return is.setstate(std::ios::failbit), is;
        std::getline(is, value, '"');
        if (is.get() != ']')
            return is.setstate(std::ios::failbit), is;
        log[key] = value;
        return is;
    }

    inline std::istream& ParseImportPgnTags(std::istream& is, GameLog& log)
    {
        std::string line;
        while (std::getline(is, line), line.find('[') != std::string::npos)
        {
            std::istringstream line_iss(line);
            ParseImportPgnTagPair(line_iss, log);
            if (line_iss.fail())
            {
                return is.setstate(std::ios::failbit), is;
            }
        }
        return is;
    }

    inline std::istream& ParseExportPgnTags(std::istream& is, GameLog& log)
    {
        std::string line;
        while (std::getline(is, line), line.size())
        {
            std::istringstream line_iss(line);
            ParseExportPgnTagPair(line_iss, log);
            if (line_iss.fail() || line_iss.get() != -1)
            {
                return is.setstate(std::ios::failbit), is;
            }
        }
        return is;
    }

    inline std::istream& ParseImportPgnMoves(std::istream& is, GameLog& log)
    {
        std::string token;
        size_t ply;
        while (is >> std::ws, !is.eof() && !IsPgnResult(token))
        {
            char ch = is.peek();
            if (ch == ';')
            {
                std::getline(is, token);
                // log.comment(token);
            }
            else if (ch == '{')
            {
                std::getline(is, token, '}');
                // log.comment(token + '}');
            }
            else if (ch == '.')
            {
                token = (ch = is.get());
            }
            else if (ch == '0' || ch == '1' || ch == '*')
            {
                
            }
            else if (std::isdigit(ch))
            {
                is >> ply;
                token = std::to_string(ply);
            }
            else
            {
                is >> token;
            }
            std::cout << "token='" << token << "'" << std::endl;
        }
        return is;
    }

    inline std::istream& ParseExportPgnMoves(std::istream& is, GameLog& log)
    {
        return is;
    }

    inline std::istream& ParseImportPgn(std::istream& is, GameLog& log)
    {
        ParseImportPgnTags(is, log);
        ParseImportPgnMoves(is, log);
        return is;
    }

    inline std::istream& ParseExportPgn(std::istream& is, GameLog& log)
    {
        ParseExportPgnTags(is, log);
        ParseExportPgnMoves(is, log);
        return is;
    }

    // inline std::istream& operator>>(std::istream& is, GameLog& log)
    // {
    //     return is;
    // }
}

#endif