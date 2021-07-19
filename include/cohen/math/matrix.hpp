#ifndef COHEN_MATH_MATRIX_HPP_INCLUDED
#define COHEN_MATH_MATRIX_HPP_INCLUDED

#include <array>
#include <cassert>
#include <type_traits>

namespace cohen::math::matrix
{
    template <typename T, size_t num_rows, size_t num_cols>
    class Matrix
    {
    public:
        constexpr size_t rows() const noexcept;
        constexpr size_t cols() const noexcept;
        constexpr size_t size() const noexcept;

        constexpr T* data() noexcept;
        constexpr const T* data() const noexcept;

        constexpr T& operator()(size_t, size_t) noexcept;
        constexpr const T& operator()(size_t, size_t) const noexcept;

    private:
        constexpr size_t index(size_t, size_t) const noexcept;

        T array[num_rows * num_cols];
    };

    template <typename T, size_t num_rows, size_t num_cols>
    constexpr size_t Matrix<T, num_rows, num_cols>::rows() const noexcept
    {
        return num_rows;
    }

    template <typename T, size_t num_rows, size_t num_cols>
    constexpr size_t Matrix<T, num_rows, num_cols>::cols() const noexcept
    {
        return num_cols;
    }

    template <typename T, size_t num_rows, size_t num_cols>
    constexpr size_t Matrix<T, num_rows, num_cols>::size() const noexcept
    {
        return rows() * cols();
    }

    template <typename T, size_t num_rows, size_t num_cols>
    constexpr T* Matrix<T, num_rows, num_cols>::data() noexcept
    {
        return array;
    }

    template <typename T, size_t num_rows, size_t num_cols>
    constexpr const T* Matrix<T, num_rows, num_cols>::data() const noexcept
    {
        return array;
    }

    template <typename T, size_t num_rows, size_t num_cols>
    constexpr T& Matrix<T, num_rows, num_cols>::operator()(size_t row, size_t col) noexcept
    {
        assert(0 <= row && row < rows());
        assert(0 <= col && col < cols());
        return array[index(row, col)];
    }

    template <typename T, size_t num_rows, size_t num_cols>
    constexpr const T& Matrix<T, num_rows, num_cols>::operator()(size_t row, size_t col) const noexcept
    {
        assert(0 <= row && row < rows());
        assert(0 <= col && col < cols());
        return array[index(row, col)];
    }

    template <typename T, size_t num_rows, size_t num_cols>
    constexpr size_t Matrix<T, num_rows, num_cols>::index(size_t row, size_t col) const noexcept
    {
        return row * cols() + col;
    }
}

namespace cohen::math
{
    using cohen::math::matrix::Matrix;
}

#endif
