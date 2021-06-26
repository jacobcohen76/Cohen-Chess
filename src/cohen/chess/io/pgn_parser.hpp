
#include <engine/game_log.hpp>
#include <io/parse.hpp>

#include <iostream>
#include <sstream>

namespace cohen
{
    namespace pgn
    {
        inline bool IsPgnResult(const std::string& token)
        {
            return token == "1-0" || token == "0-1" || token == "1/2-1/2" || token == "*";
        }

        inline std::istream& ParsePgnImportTag(std::istream& is, GameLog& log)
        {
            std::string key, value;
            if (is >> std::ws, is.get() != '[')
                throw ParseError("expected '[' token");
            is >> std::ws >> key;
            if (is >> std::ws, is.get() != '"')
                throw ParseError("expected \" token");
            std::getline(is, value, '"');
            if (is >> std::ws, is.get() != ']')
                throw ParseError("expected ']' token");
            log[key] = value;
            return is;
        }

        inline std::istream& ParsePgnExportTag(std::istream& is, GameLog& log)
        {
            std::string key, value;
            if (is.get() != '[')
                throw ParseError("expected '[' token");
            is >> key >> std::ws;
            if (is.get() != '"')
                throw ParseError("expected \" token");
            std::getline(is, value, '"');
            if (is.get() != ']')
                throw ParseError("expected ']' token");
            if (log.contains_tag(key))
                throw ParseError("duplicate tag key");
            log[key] = value;
            return is;
        }

        inline std::istream& ParsePgnImportTags(std::istream& is, GameLog& log)
        {
            std::string line;
            while (std::getline(is, line), line.find('[') != std::string::npos)
            {
                std::istringstream line_iss(line);
                ParsePgnImportTag(line_iss, log);
            }
            return is;
        }

        inline std::istream& ParsePgnExportTags(std::istream& is, GameLog& log)
        {
            std::string line;
            while (std::getline(is, line), line.size() == 0)
            {
                std::istringstream line_iss(line);
                ParsePgnExportTag(line_iss, log);
                if (line_iss.get() != -1)
                    throw ParseError("expected '\\n' token");
            }
            return is;
        }

        inline std::istream& ParsePgnImportMoveNumber(std::istream& is, size_t& ply)
        {
            if (!std::isdigit(is.peek()))
                throw ParseError("expected integer token");
            is >> ply;
            return is;
        }

        inline std::istream& ParsePgnImportMovetext(std::istream& is, GameLog& log)
        {
            std::string token;
            size_t ply = 0;
            char curr, next;
            while (is >> std::ws, !is.eof() && !IsPgnResult(token))
            {
                curr = is.peek();
                if (curr == ';')
                {
                    std::getline(is, token);
                    log.comments(ply).push_back(token);
                }
                else if (curr == '{')
                {
                    std::getline(is, token, '}');
                    log.comments(ply).push_back(token + '}');
                }
                else if (curr == '*')
                {
                    token = is.get();
                }
                else if (std::isdigit(curr))
                {
                    curr = is.get(), next = is.peek(), is.unget();
                    if ((curr == '0' || curr == '1') && (next == '-' || next == '/'))
                    {
                        is >> token;
                    }
                    else
                    {
                        is >> ply >> std::ws >> curr, next = is.peek();
                        ply = (ply - 1) * 2 + (next == '.');
                        if (next == '.' && (is.get(), is.get() != '.'))
                            throw ParseError("expected '...' token");
                    }
                }
                else
                {
                    is >> token;
                    log[ply++] = token;
                }
            }
            return is;
        }

        inline std::istream& ParsePgnExportMovetext(std::istream& is, GameLog& log)
        {
            std::string token;
            size_t ply = 0;
            char curr, next;
            while (!is.eof() && !IsPgnResult(token))
            {
                curr = is.peek();
                if (curr == ';')
                {
                    std::getline(is, token);
                    log.comments(ply).push_back(token);
                }
                else if (curr == '{')
                {
                    std::getline(is, token, '}');
                    log.comments(ply).push_back(token + '}');
                }
                else if (curr == '*')
                {
                    token = is.get();
                }
                else if (std::isdigit(curr))
                {
                    curr = is.get(), next = is.peek(), is.unget();
                    if ((curr == '0' || curr == '1') && (next == '-' || next == '/'))
                    {
                        is >> token;
                    }
                    else
                    {
                        is >> ply >> curr, next = is.peek();
                        ply = (ply - 1) * 2 + (next == '.');
                        if (next == '.' && (is.get(), is.get() != '.'))
                            throw ParseError("expected '...' token");
                    }
                }
                else
                {
                    is >> token;
                    log[ply++] = token;
                }
            }
            return is;
        }

        inline std::istream& ParsePgnImport(std::istream& is, GameLog& log)
        {
            ParsePgnImportTags(is, log);
            ParsePgnImportMovetext(is, log);
            return is;
        }

        inline std::istream& ParsePgnExport(std::istream& is, GameLog& log)
        {
            ParsePgnExportTags(is, log);
            ParsePgnExportMovetext(is, log);
            return is;
        }
    }

    using pgn::ParsePgnImport;
    using pgn::ParsePgnExport;
}
