#include "cohen_chess.h"

#include <iostream>

int main(int argc, char* argv[])
{
    cohen_chess::Init();
    long num = 0xFFFFFF3FAAAFAFA8;
    std::cout << cohen_chess::PopCountLookup(num) << std::endl;
    return 0;
}
