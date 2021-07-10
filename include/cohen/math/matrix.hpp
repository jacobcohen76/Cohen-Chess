#ifndef COHEN_MATH_MATRIX_HPP_INCLUDED
#define COHEN_MATH_MATRIX_HPP_INCLUDED

#include <array>
#include <span>

namespace cohen::math::matrix
{
    template <typename T, size_t rows, size_t cols>
    class Matrix
    {
    public:
        constexpr T& operator()(size_t, size_t) noexcept;

    private:
        T data[rows * cols];
    };

    template <typename T, std::size_t num_rows, std::size_t num_cols>
    class Matrix
    {
        static constexpr std::size_t rows() noexcept
        {
            return num_rows;
        }

        static constexpr std::size_t cols() noexcept
        {
            return num_cols;
        }
    };

}

namespace cohen::math
{
    
}

#endif
