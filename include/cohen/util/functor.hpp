#ifndef COHEN_UTIL_FUNCTOR_HPP_INCLDED
#define COHEN_UTIL_FUNCTOR_HPP_INCLDED

#include <concepts>
#include <functional>

namespace cohen::util::functor
{
    template <typename T, typename Signature>
    concept Functor = std::convertible_to<T, std::function<Signature>>;
}

namespace cohen
{
    using cohen::util::functor::Functor;
}

#endif
