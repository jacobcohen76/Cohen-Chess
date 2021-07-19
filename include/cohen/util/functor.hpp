#ifndef COHEN_UTIL_FUNCTOR_HPP_INCLDED
#define COHEN_UTIL_FUNCTOR_HPP_INCLDED

#include <concepts>
#include <functional>

namespace cohen::util::functor
{
    template <typename T>
    inline constexpr bool kIsTypeSignature = false;

    template <typename ReturnType, typename... ArgTypes>
    inline constexpr bool kIsTypeSignature<ReturnType(ArgTypes...)> = true;

    template <typename T>
    concept TypeSignature = kIsTypeSignature<T>;

    template <typename T, typename TypeSignature>
    concept Functor = std::convertible_to<T, std::function<TypeSignature>>;
}

namespace cohen
{
    using cohen::util::functor::TypeSignature;
    using cohen::util::functor::Functor;
}

#endif
