#include <cohen_chess.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <locale>

int main(int argc, char* argv[])
{
    std::cout << "kNorth"           << std::endl << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kNorth>)           << std::endl;
    std::cout << "kEast"            << std::endl << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kEast>)            << std::endl;
    std::cout << "kSouth"           << std::endl << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kSouth>)           << std::endl;
    std::cout << "kWest"            << std::endl << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kWest>)            << std::endl;
    std::cout << "kNorthEast"       << std::endl << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kNorthEast>)       << std::endl;
    std::cout << "kSouthEast"       << std::endl << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kSouthEast>)       << std::endl;
    std::cout << "kSouthWest"       << std::endl << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kSouthWest>)       << std::endl;
    std::cout << "kNorthWest"       << std::endl << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kNorthWest>)       << std::endl;
    std::cout << "kNorthNorth"      << std::endl << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kNorthNorth>)      << std::endl;
    std::cout << "kEastEast"        << std::endl << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kEastEast>)        << std::endl;
    std::cout << "kSouthSouth"      << std::endl << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kSouthSouth>)      << std::endl;
    std::cout << "kWestWest"        << std::endl << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kWestWest>)        << std::endl;
    std::cout << "kNorthNorthEast"  << std::endl << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kNorthNorthEast>)  << std::endl;
    std::cout << "kNorthNorthWest"  << std::endl << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kNorthNorthWest>)  << std::endl;
    std::cout << "kEastEastNorth"   << std::endl << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kEastEastNorth>)   << std::endl;
    std::cout << "kEastEastSouth"   << std::endl << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kEastEastSouth>)   << std::endl;
    std::cout << "kSouthSouthEast"  << std::endl << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kSouthSouthEast>)  << std::endl;
    std::cout << "kSouthSouthWest"  << std::endl << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kSouthSouthWest>)  << std::endl;
    std::cout << "kWestWestNorth"   << std::endl << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kWestWestNorth>)   << std::endl;
    std::cout << "kWestWestSouth"   << std::endl << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kWestWestSouth>)   << std::endl;
    std::cout << "kDirectionNone"   << std::endl << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kDirectionNone>)   << std::endl;
    return 0;
}
