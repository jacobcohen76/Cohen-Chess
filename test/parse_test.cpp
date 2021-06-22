#include <exception>
#include <iostream>
#include <string>

namespace cohen_chess::io::parse
{
    struct ParseError : public std::runtime_error
    {
        using std::runtime_error::runtime_error;
    };
}

namespace cohen_chess
{
    using io::parse::ParseError;
}

int stoi(const char* str)
{
    throw cohen_chess::ParseError("Help!");
    return 0;
}

int main(int argc, char* argv[])
{
    auto x = stoi("abc");
    std::cout << x << std::endl;
    return 0;
}