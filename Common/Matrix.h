//-----------------------------------------------------------------------------
// Matrix.h
//-----------------------------------------------------------------------------

#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <valarray>

#ifndef MATRIX_H_
#define MATRIX_H_

template <typename T> requires std::floating_point<T>
class Matrix
{
public:
    Matrix() = delete;

    explicit Matrix(size_t num_rows, size_t num_cols) : m_NumRows {num_rows},
        m_NumCols {num_cols}, m_Data(m_NumRows * m_NumCols) {};

    Matrix(size_t num_rows, size_t num_cols, const std::valarray<T>& va) :
        m_NumRows {num_rows}, m_NumCols {num_cols}, m_Data(m_NumRows * m_NumCols)
    {
        const size_t n = m_NumRows * m_NumCols;

        if (va.size() < n)
            throw std::runtime_error("Matrix::Matrix - invalid va.size()");

        std::copy(std::begin(va), std::end(va), std::begin(m_Data));
    }

    size_t NumRows() const { return m_NumRows; }
    size_t NumCols() const { return m_NumCols; }

    // element accessors
    T& operator()(size_t row, size_t col)
    {
        if (row >= m_NumRows || col >= m_NumCols)
            throw std::runtime_error("Matrix::operator() - invalid index");

        return m_Data[row * m_NumCols + col];
    }

    const T& operator()(size_t row, size_t col) const
    {
        if (row >= m_NumRows || col >= m_NumCols)
            throw std::runtime_error("Matrix::operator() const - invalid index");

        return m_Data[row * m_NumCols + col];
    }

    // row & column accessors
    std::valarray<T> row(size_t row) const { return m_Data[row_slice(row)]; }

    std::slice row_slice(size_t row) const
    {
        if (row >= m_NumRows)
            throw std::runtime_error("Matrix::row_slice - invalid row index");

        return std::slice(row * m_NumCols, m_NumCols, 1);
    }

    std::valarray<T> col(size_t col) const { return m_Data[col_slice(col)]; }

    std::slice col_slice(size_t col) const
    {
        if (col >= m_NumCols)
            throw std::runtime_error("Matrix::col_slice - invalid col index");

        return std::slice(col, m_NumRows, m_NumCols);
    }

    // miscellaneous matrix functions
    void fill(T val) { m_Data = val; }
    void iota(T val) { std::iota(std::begin(m_Data), std::end(m_Data), val); }

    std::valarray<T> main_diag() const
    {
        if (m_NumRows != m_NumCols)
            throw std::runtime_error("Matrix::main_diag - non-square matrix");

        auto md_slice = std::slice(0, m_NumRows, m_NumRows + 1);
        return m_Data[md_slice];
    }

    T trace() const
    {
        if (m_NumRows != m_NumCols)
            throw std::runtime_error("Matrix::trace - non-square matrix");

        auto tr_slice = std::slice(0, m_NumRows, m_NumRows + 1);
        return m_Data[tr_slice].sum();
    }

    std::valarray<T> row_means() const
    {
        std::valarray<T> row_means_va(m_NumRows);

        for (size_t i = 0; i < m_NumRows; ++i)
            row_means_va[i] = m_Data[row_slice(i)].sum() / m_NumCols;

        return row_means_va;
    }

    std::valarray<T> col_means()
    {
        std::valarray<T> col_means_va(m_NumCols);

        for (size_t i = 0; i < m_NumCols; ++i)
            col_means_va[i] = m_Data[col_slice(i)].sum() / m_NumRows;

        return col_means_va;
    }

    // matrix operators
    friend bool operator==(const Matrix<T>& m1, const Matrix<T>& m2)
    {
        if (!same_size(m1, m2))
            return false;

        std::valarray<bool> cmp = m1.m_Data == m2.m_Data;
        return std::ranges::all_of(cmp, [](bool x) { return x; });
    }

    friend bool operator!=(const Matrix<T>& m1, const Matrix<T>& m2)
        { return !operator==(m1, m2); }

    friend Matrix operator+(const Matrix& m1, const Matrix& m2)
    {
        if (!same_size(m1, m2))
            throw std::runtime_error("Matrix::operator+ - size error");

        Matrix m3 = m1;
        m3.m_Data += m2.m_Data;
        return m3;
    }

    // matrix multiplication using std::slice
    friend Matrix operator*(const Matrix& m1, const Matrix& m2)
    {
        if (m1.m_NumCols != m2.m_NumRows)
            throw std::runtime_error("Matrix::operator* - invalid size");

        Matrix m3(m1.m_NumRows, m2.m_NumCols);

        for (size_t i = 0; i < m1.m_NumRows; ++i)
        {
            std::valarray<T> m1_row = m1.m_Data[m1.row_slice(i)];

            for (size_t j = 0; j < m2.m_NumCols; ++j)
            {
                std::valarray<T> m2_col = m2.m_Data[m2.col_slice(j)];

                // m3(i, j) = inner product of m1 row i, and m2 col j
                T dp = (m1_row * m2_col).sum();
                m3.m_Data[i * m3.m_NumCols + j] = dp;
            }
        }

        return m3;
    }

