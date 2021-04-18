#ifndef COHEN_CHESS_ENGINE_ATTACKS_H_INCLUDED
#define COHEN_CHESS_ENGINE_ATTACKS_H_INCLUDED

#include "../types/bitboard.h"
#include "../types/direction.h"
#include "../types/piece_type.h"
#include "../types/square.h"

namespace cohen_chess
{
    constexpr Bitboard BishopMask(Square sq)
    {
        return (DiagBB(DiagOf(sq)) | AntiBB(AntiOf(sq)) & ~SquareBB(sq)) & ~kEdgesBB;
    }

    constexpr Bitboard RookMask(Square sq)
    {
        return ((RankBB(RankOf(sq)) & ~kRankEdgesBB) | (FileBB(FileOf(sq)) & ~kFileEdgesBB)) & ~SquareBB(sq);
    }

    template <Color side>
    constexpr Bitboard SetwisePawnAttacks(Bitboard pawns)
    {
        if constexpr (side == kWhite)
            return ShiftBB<kNorthEast>(pawns) | ShiftBB<kNorthWest>(pawns);
        else
            return ShiftBB<kSouthEast>(pawns) | ShiftBB<kSouthWest>(pawns);
    }

    constexpr Bitboard SetwiseKnightAttacks(Bitboard knights)
    {
        return ShiftBB<kNorthNorthEast>(knights) | ShiftBB<kEastEastNorth>(knights) |
               ShiftBB<kNorthNorthWest>(knights) | ShiftBB<kEastEastSouth>(knights) |
               ShiftBB<kSouthSouthEast>(knights) | ShiftBB<kWestWestNorth>(knights) |
               ShiftBB<kSouthSouthWest>(knights) | ShiftBB<kWestWestSouth>(knights);
    }

    constexpr Bitboard SetwiseKingAttacks(Bitboard kings)
    {
        Bitboard attacks = ShiftBB<kEast>(kings) | ShiftBB<kWest>(kings);
        kings   |= attacks;
        attacks |= ShiftBB<kNorth>(kings) | ShiftBB<kSouth>(kings);
        return attacks;
    }

    constexpr Bitboard RayBishopAttacks(Bitboard occ, Square sq)
    {
        return RayBB<kNorthEast>(occ, sq) | RayBB<kNorthWest>(occ, sq) |
               RayBB<kSouthEast>(occ, sq) | RayBB<kSouthWest>(occ, sq);
    }

    constexpr Bitboard RayRookAttacks(Bitboard occ, Square sq)
    {
        return RayBB<kNorth>(occ, sq) | RayBB<kEast>(occ, sq) |
               RayBB<kSouth>(occ, sq) | RayBB<kWest>(occ, sq);
    }

    constexpr Bitboard RayQueenAttacks(Bitboard occ, Square sq)
    {
        return RayBishopAttacks(occ, sq) | RayRookAttacks(occ, sq);
    }
}

#endif