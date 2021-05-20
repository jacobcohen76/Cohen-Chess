#include <iostream>
#include <map>
#include <string>

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& pair)
{
    return os << '(' << pair.first << ',' << pair.second << ')';
}

int main(int argc, char* argv[])
{
    std::cout << "Hello World!" << std::endl;

    std::multimap<size_t, std::string> comment_map;
    comment_map.insert(std::make_pair(1, "Testing 123!"));
    comment_map.insert(std::make_pair(3, "Hello World!"));
    comment_map.insert(std::make_pair(3, "Goodbye World..."));

    auto range_pair = comment_map.equal_range(3);
    for (auto itr = range_pair.first; itr != range_pair.second; ++itr)
    {
        std::cout << *itr << std::endl;
    }

    int num = std::stoi("123...");
    std::cout << num << std::endl;
    return 0;
}