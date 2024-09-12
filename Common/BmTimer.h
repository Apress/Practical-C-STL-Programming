//-----------------------------------------------------------------------------
// BmTimer.h
//-----------------------------------------------------------------------------

#ifndef BM_TIMER_H_
#define BM_TIMER_H_
#include <chrono>
#include <format>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "Common.h"

template <class CLK>
class BmTimer
{
    // time point alias
    using TP = std::chrono::time_point<CLK, typename CLK::duration>;

public:
    enum class EtUnit
        { NanoSec, MicroSec, MilliSec, Sec, Default = Sec };

    BmTimer() = delete;

    BmTimer(size_t num_iter, size_t num_alg) : m_NumIter {num_iter},
        m_NumAlg {num_alg}
    {
        static_assert(CLK::is_steady);

        m_StartTimes.resize(num_iter * num_alg);
        m_StopTimes.resize(num_iter * num_alg);
    }

    void save_to_csv(const std::string& fn, const char* fmt,
        EtUnit et_unit = EtUnit::Default)
    {
        namespace chrono = std::chrono;

        std::ofstream ofs(fn);

        if (!ofs.good())
            throw std::runtime_error("BmTimer::save_to_csv - file open error");

        for (size_t i = 0; i < m_NumIter; ++i)
        {
            for (size_t j = 0; j < m_NumAlg; ++j)
            {
                auto t_start =  m_StartTimes[i * m_NumAlg + j];
                auto t_stop = m_StopTimes[i * m_NumAlg + j];
                auto t_temp1 = t_stop - t_start;
                auto t_temp2 =
                    chrono::duration_cast<std::chrono::duration<double>>(t_temp1);

                double t_elapsed = static_cast<double>(t_temp2.count()); // seconds

                switch (et_unit)
                {
                    case EtUnit::NanoSec:
                        t_elapsed *= 1.0e9;
                        break;

                    case EtUnit::MicroSec:
                        t_elapsed *= 1.0e6;
                        break;

                    case EtUnit::MilliSec:
                        t_elapsed *= 1.0e3;
                        break;

                    default:
                        break;
                }

                // write formated time to output file
                const char* sep = (j + 1 < m_NumAlg) ? ", " : "\n";
                std::string s {std::vformat(fmt, std::make_format_args(t_elapsed))};
                std::print(ofs, "{:s}", s);
                std::print(ofs, "{:s}", sep);
            }
        }

        ofs.close();
    }

    void start(size_t iter_id, size_t alg_id)
        { m_StartTimes[iter_id * m_NumAlg + alg_id] = CLK::now(); }

    void stop(size_t iter_id, size_t alg_id)
        { m_StopTimes[iter_id * m_NumAlg + alg_id] = CLK::now(); }

private:
    size_t m_NumIter {};
    size_t m_NumAlg {};
    std::vector<TP> m_StartTimes {};
    std::vector<TP> m_StopTimes {};
};

// convenience aliases
using BmTimerSteadyClk = BmTimer<std::chrono::steady_clock>;
using BmTimerHighResClk = BmTimer<std::chrono::high_resolution_clock>;

#endif
