#ifndef COHEN_UTIL_FUNCTOR_HPP_INCLDED
#define COHEN_UTIL_FUNCTOR_HPP_INCLDED

#include <concepts>
#include <functional>

namespace cohen::util::functor
{
    template <typename T, typename signature>
    concept Functor = std::convertible_to<T, std::function<signature>>;
}

namespace cohen
{
    using cohen::util::functor::Functor;
}

#endif
