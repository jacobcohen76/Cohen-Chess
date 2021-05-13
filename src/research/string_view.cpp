#include <iostream>
#include <string_view>

int main(int argc, char* argv[])
{
    const char* alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::string_view str_view(alphabet, alphabet + 5);
    auto itr = std::begin(str_view);
    while (itr < std::end(str_view))
    {
        std::cout << *itr++ << std::endl;
    }
    return 0;
}