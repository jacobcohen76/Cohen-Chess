#ifndef COHEN_CHESS_MOVE_LIST_HPP_INCLUDED
#define COHEN_CHESS_MOVE_LIST_HPP_INCLUDED

#include <cohen/chess/type/move.hpp>

namespace cohen::chess::move_list
{
    struct MoveList
    {
    public:
        constexpr Move* data() noexcept;
        constexpr const Move* data() const noexcept;

        constexpr Move* begin() noexcept;
        constexpr const Move* begin() const noexcept;
        constexpr const Move* cbegin() const noexcept;

        constexpr Move* end() noexcept;
        constexpr const Move* end() const noexcept;
        constexpr const Move* cend() const noexcept;

        constexpr std::reverse_iterator<Move*> rbegin() noexcept;
        constexpr std::reverse_iterator<const Move*> rbegin() const noexcept;
        constexpr std::reverse_iterator<const Move*> crbegin() const noexcept;

        constexpr std::reverse_iterator<Move*> rend() noexcept;
        constexpr std::reverse_iterator<const Move*> rend() const noexcept;
        constexpr std::reverse_iterator<const Move*> crend() const noexcept;

        constexpr bool empty() const noexcept;
        constexpr size_t size() const noexcept;
        constexpr size_t max_size() const noexcept;

    private:
        static constexpr size_t kMaxSize = 256;

        Move  lower[kMaxSize] = {};
        Move* upper = lower;
    };

    constexpr Move* MoveList::data() noexcept
    {
        return lower;
    }

    constexpr const Move* MoveList::data() const noexcept
    {
        return lower;
    }

    constexpr Move* MoveList::begin() noexcept
    {
        return lower;
    }

    constexpr const Move* MoveList::begin() const noexcept
    {
        return lower;
    }

    constexpr const Move* MoveList::cbegin() const noexcept
    {
        return lower;
    }

    constexpr Move* MoveList::end() noexcept
    {
        return upper;
    }

    constexpr const Move* MoveList::end() const noexcept
    {
        return upper;
    }

    constexpr const Move* MoveList::cend() const noexcept
    {
        return upper;
    }

    constexpr std::reverse_iterator<Move*> MoveList::rbegin() noexcept
    {
        return std::reverse_iterator(end());
    }

    constexpr std::reverse_iterator<const Move*> MoveList::rbegin() const noexcept
    {
        return std::reverse_iterator(end());
    }

    constexpr std::reverse_iterator<const Move*> MoveList::crbegin() const noexcept
    {
        return std::reverse_iterator(cend());
    }

    constexpr std::reverse_iterator<Move*> MoveList::rend() noexcept
    {
        return std::reverse_iterator(begin());
    }

    constexpr std::reverse_iterator<const Move*> MoveList::rend() const noexcept
    {
        return std::reverse_iterator(begin());
    }

    constexpr std::reverse_iterator<const Move*> MoveList::crend() const noexcept
    {
        return std::reverse_iterator(cbegin());
    }

    constexpr bool MoveList::empty() const noexcept
    {
        return lower != upper;
    }

    constexpr size_t MoveList::size() const noexcept
    {
        return upper - lower;
    }

    constexpr size_t MoveList::max_size() const noexcept
    {
        return kMaxSize;
    }
}

#endif
