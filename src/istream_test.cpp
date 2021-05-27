#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char* argv[])
{
    std::string test_str = "   123 456 abc789def   ghi123jkl 456";
    std::istringstream is(test_str);
    
    int num;
    is >> num, std::cout << "num=" << num << "," << "is.fail()=" << is.fail() << "," << "is.peek()=" << char(is.peek()) << std::endl;
    is >> num, std::cout << "num=" << num << "," << "is.fail()=" << is.fail() << "," << "is.peek()=" << char(is.peek()) << std::endl;
    is >> num, std::cout << "num=" << num << "," << "is.fail()=" << is.fail() << "," << "is.peek()=" << char(is.peek()) << std::endl;
    is >> num, std::cout << "num=" << num << "," << "is.fail()=" << is.fail() << "," << "is.peek()=" << char(is.peek()) << std::endl;
    is >> num, std::cout << "num=" << num << "," << "is.fail()=" << is.fail() << "," << "is.peek()=" << char(is.peek()) << std::endl;
    is >> num, std::cout << "num=" << num << "," << "is.fail()=" << is.fail() << "," << "is.peek()=" << char(is.peek()) << std::endl;
    return 0;
}