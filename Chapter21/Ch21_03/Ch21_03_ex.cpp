//-----------------------------------------------------------------------------
// Ch21_03_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <string>
#include <vector>
#include <thread>
#include "Ch21_03.h"
#include "Airport.h"
#include "THR.h"

struct ConditionVarDemo
{
    // event signaling 
    std::mutex Mutex {};
    std::condition_variable ConditionVar {};
    bool NoMoreData {};
    bool DataReady {};

    // generated data
    std::vector<Airport> Airports {};
    std::vector<double> Distances {};
    Airport::GeoCoord::Units Units {};

    // miscellaneous data
    unsigned int RngSeed {};
};

static void generate_data(ConditionVarDemo& cvd)
{
    std::print("\nENTER generate_data\n");

    for (unsigned int n = 3; n < 8; ++n)
    {
        // generate data
        auto airports = get_random_airports(n, cvd.RngSeed + n);
        auto distances = calc_distance_matrix(airports, cvd.Units);

        // move data into cvd
        {
            std::lock_guard<std::mutex> lock(cvd.Mutex);
            cvd.Airports = std::move(airports);
            cvd.Distances = std::move(distances);
            cvd.DataReady = true;
        }

        // send data ready notification
        // (sleep added to simulate random processing delays)
        cvd.ConditionVar.notify_one();
        THR::sleep_for_random_ms(250, 500);
    }

    // signal end of data
    {
        std::lock_guard<std::mutex> lock(cvd.Mutex);
        cvd.NoMoreData = true;
    }

    cvd.ConditionVar.notify_one();
    THR::sleep_for_random_ms(25, 50);
    std::print("\nEXIT  generate_data\n");
}

static void process_data(ConditionVarDemo& cvd)
{
    std::print("\nENTER process_data\n");

    // miscellanous data items
    bool done {};
    std::vector<Airport> airports {};
    std::vector<double> distances {};
    std::string units {"Uknown"};

    if (cvd.Units == Airport::GeoCoord::Units::mi)
        units = "Miles";
    else if (cvd.Units == Airport::GeoCoord::Units::km)
        units = "Kilometers";

    while (!done)
    {
        {
            // wait for event
            std::unique_lock<std::mutex> lk(cvd.Mutex);

            cvd.ConditionVar.wait(lk,
                    [&cvd] { return cvd.NoMoreData || cvd.DataReady; });

            if (cvd.NoMoreData)
                done = true;
            else
            {
                cvd.DataReady = false;
                airports = std::move(cvd.Airports);
                distances = std::move(cvd.Distances);
            }
        }

        // above lock released, generate_data() can now lock again
        if (!done)
        {
            std::string title = std::format(
                "---- Distance Matrix ({:d} airports in {:s}) -----", airports.size(),
                units);

            print_distance_matrix(title, airports, distances);
        }
    }

    std::print("\nEXIT  process_data\n");
}

void Ch21_03_ex1()
{
    ConditionVarDemo cvd {};
    cvd.RngSeed = 73;
    cvd.Units = Airport::GeoCoord::Units::mi;

    // launch process_data and generate_data threads
    // (sleep allows time for process_data thread to begin)
    std::jthread thread1(process_data, std::ref(cvd));
    std::this_thread::sleep_for(std::chrono::milliseconds(25));
    std::jthread thread2(generate_data, std::ref(cvd));

    // threads joined here
}

void Ch21_03_ex()
{
    std::println("\n----- Ch21_03_ex1() -----");
    Ch21_03_ex1();
}
