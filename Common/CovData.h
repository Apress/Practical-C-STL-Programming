//-----------------------------------------------------------------------------
// CovData.h
//-----------------------------------------------------------------------------

#ifndef COV_DATA_H_
#define COV_DATA_H_

#include <format>
#include <fstream>
#include <random>
#include <stdexcept>
#include <string>
#include <valarray>
#include "Common.h"
#include "Matrix.h"

template <typename T = double> requires std::floating_point<T>
class CovData
{
public:
    CovData() = delete;
    explicit CovData(size_t num_vars, size_t num_obvs) :
        m_Data(num_vars, num_obvs), m_CovMat(num_vars, num_vars),
        m_VarMeans(num_vars), m_VarStdDevs(num_vars) {};

    //
    void generate_data(T rng_min, T rng_max, unsigned int rng_seed)
    {
        std::mt19937 rng_engine {};
        std::uniform_real_distribution<T> rng_dist { rng_min, rng_max };

        if (rng_seed == 0)
        {
            std::random_device rd {};
            rng_engine.seed(rd());
        }
        else
            rng_engine.seed(rng_seed);

        for (size_t i = 0; i < m_Data.NumRows(); ++i)
        {
            for (size_t j = 0; j < m_Data.NumCols(); ++j)
                m_Data(i, j) = rng_dist(rng_engine);
        }
    }

    void covariance()
    {
        m_VarMeans = m_Data.row_means();
        m_CovMat = m_Data.covariance(m_VarMeans);

        // main diagonal of covariance matrix contains variable variances
        auto variances = m_CovMat.main_diag();
        m_VarStdDevs = std::sqrt(variances);
    }

    void covariance_indx()
    {
        m_VarMeans = m_Data.row_means();
        m_CovMat = m_Data.covariance_indx(m_VarMeans);

        // main diagonal of covariance matrix contains variable variances
        auto variances = m_CovMat.main_diag();
        m_VarStdDevs = std::sqrt(variances);
    }

    //
    void save_results(const char* fn, const char* fmt) const
    {
        std::ofstream ofs {fn, std::ios_base::out | std::ios_base::trunc};

        if (!ofs.good())
            throw std::runtime_error("CovData::save_results - file open error");

        // write data matrix
        std::println(ofs, "----- Data Matrix (transposed) -----");
        for (size_t j = 0; j < m_Data.NumCols(); ++j)
        {
            std::string s_dm {};
            std::format_to(std::back_inserter(s_dm), "{:4d}: ", j);

            for (size_t i = 0; i < m_Data.NumRows(); ++i)
            {
                std::vformat_to(std::back_inserter(s_dm), fmt,
                    std::make_format_args(m_Data(i, j)));
            }

            std::println(ofs, "{:s}", s_dm);
        }

        // write variable means
        std::println(ofs, "\n----- Variable Means -----");
        std::string align(6, ' ');
        std::string s_vm {align};

        for (size_t i = 0; i < m_VarMeans.size(); ++i)
        {
            std::vformat_to(std::back_inserter(s_vm), fmt,
                std::make_format_args(m_VarMeans[i]));
        }
        std::println(ofs, "{:s}", s_vm);

        // write covariance matrix
        std::println(ofs, "\n----- Covariance Matrix -----");
        for (size_t i = 0; i < m_CovMat.NumRows(); ++i)
        {
            std::string s_cm {};
            std::format_to(std::back_inserter(s_cm), "{:4d}: ", i);

            for (size_t j = 0; j < m_CovMat.NumCols(); ++j)
            {
                std::vformat_to(std::back_inserter(s_cm), fmt,
                    std::make_format_args(m_CovMat(i, j)));
            }

            std::println(ofs, "{:s}", s_cm);
        }

        // write variable standard deviations
        std::println(ofs, "\n----- Variable Standard Deviations -----");
        std::string s_vsd {align};

        for (size_t i = 0; i < m_VarStdDevs.size(); ++i)
        {
            std::vformat_to(std::back_inserter(s_vsd), fmt,
                std::make_format_args(m_VarStdDevs[i]));
        }
        std::println(ofs, "{:s}", s_vsd);
   
        ofs.close();
        std::println("results saved to file {:s}", fn);
    }

private:
    Matrix<T> m_Data {};                // data matrix (num_vars x num_obvs)
    Matrix<T> m_CovMat {};              // covariance matrix (num_vars x num_vars)
    std::valarray<T> m_VarMeans {};     // var means (num_vars)
    std::valarray<T> m_VarStdDevs{};    // var standard deviations (num_vars)
};

#endif
