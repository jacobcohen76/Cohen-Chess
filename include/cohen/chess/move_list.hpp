#ifndef COHEN_CHESS_MOVE_LIST_HPP_INCLUDED
#define COHEN_CHESS_MOVE_LIST_HPP_INCLUDED

#include <cassert>

#include <cohen/chess/type/move.hpp>

namespace cohen::chess::move_list
{
    struct MoveList
    {
        static constexpr size_t kMaxSize = 256;

        constexpr MoveList() noexcept = default;

        constexpr Move& operator[](size_t) noexcept;
        constexpr const Move& operator[](size_t) const noexcept;

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

        constexpr void clear() noexcept;
        constexpr void push(Move) noexcept;
        constexpr Move pop() noexcept;

        Move  mem_array[kMaxSize] = {};
        Move* stack_ptr = mem_array;
    };

    constexpr Move& MoveList::operator[](size_t index) noexcept
    {
        assert(0 <= index && index < size());
        return mem_array[index];
    }

    constexpr const Move& MoveList::operator[](size_t index) const noexcept
    {
        assert(0 <= index && index < size());
        return mem_array[index];
    }

    constexpr Move* MoveList::data() noexcept
    {
        return mem_array;
    }

    constexpr const Move* MoveList::data() const noexcept
    {
        return mem_array;
    }

    constexpr Move* MoveList::begin() noexcept
    {
        return mem_array;
    }

    constexpr const Move* MoveList::begin() const noexcept
    {
        return mem_array;
    }

    constexpr const Move* MoveList::cbegin() const noexcept
    {
        return mem_array;
    }

    constexpr Move* MoveList::end() noexcept
    {
        return stack_ptr;
    }

    constexpr const Move* MoveList::end() const noexcept
    {
        return stack_ptr;
    }

    constexpr const Move* MoveList::cend() const noexcept
    {
        return stack_ptr;
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
        return mem_array == stack_ptr;
    }

    constexpr size_t MoveList::size() const noexcept
    {
        return stack_ptr - mem_array;
    }

    constexpr size_t MoveList::max_size() const noexcept
    {
        return kMaxSize;
    }

    constexpr void MoveList::clear() noexcept
    {
        stack_ptr = mem_array;
    }

    constexpr void MoveList::push(Move move) noexcept
    {
        assert(size() < max_size());
        *stack_ptr++ = move;
    }

    constexpr Move MoveList::pop() noexcept
    {
        assert(size() > 0);
        return *--stack_ptr;
    }
}

namespace cohen::chess
{
    using cohen::chess::move_list::MoveList;
}

#endif
