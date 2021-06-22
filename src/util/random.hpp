#ifndef COHEN_CHESS_UTIL_RANDOM_HPP_INCLUDED
#define COHEN_CHESS_UTIL_RANDOM_HPP_INCLUDED

#include <cstdint>

namespace cohen_chess
{
    template <uint64_t a = 6364136223846793005, uint64_t c = 1442695040888963407>
    class LinearCongruentialGenerator
    {
    public:
        constexpr LinearCongruentialGenerator(uint64_t seed = 0)
            : state(seed) {}

        constexpr uint64_t operator()()
        {
            return state = state * a + c;
        }

    private:
        uint64_t state;
    };
}

#endif