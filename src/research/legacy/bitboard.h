
#include <cstdint>

namespace cohen_chess
{
    class Bitboard
    {
        public:
            constexpr Bitboard(uint64_t);

            constexpr operator uint64_t() const;

            constexpr Bitboard operator +(const Bitboard) const;
            constexpr Bitboard operator -(const Bitboard) const;
            constexpr Bitboard operator *(const Bitboard) const;
            constexpr Bitboard operator /(Bitboard);

        private:
            uint64_t raw_;
    };

    constexpr Bitboard::Bitboard(uint64_t raw) : raw_(raw)
    {

    }

    constexpr Bitboard::operator uint64_t() const
    {
        return this->raw_;
    }

    constexpr Bitboard Bitboard::operator +(const Bitboard rhs) const
    {
        return Bitboard(this->raw_ + rhs.raw_);
    }

    constexpr Bitboard Bitboard::operator -(const Bitboard rhs) const
    {
        return Bitboard(this->raw_ - rhs.raw_);
    }

    constexpr Bitboard Bitboard::operator *(const Bitboard rhs) const
    {
        return Bitboard(this->raw_ * rhs.raw_);
    }

    constexpr Bitboard Bitboard::operator /(Bitboard rhs)
    {
        return Bitboard(this->raw_ / rhs.raw_);
    }
};