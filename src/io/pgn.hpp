#ifndef COHEN_CHESS_IO_PGN_HPP_INCLUDED
#define COHEN_CHESS_IO_PGN_HPP_INCLUDED

#include <engine/game_log.hpp>

#include <iostream>

namespace cohen_chess
{
    inline std::istream& ParsePgnTags(std::istream& is, GameLog& log)
    {

        return is;
    }

    inline std::istream& ParsePGN(std::istream& is, GameLog& log)
    {
        while (is.get() == '[')
        {
            std::string key, value;
            is >> std::ws >> key;
            if (is >> std::ws, is.get() != '"')
            {
                return is.setstate(std::iostream::failbit), is;
            }
            std::getline(is, value, '"');
            if (is >> std::ws, is.get() != ']')
            {
                return is.setstate(std::iostream::failbit), is;
            }
            is >> std::ws;
            log[key] = value;
        }
        is.unget();

        
        return is;
    }

    inline std::istream& operator>>(std::istream& is, GameLog& log)
    {
        return ParsePGN(is, log);
    }
}

#endif