#ifndef COHEN_CHESS_ENGINE_GAME_LOG_HPP_INCLUDED
#define COHEN_CHESS_ENGINE_GAME_LOG_HPP_INCLUDED

#include <map>
#include <string>
#include <vector>

namespace cohen_chess
{
    class GameLog
    {
    public:
        inline void clear() noexcept;

        inline bool contains(const std::string&) const;

        inline std::string& operator[](const std::string&);
        inline std::string& operator[](std::string&&);

        constexpr void push_back(const std::string&);
        constexpr void push_back(std::string&&);

        constexpr std::string& at(size_t);
        constexpr const std::string& at(size_t) const;

        constexpr std::string& operator[](size_t);
        constexpr const std::string& operator[](size_t) const;

        constexpr std::vector<std::string>::iterator begin() noexcept;
        constexpr std::vector<std::string>::const_iterator begin() const noexcept;
        constexpr std::vector<std::string>::const_iterator cbegin() const noexcept;

        constexpr std::vector<std::string>::iterator end() noexcept;
        constexpr std::vector<std::string>::const_iterator end() const noexcept;
        constexpr std::vector<std::string>::const_iterator cend() const noexcept;

        constexpr std::vector<std::string>::reverse_iterator rbegin() noexcept;
        constexpr std::vector<std::string>::const_reverse_iterator rbegin() const noexcept;
        constexpr std::vector<std::string>::const_reverse_iterator crbegin() const noexcept;

        constexpr std::vector<std::string>::reverse_iterator rend() noexcept;
        constexpr std::vector<std::string>::const_reverse_iterator rend() const noexcept;
        constexpr std::vector<std::string>::const_reverse_iterator crend() const noexcept;

    // private:
        std::vector<std::string> move_list;
        std::multimap<size_t, std::string> comment_map;
        std::map<std::string, std::string> tag_map;
    };

    inline void GameLog::clear() noexcept
    {
        move_list.clear();
        comment_map.clear();
        tag_map.clear();
    }

    inline bool GameLog::contains(const std::string& key) const
    {
        return tag_map.find(key) != tag_map.end();
    }

    inline std::string& GameLog::operator[](const std::string& key)
    {
        return tag_map[key];
    }

    inline std::string& GameLog::operator[](std::string&& key)
    {
        return tag_map[key];
    }

    constexpr void GameLog::push_back(const std::string& value)
    {
        move_list.push_back(value);
    }

    constexpr void GameLog::push_back(std::string&& value)
    {
        move_list.push_back(value);
    }

    constexpr std::string& GameLog::at(size_t index)
    {
        return move_list.at(index);
    }

    constexpr const std::string& GameLog::at(size_t index) const
    {
        return move_list.at(index);
    }

    constexpr std::string& GameLog::operator[](size_t ply)
    {
        return move_list[ply];
    }

    constexpr const std::string& GameLog::operator[](size_t ply) const
    {
        return move_list[ply];
    }

    constexpr std::vector<std::string>::iterator GameLog::begin() noexcept
    {
        return move_list.begin();
    }

    constexpr std::vector<std::string>::const_iterator GameLog::begin() const noexcept
    {
        return move_list.begin();
    }

    constexpr std::vector<std::string>::const_iterator GameLog::cbegin() const noexcept
    {
        return move_list.cbegin();
    }

    constexpr std::vector<std::string>::iterator GameLog::end() noexcept
    {
        return move_list.end();
    }

    constexpr std::vector<std::string>::const_iterator GameLog::end() const noexcept
    {
        return move_list.end();
    }

    constexpr std::vector<std::string>::const_iterator GameLog::cend() const noexcept
    {
        return move_list.cend();
    }

    constexpr std::vector<std::string>::reverse_iterator GameLog::rbegin() noexcept
    {
        return move_list.rbegin();
    }

    constexpr std::vector<std::string>::const_reverse_iterator GameLog::rbegin() const noexcept
    {
        return move_list.rbegin();
    }

    constexpr std::vector<std::string>::const_reverse_iterator GameLog::crbegin() const noexcept
    {
        return move_list.crbegin();
    }

    constexpr std::vector<std::string>::reverse_iterator GameLog::rend() noexcept
    {
        return move_list.rend();
    }

    constexpr std::vector<std::string>::const_reverse_iterator GameLog::rend() const noexcept
    {
        return move_list.rend();
    }

    constexpr std::vector<std::string>::const_reverse_iterator GameLog::crend() const noexcept
    {
        return move_list.crend();
    }
}

#endif