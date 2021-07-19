#ifndef COHEN_UTIL_STRING_UTIL_HPP_INCLUDED
#define COHEN_UTIL_STRING_UTIL_HPP_INCLUDED

#include <algorithm>
#include <concepts>
#include <cstdint>
#include <vector>

namespace cohen::util
{
    template <typename T>
    concept Character = std::same_as<T, char>     ||
                        std::same_as<T, wchar_t>  ||
                        std::same_as<T, char8_t>  ||
                        std::same_as<T, char16_t> ||
                        std::same_as<T, char32_t>;

    // template <Character T>
    // inline std::vector<std::basic_string<T>> Tokenize(std::basic_string<T>&& str)
    // {
    //     std::vector<std::basic_string<T>> lines;
    // }

    // template <Character T1, Character T2>
    // inline auto HorizontalMerge(const std::basic_string<T1>& lhs,
    //                             const std::basic_string<T2>& rhs,
    //                             size_t gap_size = 3,
    //                             std::common_type_t<T1, T2> space = ' ') noexcept
    //     -> std::basic_string<std::common_type_t<T1, T2>>
    // {

    // }
}

#endif
