#include <cohen_chess.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <locale>

int main(int argc, char* argv[])
{
    std::cout << "kNorth"           << '\n' << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kNorth>)           << '\n';
    std::cout << "kEast"            << '\n' << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kEast>)            << '\n';
    std::cout << "kSouth"           << '\n' << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kSouth>)           << '\n';
    std::cout << "kWest"            << '\n' << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kWest>)            << '\n';
    std::cout << "kNorthEast"       << '\n' << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kNorthEast>)       << '\n';
    std::cout << "kSouthEast"       << '\n' << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kSouthEast>)       << '\n';
    std::cout << "kSouthWest"       << '\n' << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kSouthWest>)       << '\n';
    std::cout << "kNorthWest"       << '\n' << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kNorthWest>)       << '\n';
    std::cout << "kNorthNorth"      << '\n' << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kNorthNorth>)      << '\n';
    std::cout << "kEastEast"        << '\n' << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kEastEast>)        << '\n';
    std::cout << "kSouthSouth"      << '\n' << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kSouthSouth>)      << '\n';
    std::cout << "kWestWest"        << '\n' << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kWestWest>)        << '\n';
    std::cout << "kNorthNorthEast"  << '\n' << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kNorthNorthEast>)  << '\n';
    std::cout << "kNorthNorthWest"  << '\n' << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kNorthNorthWest>)  << '\n';
    std::cout << "kEastEastNorth"   << '\n' << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kEastEastNorth>)   << '\n';
    std::cout << "kEastEastSouth"   << '\n' << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kEastEastSouth>)   << '\n';
    std::cout << "kSouthSouthEast"  << '\n' << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kSouthSouthEast>)  << '\n';
    std::cout << "kSouthSouthWest"  << '\n' << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kSouthSouthWest>)  << '\n';
    std::cout << "kWestWestNorth"   << '\n' << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kWestWestNorth>)   << '\n';
    std::cout << "kWestWestSouth"   << '\n' << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kWestWestSouth>)   << '\n';
    std::cout << "kDirectionNone"   << '\n' << cohen_chess::AsciiBoard(cohen_chess::type::bitboard::kShiftMask<cohen_chess::kDirectionNone>)   << '\n';
    return 0;
}
