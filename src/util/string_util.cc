#include "string_util.h"

namespace cohen_chess
{
    namespace util
    {
        template <>
        std::string HorizontalMerge<false>(const std::string& lhs, const std::string& rhs, const std::string& gap, char space)
        {
            std::vector<std::string> lines_lhs = Tokenize(lhs, '\n');
            std::vector<std::string> lines_rhs = Tokenize(rhs, '\n');
            std::string merged;
            size_t longest_line_lhs = LongestString(lines_lhs);
            size_t longest_line_rhs = LongestString(lines_rhs);
            size_t i;
            PadLeft(lines_lhs, longest_line_lhs, space);
            PadLeft(lines_rhs, longest_line_rhs, space);
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