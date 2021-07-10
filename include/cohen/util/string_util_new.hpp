#ifndef COHEN_UTIL_STRING_UTIL_HPP_INCLUDED
#define COHEN_UTIL_STRING_UTIL_HPP_INCLUDED

#include <algorithm>
#include <concepts>
#include <cstdint>
#include <vector>

namespace cohen
{
    template <typename T>
    concept Character = std::same_as<char>     ||
                        std::same_as<wchar_t>  ||
                        std::same_as<char8_t>  ||
                        std::same_as<char16_t> ||
                        std::same_as<char32_t>;

    template <Character T1, Character T2>
    inline std::basic_string<std::common_type_t<T1, T2>> HorizonalMerge(std::basic_string<T1> lhs, std::basic_string<T2> rhs, size_t gap_size,)
}

#endif
