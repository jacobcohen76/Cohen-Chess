#include "string_util.h"

#include <string>
#include <vector>

#include <iostream>

namespace cohen_chess
{
    namespace util
    {
        std::string HorizontalMerge(const std::string& str1, const std::string& str2, const std::string& gap, char space)
        {
            std::vector<std::string> tokens1 = Tokenize(str1, '\n');
            std::vector<std::string> tokens2 = Tokenize(str2, '\n');
            std::string merged;
            size_t i, longest1 = LongestString(tokens1), longest2 = LongestString(tokens2);
            PadRight(tokens1, longest1, space);
            PadRight(tokens2, longest2, space);
            for(i = 0; i < std::min(tokens1.size(), tokens2.size()); ++i)
            {
                merged += tokens1.at(i);
                merged += gap;
                merged += tokens2.at(i);
                merged += '\n';
            }
            for(; i < tokens1.size(); ++i)
            {
                merged += tokens1.at(i);
                merged += gap;
                merged += std::string(longest2, space);
                merged += '\n';
            }
            for(; i < tokens2.size(); ++i)
            {
                merged += std::string(longest1, space);
                merged += gap;
                merged += tokens2.at(i);
                merged += '\n';
            }
            if(merged.size()) merged.pop_back();
            return merged;
        }
    };
};