#ifndef COHEN_CHESS_ATTACKS_HPP_INCLUDED
#define COHEN_CHESS_ATTACKS_HPP_INCLUDED

#include <assert.h>

#include <algorithm>
#include <array>

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

    constexpr Bitboard SetwisePawnAttacks(Color side, Bitboard pawns) noexcept
    {
        assert(side == kWhite || side == kBlack);
        return side == kWhite ? SetwisePawnAttacks<kWhite>(pawns)
                              : SetwisePawnAttacks<kBlack>(pawns);
    }

    constexpr Bitboard RuntimePawnAttacks(Color side, Square sq) noexcept
    {
        assert(side == kWhite || side == kBlack);
        assert(kA1 <= sq && sq < kSquareNB);
        return SetwisePawnAttacks(side, SquareBB(sq));
    }

    inline constexpr std::array<std::array<Bitboard, kSquareNB>, kColorNB> kPawnAttacksTable = []()
    {
        std::array<std::array<Bitboard, kSquareNB>, kColorNB> pawn_table = {};
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            pawn_table[kWhite][sq] = RuntimePawnAttacks(kWhite, sq);
            pawn_table[kBlack][sq] = RuntimePawnAttacks(kBlack, sq);
        }
        return pawn_table;
    }();

    constexpr Bitboard LookupPawnAttacks(Color side, Square sq) noexcept
    {
        assert(side == kWhite || side == kBlack);
        assert(kA1 <= sq && sq < kSquareNB);
        return kPawnAttacksTable[side][sq];
    }

    constexpr Bitboard PawnAttacks(Color side, Square sq) noexcept
    {
        assert(side == kWhite || side == kBlack);
        assert(kA1 <= sq && sq < kSquareNB);
        return LookupPawnAttacks(side, sq);
    }

    constexpr Bitboard SetwiseKnightAttacks(Bitboard knights) noexcept
    {
        const Bitboard inner = ShiftBB<kWest>(knights) | ShiftBB<kEast>(knights);
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
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            knight_table[sq] = RuntimeKnightAttacks(sq);
        }
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
        for (Square sq = kA1; sq < kSquareNB; ++sq)
        {
            king_table[sq] = RuntimeKingAttacks(sq);
        }
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

    constexpr Bitboard RayBishopAttacks(Square sq, Bitboard occ) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return RayBB<kNorthWest>(sq, occ) | RayBB<kNorthEast>(sq, occ)
             | RayBB<kSouthWest>(sq, occ) | RayBB<kSouthEast>(sq, occ);
    }

    constexpr Bitboard RayRookAttacks(Square sq, Bitboard occ) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return RayBB<kNorth>(sq, occ) | RayBB<kEast>(sq, occ)
             | RayBB<kSouth>(sq, occ) | RayBB<kWest>(sq, occ);
    }

    constexpr Bitboard RayQueenAttacks(Square sq, Bitboard occ) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return RayBishopAttacks(sq, occ) | RayRookAttacks(sq, occ);
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