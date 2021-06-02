#include <cohen_chess.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <locale>

int main(int argc, char* argv[])
{
    using namespace cohen_chess;
    std::cout << "kNorth" << std::endl << AsciiBoard(bitboard::kShiftMask<kNorth>) << std::endl;
    std::cout << "kEast" << std::endl << AsciiBoard(bitboard::kShiftMask<kEast>) << std::endl;
    std::cout << "kSouth" << std::endl << AsciiBoard(bitboard::kShiftMask<kSouth>) << std::endl;
    std::cout << "kWest" << std::endl << AsciiBoard(bitboard::kShiftMask<kWest>) << std::endl;
    std::cout << "kNorthEast" << std::endl << AsciiBoard(bitboard::kShiftMask<kNorthEast>) << std::endl;
    std::cout << "kSouthEast" << std::endl << AsciiBoard(bitboard::kShiftMask<kSouthEast>) << std::endl;
    std::cout << "kSouthWest" << std::endl << AsciiBoard(bitboard::kShiftMask<kSouthWest>) << std::endl;
    std::cout << "kNorthWest" << std::endl << AsciiBoard(bitboard::kShiftMask<kNorthWest>) << std::endl;
    std::cout << "kNorthNorth" << std::endl << AsciiBoard(bitboard::kShiftMask<kNorthNorth>) << std::endl;
    std::cout << "kEastEast" << std::endl << AsciiBoard(bitboard::kShiftMask<kEastEast>) << std::endl;
    std::cout << "kSouthSouth" << std::endl << AsciiBoard(bitboard::kShiftMask<kSouthSouth>) << std::endl;
    std::cout << "kWestWest" << std::endl << AsciiBoard(bitboard::kShiftMask<kWestWest>) << std::endl;
    std::cout << "kNorthNorthEast" << std::endl << AsciiBoard(bitboard::kShiftMask<kNorthNorthEast>) << std::endl;
    std::cout << "kNorthNorthWest" << std::endl << AsciiBoard(bitboard::kShiftMask<kNorthNorthWest>) << std::endl;
    std::cout << "kEastEastNorth" << std::endl << AsciiBoard(bitboard::kShiftMask<kEastEastNorth>) << std::endl;
    std::cout << "kEastEastSouth" << std::endl << AsciiBoard(bitboard::kShiftMask<kEastEastSouth>) << std::endl;
    std::cout << "kSouthSouthEast" << std::endl << AsciiBoard(bitboard::kShiftMask<kSouthSouthEast>) << std::endl;
    std::cout << "kSouthSouthWest" << std::endl << AsciiBoard(bitboard::kShiftMask<kSouthSouthWest>) << std::endl;
    std::cout << "kWestWestNorth" << std::endl << AsciiBoard(bitboard::kShiftMask<kWestWestNorth>) << std::endl;
    std::cout << "kWestWestSouth" << std::endl << AsciiBoard(bitboard::kShiftMask<kWestWestSouth>) << std::endl;
    std::cout << "kDirectionNone" << std::endl << AsciiBoard(bitboard::kShiftMask<kDirectionNone>) << std::endl;
    return 0;
}
