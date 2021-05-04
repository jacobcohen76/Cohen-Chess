#include "cohen_chess.h"

using namespace cohen_chess;

int main(int argc, char* argv[])
{
    Board board;
    AsciiBoard ascii_board;
    SetFenPosition("rnbqkbnr/ppp1pppp/8/3p4/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 0 1", board);
    for (Piece piece = kPieceNone; piece < kPieceNB; ++piece)
    {
        ascii_board.set_bb(board.bitboards[piece], '1');
        std::cout << "piece=" << piece << ":" << std::endl;
        std::cout << ascii_board << std::endl;
        ascii_board.clear();
    }
    ascii_board.set_board(board);
    std::cout << "board:" << std::endl;
    std::cout << ascii_board << std::endl;
    ascii_board.clear();
    FormatFenPosition(std::cout, board) << std::endl;
    return 0;
}
