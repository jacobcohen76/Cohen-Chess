#include <fstream>
#include <iostream>
#include <locale>
#include <string>

int main(int argc, char* argv[])
{
    std::ifstream fis("hello_world!.txt");
    while (!fis.eof())
    {
        auto token = fis.get();
        std::cout << "get='" << char(token) << "'," << token << std::endl;
    }
    return 0;
}
