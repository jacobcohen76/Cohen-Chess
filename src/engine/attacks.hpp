#ifndef COHEN_CHESS_ENGINE_ATTACKS_HPP_INCLUDED
#define COHEN_CHESS_ENGINE_ATTACKS_HPP_INCLUDED

#include <type/bitboard.hpp>
#include <type/color.hpp>

namespace cohen_chess::engine::attacks
{
    template <Color side>
    constexpr Bitboard SetwisePawnAttacks(Bitboard pawns) noexcept
    {
        static_assert(side == kWhite || side == kBlack);
        if constexpr (side == kWhite)
        {
            return ShiftBB<kNorthEast>(pawns) | ShiftBB<kNorthWest>(pawns);
        }
        else
        {
            return ShiftBB<kSouthEast>(pawns) | ShiftBB<kSouthWest>(pawns);
        }
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

    constexpr std::array<std::array<Bitboard, kSquareNB>, kColorNB> kPawnAttackTable = []()
    {
        std::array<std::array<Bitboard, kSquareNB>, kColorNB> pawn_table = {};
        std::generate(std::begin(pawn_table), std::end(pawn_table),
        [color = Color(kWhite)]() mutable -> std::array<Bitboard, kSquareNB>
        {
            std::array<Bitboard, kSquareNB> sub_table = {};
            std::generate(std::begin(sub_table), std::end(sub_table),
            [color, sq = Square(kA1)]() mutable -> Bitboard
            {
                return RuntimePawnAttacks(sq++, color);
            });
            return sub_table;
        });
        return pawn_table;
    }();

    constexpr Bitboard LookupPawnAttacks(Square sq, Color side) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        assert(side == kWhite || side == kBlack);
        return kPawnAttackTable[side][sq];
    }

    constexpr Bitboard PawnAttacks(Square sq, Color side) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        assert(side == kWhite || side == kBlack);
        return LookupPawnAttacks(sq, side);
    }

    constexpr Bitboard SetwiseKnightAttacks(Bitboard knights) noexcept
    {
        const Bitboard inner = ShiftBB<kEast>    (knights) | ShiftBB<kWest>    (knights);
        const Bitboard outer = ShiftBB<kEastEast>(knights) | ShiftBB<kWestWest>(knights);
        return ShiftBB<kNorthNorth>(inner) | ShiftBB<kSouthSouth>(inner) |
               ShiftBB<kNorth>     (outer) | ShiftBB<kSouth>     (outer);
    }

    constexpr Bitboard RuntimeKnightAttacks(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return SetwiseKnightAttacks(SquareBB(sq));
    }

    constexpr std::array<Bitboard, kSquareNB> kKnightAttackTable = []()
    {
        std::array<Bitboard, kSquareNB> knight_table = {};
        std::generate(std::begin(knight_table), std::end(knight_table),
        [sq = Square(kA1)]() mutable -> Bitboard
        {
            return RuntimeKnightAttacks(sq++);
        });
        return knight_table;
    }();

    constexpr Bitboard LookupKnightAttacks(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return kKnightAttackTable[sq];
    }

    constexpr Bitboard KnightAttacks(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return LookupKnightAttacks(sq);
    }

    constexpr Bitboard SetwiseKingAttacks(Bitboard kings) noexcept
    {
        Bitboard attacks = ShiftBB<kEast>(kings) | ShiftBB<kWest>(kings);
        kings |= attacks;
        return attacks | ShiftBB<kNorth>(kings) | ShiftBB<kSouth>(kings);
    }

    constexpr Bitboard RuntimeKingAttacks(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return SetwiseKingAttacks(SquareBB(sq));
    }

    constexpr std::array<Bitboard, kSquareNB> kKingAttackTable = []()
    {
        std::array<Bitboard, kSquareNB> king_table = {};
        std::generate(std::begin(king_table), std::end(king_table),
        [sq = Square(kA1)]() mutable -> Bitboard
        {
            return RuntimeKingAttacks(sq++);
        });
        return king_table;
    }();

    constexpr Bitboard LookupKingAttacks(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return kKingAttackTable[sq];
    }

    constexpr Bitboard KingAttacks(Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return LookupKingAttacks(sq);
    }

    constexpr Bitboard RayBishopAttacks(Bitboard occ, Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return RayBB<kNorthEast>(occ, sq) | RayBB<kNorthWest>(occ, sq) |
               RayBB<kSouthEast>(occ, sq) | RayBB<kSouthWest>(occ, sq);
    }

    constexpr Bitboard RayRookAttacks(Bitboard occ, Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return RayBB<kNorth>(occ, sq) | RayBB<kEast>(occ, sq) |
               RayBB<kSouth>(occ, sq) | RayBB<kWest>(occ, sq);
    }

    constexpr Bitboard RayQueenAttacks(Bitboard occ, Square sq) noexcept
    {
        assert(kA1 <= sq && sq < kSquareNB);
        return RayBishopAttacks(occ, sq) | RayRookAttacks(occ, sq);
    }
}

namespace cohen_chess
{
    using engine::attacks::SetwisePawnAttacks;
    using engine::attacks::PawnAttacks;
    using engine::attacks::SetwiseKnightAttacks;
    using engine::attacks::KnightAttacks;
    using engine::attacks::SetwiseKingAttacks;
    using engine::attacks::KnightAttacks;
    using engine::attacks::RayBishopAttacks;
    using engine::attacks::RayRookAttacks;
    using engine::attacks::RayQueenAttacks;
}

#endif