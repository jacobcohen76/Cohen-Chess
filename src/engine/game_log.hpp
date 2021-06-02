#ifndef COHEN_CHESS_ENGINE_GAME_LOG_HPP_INCLUDED
#define COHEN_CHESS_ENGINE_GAME_LOG_HPP_INCLUDED

#include <map>
#include <string>
#include <vector>

namespace cohen_chess
{
    struct GameLog
    {
        inline void clear() noexcept;

        inline bool contains_tag(const std::string&) const;
        inline bool contains_comment(const size_t&) const;
        inline bool contains_move(const size_t&) const;

        inline std::string& operator[](const std::string&);
        inline const std::string& operator[](const std::string&) const;

        inline std::string& operator[](const size_t&);
        inline const std::string& operator[](const size_t&) const;

        inline std::vector<std::string>& comments(const size_t&);
        inline const std::vector<std::string>& comments(const size_t&) const;

        inline std::map<size_t, std::string>::iterator begin() noexcept;
        inline std::map<size_t, std::string>::const_iterator begin() const noexcept;
        inline std::map<size_t, std::string>::const_iterator cbegin() const noexcept;

        inline std::map<size_t, std::string>::iterator end() noexcept;
        inline std::map<size_t, std::string>::const_iterator end() const noexcept;
        inline std::map<size_t, std::string>::const_iterator cend() const noexcept;

        inline std::map<size_t, std::string>::reverse_iterator rbegin() noexcept;
        inline std::map<size_t, std::string>::const_reverse_iterator rbegin() const noexcept;
        inline std::map<size_t, std::string>::const_reverse_iterator crbegin() const noexcept;

        inline std::map<size_t, std::string>::reverse_iterator rend() noexcept;
        inline std::map<size_t, std::string>::const_reverse_iterator rend() const noexcept;
        inline std::map<size_t, std::string>::const_reverse_iterator crend() const noexcept;

        std::map<std::string, std::string> tag_map;
        std::map<size_t, std::vector<std::string>> comment_map;
        std::map<size_t, std::string> move_map;
    };

    inline void GameLog::clear() noexcept
    {
        tag_map.clear();
        comment_map.clear();
        move_map.clear();
    }

    inline bool GameLog::contains_tag(const std::string& key) const
    {
        return tag_map.contains(key);
    }

    inline bool GameLog::contains_comment(const size_t& halfmove) const
    {
        return comment_map.contains(halfmove);
    }

    inline bool GameLog::contains_move(const size_t& halfmove) const
    {
        return move_map.contains(halfmove);
    }

    inline std::string& GameLog::operator[](const std::string& key)
    {
        return tag_map[key];
    }

    inline const std::string& GameLog::operator[](const std::string& key) const
    {
        return tag_map.at(key);
    }

    inline std::string& GameLog::operator[](const size_t& halfmove)
    {
        return move_map[halfmove];
    }

    inline const std::string& GameLog::operator[](const size_t& halfmove) const
    {
        return move_map.at(halfmove);
    }

    inline std::vector<std::string>& GameLog::comments(const size_t& halfmove)
    {
        return comment_map[halfmove];
    }

    inline const std::vector<std::string>& GameLog::comments(const size_t& halfmove) const
    {
        return comment_map.at(halfmove);
    }

    inline std::map<size_t, std::string>::iterator GameLog::begin() noexcept
    {
        return move_map.begin();
    }

    inline std::map<size_t, std::string>::const_iterator GameLog::begin() const noexcept
    {
        return move_map.begin();
    }

    inline std::map<size_t, std::string>::const_iterator GameLog::cbegin() const noexcept
    {
        return move_map.cbegin();
    }

    inline std::map<size_t, std::string>::iterator GameLog::end() noexcept
    {
        return move_map.end();
    }

    inline std::map<size_t, std::string>::const_iterator GameLog::end() const noexcept
    {
        return move_map.end();
    }

    inline std::map<size_t, std::string>::const_iterator GameLog::cend() const noexcept
    {
        return move_map.cend();
    }

    inline std::map<size_t, std::string>::reverse_iterator GameLog::rbegin() noexcept
    {
        return move_map.rbegin();
    }

    inline std::map<size_t, std::string>::const_reverse_iterator GameLog::rbegin() const noexcept
    {
        return move_map.rbegin();
    }

    inline std::map<size_t, std::string>::const_reverse_iterator GameLog::crbegin() const noexcept
    {
        return move_map.crbegin();
    }

    inline std::map<size_t, std::string>::reverse_iterator GameLog::rend() noexcept
    {
        return move_map.rend();
    }

    inline std::map<size_t, std::string>::const_reverse_iterator GameLog::rend() const noexcept
    {
        return move_map.rend();
    }

    inline std::map<size_t, std::string>::const_reverse_iterator GameLog::crend() const noexcept
    {
        return move_map.crend();
    }
}

#endif