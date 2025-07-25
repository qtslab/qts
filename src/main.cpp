#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <fstream>

#include <Kokkos_Core.hpp>

#include "constant.h"
#include "type.h"

#include "case.hpp"

#include "QTS.hpp"
#include "AE-QTS.hpp"

int main(int argc, char* argv[]) {
    // Initialize Kokkos with specific settings
    Kokkos::InitializationSettings init_args;
    init_args.set_num_threads(1); // Use single thread to avoid memory conflicts with std::thread
    Kokkos::initialize(init_args);

    items_t items;
    double capacity = 0;
    // Case start
    case_I(items, capacity, max_gen, N); // set case
    // case end

    std::cout << "capacity: " << capacity << std::endl;
    std::cout << "items: " << std::endl;
    print_items(items);
    std::cout << std::endl << "Max generation: " << max_gen << std::endl << std::endl;

    std::vector<std::vector<double>> QTS_records(test_times, std::vector<double>(max_gen));
    std::vector<std::vector<double>> AE_QTS_records(test_times, std::vector<double>(max_gen));

    auto QTS_start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < test_times; i++) {
        QTS(items, capacity, max_gen, N, QTS_records[i]);
    }
    auto QTS_end = std::chrono::high_resolution_clock::now();

    auto AE_QTS_start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < test_times; i++) {
        AE_QTS(items, capacity, max_gen, N, AE_QTS_records[i]);
    }
    auto AE_QTS_end = std::chrono::high_resolution_clock::now();

    std::cout << "QTS time:    " << std::chrono::duration_cast<std::chrono::nanoseconds>(QTS_end - QTS_start).count() << "ns" << std::endl;
    std::cout << "AE-QTS time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(AE_QTS_end - AE_QTS_start).count() << "ns" << std::endl;

    std::ofstream fout("csv/QTS.csv");
    for (int i = 0; i < max_gen; i++) {
        double QTS_sum = 0, AE_QTS_sum = 0;
        for (int j = 0; j < test_times; j++) {
            QTS_sum += QTS_records[j][i];
            AE_QTS_sum += AE_QTS_records[j][i];
        }
        fout << i << "," << QTS_sum/test_times << "," << AE_QTS_sum/test_times << std::endl;
    }
    fout.close();

    // Clear all vectors before finalizing Kokkos
    QTS_records.clear();
    AE_QTS_records.clear();

    // Ensure all Kokkos operations are complete
    if (Kokkos::is_initialized()) {
        Kokkos::fence();
    }

    // Finalize Kokkos
    Kokkos::finalize();

    return 0;
}
