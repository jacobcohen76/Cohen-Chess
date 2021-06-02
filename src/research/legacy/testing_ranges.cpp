#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <ranges>

template <typename OutStream, typename Iterator>
OutStream& PrintTo(OutStream& os, Iterator first, Iterator last)
{
    os << "[";
    while (first != last)
    {
        os << *first;
        if (++first != last)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

int square(int n)
{
    return n * n;
}

int main(int argc, char* argv[])
{
    std::array<uint64_t, 10> array(std::views::iota(1, 10));
    PrintTo(std::cout, array.begin(), array.end());
    std::cout << std::endl << std::endl;

    for (int i : std::views::iota(1, 10) | std::views::transform(square))
    {
        std::cout << i << std::endl;
    }
    return 0;
}
