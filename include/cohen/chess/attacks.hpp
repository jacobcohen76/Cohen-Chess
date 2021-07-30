#ifndef COHEN_CHESS_ATTACKS_HPP_INCLUDED
#define COHEN_CHESS_ATTACKS_HPP_INCLUDED

#include <algorithm>
#include <array>
#include <cassert>
#include <ranges>

#include <cohen/chess/type/bitboard.hpp>
#include <cohen/chess/type/color.hpp>
#include <cohen/chess/type/square.hpp>

namespace cohen::chess::attacks
{
    template <Color side>
    constexpr Bitboard SetwisePawnAttacks(Bitboard pawns) noexcept
    {
        static_assert(side == kWhite || side == kBlack);
        if constexpr (side == kWhite)
            return ShiftBB<kNorthWest>(pawns) | ShiftBB<kNorthEast>(pawns);
        else
            return ShiftBB<kSouthWest>(pawns) | ShiftBB<kSouthEast>(pawns);
    }

    constexpr Bitboard SetwisePawnAttacks(Bitboard pawns, Color side) noexcept
    {
        assert(side == kWhite || side == kBlack);
        return side == kWhite ? SetwisePawnAttacks<kWhite>(pawns)
                              : SetwisePawnAttacks<kBlack>(pawns);
    }

    constexpr Bitboard RuntimePawnAttacks(Square sq, Color side) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        assert(side == kWhite || side == kBlack);
        return SetwisePawnAttacks(SquareBB(sq), side);
    }

    inline constexpr std::array<std::array<Bitboard, kSquareNB>, kColorNB> kPawnAttacksTable = []()
    {
        std::array<std::array<Bitboard, kSquareNB>, kColorNB> pawn_table = {};
        const auto range = std::views::iota(Square{kA1}, Square{kSquareNB})
                         | std::views::transform(SquareBB);
        const auto white_range = range | std::views::transform(SetwisePawnAttacks<kWhite>);
        const auto black_range = range | std::views::transform(SetwisePawnAttacks<kBlack>);
        std::ranges::copy(white_range, std::begin(pawn_table[kWhite]));
        std::ranges::copy(black_range, std::begin(pawn_table[kBlack]));
        return pawn_table;
    }();

    constexpr Bitboard LookupPawnAttacks(Square sq, Color side) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        assert(side == kWhite || side == kBlack);
        return kPawnAttacksTable[side][sq];
    }

    constexpr Bitboard PawnAttacks(Square sq, Color side) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        assert(side == kWhite || side == kBlack);
        return LookupPawnAttacks(sq, side);
    }

    constexpr Bitboard SetwiseKnightAttacks(Bitboard knights) noexcept
    {
        const Bitboard inner = ShiftBB<kWest>    (knights) | ShiftBB<kEast>    (knights);
        const Bitboard outer = ShiftBB<kWestWest>(knights) | ShiftBB<kEastEast>(knights);
        return ShiftBB<kNorth>(outer) | ShiftBB<kNorthNorth>(inner)
             | ShiftBB<kSouth>(outer) | ShiftBB<kSouthSouth>(inner);
    }

    constexpr Bitboard RuntimeKnightAttacks(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return SetwiseKnightAttacks(SquareBB(sq));
    }

    inline constexpr std::array<Bitboard, kSquareNB> kKnightAttacksTable = []()
    {
        std::array<Bitboard, kSquareNB> knight_table = {};
        const auto range = std::views::iota(Square{kA1}, Square{kSquareNB})
                         | std::views::transform(RuntimeKnightAttacks);
        std::ranges::copy(range, std::begin(knight_table));
        return knight_table;
    }();

    constexpr Bitboard LookupKnightAttacks(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return kKnightAttacksTable[sq];
    }

    constexpr Bitboard KnightAttacks(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return LookupKnightAttacks(sq);
    }

    constexpr Bitboard SetwiseKingAttacks(Bitboard kings) noexcept
    {
        const Bitboard attacks = ShiftBB<kWest>(kings) | ShiftBB<kEast>(kings);
        return ShiftBB<kNorth>(kings | attacks)
             | ShiftBB<kSouth>(kings | attacks)
             | attacks;
    }

    constexpr Bitboard RuntimeKingAttacks(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return SetwiseKingAttacks(SquareBB(sq));
    }

    inline constexpr std::array<Bitboard, kSquareNB> kKingAttacksTable = []()
    {
        std::array<Bitboard, kSquareNB> king_table = {};
        const auto range = std::views::iota(Square{kA1}, Square{kSquareNB})
                         | std::views::transform(RuntimeKingAttacks);
        std::ranges::copy(range, std::begin(king_table));
        return king_table;
    }();

    constexpr Bitboard LookupKingAttacks(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return kKingAttacksTable[sq];
    }

    constexpr Bitboard KingAttacks(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return LookupKingAttacks(sq);
    }

    constexpr Bitboard RayBishopAttacks(Bitboard occ, Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return RayBB<kNorthWest>(occ, sq) | RayBB<kNorthEast>(occ, sq)
             | RayBB<kSouthWest>(occ, sq) | RayBB<kSouthEast>(occ, sq);
    }

    constexpr Bitboard RayRookAttacks(Bitboard occ, Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return RayBB<kNorth>(occ, sq) | RayBB<kEast>(occ, sq)
             | RayBB<kSouth>(occ, sq) | RayBB<kWest>(occ, sq);
    }

    constexpr Bitboard RayQueenAttacks(Bitboard occ, Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return RayBishopAttacks(occ, sq) | RayRookAttacks(occ, sq);
    }
}

namespace cohen::chess
{
    using cohen::chess::attacks::SetwisePawnAttacks;
    using cohen::chess::attacks::PawnAttacks;
    using cohen::chess::attacks::SetwiseKnightAttacks;
    using cohen::chess::attacks::KnightAttacks;
    using cohen::chess::attacks::SetwiseKingAttacks;
    using cohen::chess::attacks::KingAttacks;
    using cohen::chess::attacks::RayBishopAttacks;
    using cohen::chess::attacks::RayRookAttacks;
    using cohen::chess::attacks::RayQueenAttacks;
}

#endif
