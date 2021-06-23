#ifndef COHEN_CHESS_UTIL_STRING_UTIL_HPP_INCLUDED
#define COHEN_CHESS_UTIL_STRING_UTIL_HPP_INCLUDED

#include <algorithm>
#include <string_view>
#include <vector>

namespace cohen_chess
{
    inline std::vector<std::string_view> Tokenize(std::string_view str_view, char delim)
    {
        std::vector<std::string_view> tokens;
        auto itr = std::begin(str_view);
        do
        {
            auto start = itr;
            while (itr < std::end(str_view) && *itr != delim)
            {
                ++itr;
            }
            tokens.push_back(std::string_view(start, itr));
        }
        while (++itr < std::end(str_view));
        return tokens;
    }

    inline std::string HorizontalMerge(std::string_view lhs, std::string_view rhs, std::string_view gap)
    {
        
    }
}

#endif
