#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    std::string s = "abcdefg";
    if (s.contains("abc"))
    {
        std::cout << "contains" << std::endl;
    }
    return 0;
}