    // classic matrix multiplication using indicies
    static Matrix mul(const Matrix& m1, const Matrix& m2)
    {
        if (m1.m_NumCols != m2.m_NumRows)
            throw std::runtime_error("Matrix::mul - invalid size");

        Matrix m3(m1.m_NumRows, m2.m_NumCols);

        for (size_t i = 0; i < m1.m_NumRows; ++i)
        {
            for (size_t j = 0; j < m2.m_NumCols; ++j)
            {
                T sum {};

                for (size_t k = 0; k < m1.m_NumCols; ++k)
                {
                    T t = m1.m_Data[i * m1.m_NumCols + k] *
                            m2.m_Data[k * m2.m_NumCols + j];

                    sum += t;
                }

                m3.m_Data[i * m3.m_NumCols + j] = sum;
            }
        }

        return m3;
    }

    // covariance matrix using slices
    Matrix covariance(const std::valarray<T>& var_means) const
    {
        const size_t num_vars = m_NumRows;
        const size_t num_obvs = m_NumCols;
        
        if (var_means.size() != num_vars)
            throw std::runtime_error("Matrix::covariance - invalid size");

        Matrix cvm(num_vars, num_vars);      // covariance matrix

        for (size_t i = 0; i < num_vars; i++)
        {
            std::slice row_i = std::slice(i * num_obvs, num_obvs, 1);
            std::valarray<T> t1 = m_Data[row_i] - var_means[i];

            for (size_t j = 0; j < num_vars; j++)
            {
               if (i <= j)
               {
                    // calculate cvm(i, j)
                    std::slice row_j = std::slice(j * num_obvs, num_obvs, 1);
                    std::valarray<T> t2 = m_Data[row_j] - var_means[j];
                    T t3 = (t1 * t2).sum();

                    cvm.m_Data[i * num_vars + j] = t3 / (num_obvs - 1);
               }
               else
                    cvm.m_Data[i * num_vars + j] = cvm.m_Data[j * num_vars + i];
            }
        }

        return cvm;
    }

    // covariance matrix using indices
    Matrix covariance_indx(const std::valarray<T>& var_means) const
    {
        const size_t num_vars = m_NumRows;
        const size_t num_obvs = m_NumCols;
        
        if (var_means.size() != num_vars)
            throw std::runtime_error("Matrix::covariance_indx - invalid size");

        Matrix cvm(num_vars, num_vars);      // covariance matrix

        for (size_t i = 0; i < num_vars; i++)
        {
            for (size_t j = 0; j < num_vars; j++)
            {
                if (i <= j)
                {
                    T sum {};

                    for (size_t k = 0; k < num_obvs; k++)
                    {
                        T t1 = m_Data[i * num_obvs + k] - var_means[i];
                        T t2 = m_Data[j * num_obvs + k] - var_means[j];
                        sum += t1 * t2;
                    }

                    cvm.m_Data[i * num_vars + j] = sum / (num_obvs - 1);
                }
                else
                    cvm.m_Data[i * num_vars + j] = cvm.m_Data[j * num_vars + i];
            }
        }

        return cvm;
    }

private:
    static bool same_size(const Matrix& m1, const Matrix& m2)
        { return m1.m_NumRows == m2.m_NumRows && m1.m_NumCols == m2.m_NumCols; }

    size_t m_NumRows {};
    size_t m_NumCols {};
    std::valarray<T> m_Data {};         // data matrix
};

// formatter for class matrix 
template <typename T> struct std::formatter<Matrix<T>> : std::formatter<std::string>
{
    constexpr auto parse(std::format_parse_context& fpc)
    {
        m_Format = "{:";

        for (auto iter = fpc.begin(); iter != fpc.end(); ++iter)
        {
            char c = *iter;
            m_Format += c;

            if (c == '}')
                return iter;
        }

        return fpc.end();
    }

    auto format(const Matrix<T>& m, std::format_context& fc) const
    {
        std::string s {};

        for (size_t i = 0; i < m.NumRows(); ++i)
        {
            for (size_t j = 0; j < m.NumCols(); ++j)
            {
                std::vformat_to(std::back_inserter(s), m_Format,
                    std::make_format_args(m(i, j)));
                s += ' ';
            }

            if (i + 1 < m.NumRows())
                s += '\n';
        }

        return std::format_to(fc.out(), "{:s}", s);
    }

    std::string m_Format {};
};

#endif
