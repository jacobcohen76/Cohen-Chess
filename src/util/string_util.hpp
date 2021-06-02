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

        std::string HorizontalMerge(const std::string& lhs, const std::string& rhs, const std::string& gap, char space=' ')
        {
            std::vector<std::string> lines_lhs = Tokenize(lhs, '\n');
            std::vector<std::string> lines_rhs = Tokenize(rhs, '\n');
            std::string merged;
            size_t longest_line_lhs = LongestString(lines_lhs);
            size_t longest_line_rhs = LongestString(lines_rhs);
            size_t i;
            PadRight(lines_lhs, longest_line_lhs, space);
            PadRight(lines_rhs, longest_line_rhs, space);
            for(i = 0; i < std::min(lines_lhs.size(), lines_rhs.size()); ++i)
            {
                merged += lines_lhs.at(i);
                merged += gap;
                merged += lines_rhs.at(i);
                merged += '\n';
            }
            while(i < lines_lhs.size())
            {
                merged += lines_lhs.at(i++);
                merged += gap;
                merged += std::string(longest_line_rhs, space);
                merged += '\n';
            }
            while(i < lines_rhs.size())
            {
                merged += std::string(longest_line_lhs, space);
                merged += gap;
                merged += lines_rhs.at(i++);
                merged += '\n';
            }
            if(merged.size())
            {
                merged.pop_back();
            }
            return merged;
        }
    }
}

#endif