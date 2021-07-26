#include <cassert>

#include <cohen/chess.hpp>
#include <cohen/util.hpp>

using namespace cohen;
using namespace cohen::chess;

void Init()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
}

void TestMagics()
{
    auto assert_magic = [](Functor<Bitboard(Bitboard, Square)> auto control,
                           Functor<Bitboard(Bitboard, Square)> auto testing,
                           Bitboard mask, Square sq) -> void
    {
        Bitboard occ = kEmptyBB;
        do
        {
            assert(control(occ, sq) == testing(occ, sq));
        }
        while ((occ = (occ - mask) & mask));
    };
    for (Square sq = kA1; sq < kSquareNB; ++sq)
    {
        assert_magic(RayBishopAttacks, FancyMagicBishopAttacks, MagicBishopMask(sq), sq);
        assert_magic(RayBishopAttacks, BlackMagicBishopAttacks, MagicBishopMask(sq), sq);
        assert_magic(RayRookAttacks,   FancyMagicRookAttacks,   MagicRookMask(sq),   sq);
        assert_magic(RayRookAttacks,   BlackMagicRookAttacks,   MagicRookMask(sq),   sq);
    }
    using namespace cohen::chess::magics;
    std::cout << "kFancyMagicAttackTable.size() = " << kFancyMagicAttackTable.size() << std::endl;
    std::cout << "kBlackMagicAttackTable.size() = " << kBlackMagicAttackTable.size() << std::endl;
}

void TestAsciiBoard()
{
    AsciiBoard ascii_board = {};
    ascii_board.fill(RayBB<kNorth>(kE4));
    ascii_board.fill(RayBB<kEast>(kE4));
    ascii_board[kE4] = 'x';
    std::cout << ascii_board << std::endl, ascii_board.flip();
    std::cout << ascii_board << std::endl, ascii_board.flip();
}

void TestPawnAttacks(Square sq)
{
    AsciiBoard ascii_board = {};
    ascii_board.fill(PawnAttacks(sq, kWhite), 'w');
    ascii_board.fill(PawnAttacks(sq, kBlack), 'b');
    ascii_board[sq] = 'x';
    std::cout << ascii_board << std::endl;
}

void TestKingAttacks(Square sq)
{
    AsciiBoard ascii_board = {};
    ascii_board.fill(KingAttacks(sq));
    ascii_board[sq] = 'x';
    std::cout << ascii_board << std::endl;
}

int main(int argc, char* argv[])
{
    Init();
    TestMagics();
    TestAsciiBoard();
    for (Square sq = kA1; sq < kSquareNB; ++sq)
    {
        TestPawnAttacks(sq);
        TestKingAttacks(sq);
    }
    MoveList move_list;
    move_list.push(MakeMove(kE1, kE4));
    move_list.push(kMoveNone);
    move_list.push(kMoveNull);
    for (Move move : move_list)
    {
        std::cout << CoordinateString(FromSquare(move)) << "->" << CoordinateString(ToSquare(move)) << std::endl;
    }
    return 0;
}
