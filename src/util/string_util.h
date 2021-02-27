#ifndef COHEN_CHESS_UTIL_STRING_UTIL_H_INCLUDED
#define COHEN_CHESS_UTIL_STRING_UTIL_H_INCLUDED

#include <algorithm>
#include <string>
#include <vector>

namespace cohen_chess
{
    namespace util
    {
        inline std::vector<std::string> Tokenize(const char* c_str, char delim)
        {
            std::vector<std::string> tokens;
            do
            {
                const char* begin = c_str;
                while(*c_str != delim && *c_str)
                {
                    ++c_str;
                }
                tokens.push_back(std::string(begin, c_str));
            } while(*c_str++);
            return tokens;
        }

        inline std::vector<std::string> Tokenize(const std::string& str, char delim)
        {
            return Tokenize(str.c_str(), delim);
        }

        inline size_t LongestString(const std::vector<std::string>& strings)
        {
            size_t longest = 0;
            for(const std::string& s : strings)
            {
                longest = std::max(longest, s.size());
            }
            return longest;
        }

        inline void PadRight(std::vector<std::string>& strings, size_t longest, char pad)
        {
            for(size_t i = 0; i < strings.size(); ++i)
            {
                strings[i].append(std::string(longest - strings[i].size(), pad));
            }
        }

        inline void PadRight(std::vector<std::string>& strings, char pad)
        {
            return PadRight(strings, LongestString(strings), pad);
        }

        inline void PadLeft(std::vector<std::string>& strings, size_t longest, char pad)
        {
            for(size_t i = 0; i < strings.size(); ++i)
            {
                strings[i] = std::string(longest - strings[i].size(), pad).append(strings[i]);
            }
        }

        inline void PadLeft(std::vector<std::string>& strings, char pad)
        {
            return PadLeft(strings, LongestString(strings), pad);
        }

        std::string HorizontalMerge(const std::string&, const std::string&, const std::string&, char = ' ');
    };
};

#endif
