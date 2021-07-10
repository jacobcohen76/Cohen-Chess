#include <cassert>
#include <iostream>

#include <cohen/chess.hpp>

void Init()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
}

int main(int argc, char* argv[])
{
    Init();
    for (int i = 2; i < argc; ++i)
    {
        cohen::chess::Board board = {};
        int repeat = std::stoi(argv[1]);
        for (int j = 0; j < repeat; ++j)
        {
            cohen::chess::SetFenPosition(argv[i], board);
            assert(argv[i] == cohen::chess::FormatFenPosition(board));
        }
    }
    return 0;
}
