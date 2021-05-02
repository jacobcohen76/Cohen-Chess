#include "cohen_chess.h"

using namespace cohen_chess;

template <Color side>
void TestAsciiBoard()
{
    AsciiBoard<side> ascii_board;

    ascii_board.clear();
    ascii_board.set_bb(RankBB(kRank1), '1');
    ascii_board.set_bb(RankBB(kRank2), '2');
    ascii_board.set_bb(RankBB(kRank3), '3');
    ascii_board.set_bb(RankBB(kRank4), '4');
    ascii_board.set_bb(RankBB(kRank5), '5');
    ascii_board.set_bb(RankBB(kRank6), '6');
    ascii_board.set_bb(RankBB(kRank7), '7');
    ascii_board.set_bb(RankBB(kRank8), '8');
    std::cout << "Rank" << std::endl << ascii_board << std::endl;

    ascii_board.clear();
    ascii_board.set_bb(FileBB(kFileA), 'A');
    ascii_board.set_bb(FileBB(kFileB), 'B');
    ascii_board.set_bb(FileBB(kFileC), 'C');
    ascii_board.set_bb(FileBB(kFileD), 'D');
    ascii_board.set_bb(FileBB(kFileE), 'E');
    ascii_board.set_bb(FileBB(kFileF), 'F');
    ascii_board.set_bb(FileBB(kFileG), 'G');
    ascii_board.set_bb(FileBB(kFileH), 'H');
    std::cout << "File" << std::endl << ascii_board << std::endl;

    ascii_board.clear();
    ascii_board.set_bb(DiagBB(kDiag1), '1');
    ascii_board.set_bb(DiagBB(kDiag2), '2');
    ascii_board.set_bb(DiagBB(kDiag3), '3');
    ascii_board.set_bb(DiagBB(kDiag4), '4');
    ascii_board.set_bb(DiagBB(kDiag5), '5');
    ascii_board.set_bb(DiagBB(kDiag6), '6');
    ascii_board.set_bb(DiagBB(kDiag7), '7');
    ascii_board.set_bb(DiagBB(kDiag8), '8');
    ascii_board.set_bb(DiagBB(kDiag9), '9');
    ascii_board.set_bb(DiagBB(kDiagA), 'A');
    ascii_board.set_bb(DiagBB(kDiagB), 'B');
    ascii_board.set_bb(DiagBB(kDiagC), 'C');
    ascii_board.set_bb(DiagBB(kDiagD), 'D');
    ascii_board.set_bb(DiagBB(kDiagE), 'E');
    ascii_board.set_bb(DiagBB(kDiagF), 'F');
    std::cout << "Diag" << std::endl << ascii_board << std::endl;

    ascii_board.clear();
    ascii_board.set_bb(AntiBB(kAnti1), '1');
    ascii_board.set_bb(AntiBB(kAnti2), '2');
    ascii_board.set_bb(AntiBB(kAnti3), '3');
    ascii_board.set_bb(AntiBB(kAnti4), '4');
    ascii_board.set_bb(AntiBB(kAnti5), '5');
    ascii_board.set_bb(AntiBB(kAnti6), '6');
    ascii_board.set_bb(AntiBB(kAnti7), '7');
    ascii_board.set_bb(AntiBB(kAnti8), '8');
    ascii_board.set_bb(AntiBB(kAnti9), '9');
    ascii_board.set_bb(AntiBB(kAntiA), 'A');
    ascii_board.set_bb(AntiBB(kAntiB), 'B');
    ascii_board.set_bb(AntiBB(kAntiC), 'C');
    ascii_board.set_bb(AntiBB(kAntiD), 'D');
    ascii_board.set_bb(AntiBB(kAntiE), 'E');
    ascii_board.set_bb(AntiBB(kAntiF), 'F');
    std::cout << "Anti" << std::endl << ascii_board << std::endl;
}

int main(int argc, char* argv[])
{
    TestAsciiBoard<kWhite>();
    TestAsciiBoard<kBlack>();

    AsciiBoard ascii_board;
    Board board = {};
    for (File file = kFileA; file < kFileNB; ++file)
    {
        board.put(kWhitePawn, MakeSquare(kRank2, file));
    }
    board.make(MakeMove(kE2, kE4));
    ascii_board.set_board(board);
    std::cout << "Board" << std::endl << ascii_board << std::endl;

    board.clear();
    SetFenPosition("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", board);
    ascii_board.set_board(board);
    std::cout << "Board" << std::endl << ascii_board << std::endl;

    board.clear();
    std::cout << "Board" << std::endl << ascii_board << std::endl;
    return 0;
}
