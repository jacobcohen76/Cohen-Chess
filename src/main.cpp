#include "cohen_chess.h"

#include <iostream>

int main(int argc, char* argv[])
{
    cohen_chess::Init();
    std::cout << cohen_chess::DeBruijnBitScanForward(0) << std::endl;
    return 0;
}
