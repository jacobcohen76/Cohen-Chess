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

    template <typename T1, typename T2, typename T3,
              size_t    m, size_t    n, size_t    p>
    constexpr void MatrixMult(const Matrix<T1, m, n>& op1,
                              const Matrix<T2, n, p>& op2,
                                    Matrix<T3, m, p>& acc) noexcept
    {
        for (size_t i = 0; i < m; ++i)
        for (size_t j = 0; j < p; ++j)
        for (size_t k = 0; k < n; ++k)
        {
            acc(i, j) += op1(i, k) * op2(k, j);
        }
    }

    template <typename T1, typename T2, typename T3, size_t m, size_t n>
    constexpr void MatrixMult<T1, T2, T3, m, n, 1>(const Matrix<T1, m, n>& op1,
                                                   const Matrix<T2, n, 1>& op2,
                                                         Matrix<T3, m, 1>& acc) noexcept
    {
        for (size_t i = 0; i < m; ++i)
        for (size_t k = 0; k < n; ++k)
        {
            acc(i, 0) += op1(i, k) * op2(k, 0);
        }
    }

    template <typename T1, typename T2, typename T3, size_t n, size_t p>
    constexpr void MatrixMult<T1, T2, T3, 1, n, p>(const Matrix<T1, 1, n>& op1,
                                                   const Matrix<T2, n, p>& op2,
                                                         Matrix<T3, 1, p>& acc) noexcept
    {
        for (size_t j = 0; j < p; ++i)
        for (size_t k = 0; k < n; ++k)
        {
            acc(0, j) += op1(0, k) * op2(k, j);
        }
    }

    template <typename T1, size_t num_rows_1, size_t num_cols_1,
              typename T2, size_t num_rows_2, size_t num_cols_2>
    constexpr auto MatrixMult(const Matrix<T1, num_rows_1, num_cols_1>& op1,
                              const Matrix<T2, num_rows_2, num_cols_2>& op2) noexcept
        -> Matrix<std::common_type_t<T1, T2>, num_rows_1, num_cols_2>
    {
        static_assert(num_cols_1 == num_rows_2);
        Matrix<std::common_type_t<T1, T2>, num_rows_1, num_cols_2> acc;
        MatrixMult(op1, op2, acc);
        return acc;
    }
}

namespace cohen::math
{
    
}

#endif
